#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>

#include "utilizadores.h"
#include "basededados.h"
#include "estruturas.h"
#include "bilhetes.h"
#include "faturas.h"
#include "concertos.h"


int loginUtilizador(char nome[], char nif[])
{
    SQLHSTMT hStmt;
    SQLRETURN ret;
    int encontrado = 0;

    char query[512];

    sprintf_s(query, sizeof(query),
        "SELECT COUNT(*) "
        "FROM dbo.Users "
        "WHERE user_name='%s' AND NIF='%s'",
        nome,
        nif);

    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    ret = SQLExecDirectA(hStmt, (SQLCHAR*)query, SQL_NTS);

    if (SQL_SUCCEEDED(ret))
    {
        SQLFetch(hStmt);

        SQLGetData(
            hStmt,
            1,
            SQL_C_LONG,
            &encontrado,
            0,
            NULL
        );
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    return encontrado;
}
void criarUtilizador(char nome[], char email[], char nif[])
{
    SQLHSTMT hStmt;
    SQLRETURN ret;

    char query[512];

    sprintf_s(query, sizeof(query),
        "INSERT INTO dbo.Users(user_name, email, NIF) "
        "VALUES('%s', '%s', '%s')",
        nome,
        email,
        nif);

    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    ret = SQLExecDirectA(hStmt, (SQLCHAR*)query, SQL_NTS);

    if (SQL_SUCCEEDED(ret))
    {
        printf("\nUtilizador criado com sucesso!\n");
    }
    else
    {
        SQLCHAR sqlState[6];
        SQLCHAR message[256];
        SQLINTEGER nativeError;
        SQLSMALLINT textLength;

        SQLGetDiagRecA(
            SQL_HANDLE_STMT,
            hStmt,
            1,
            sqlState,
            &nativeError,
            message,
            sizeof(message),
            &textLength
        );

        printf("\nErro SQL: %s\n", message);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}
int existeUtilizador(char nome[])
{
    SQLHSTMT hStmt;
    SQLRETURN ret;
    int existe = 0;

    char query[512];

    sprintf_s(query, sizeof(query),
        "SELECT COUNT(*) "
        "FROM dbo.Users "
        "WHERE user_name='%s'",
        nome);

    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    ret = SQLExecDirectA(hStmt, (SQLCHAR*)query, SQL_NTS);

    if (SQL_SUCCEEDED(ret))
    {
        SQLFetch(hStmt);

        SQLGetData(
            hStmt,
            1,
            SQL_C_LONG,
            &existe,
            0,
            NULL
        );
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    return existe;
}
int existeEmail(char email[])
{
    SQLHSTMT hStmt;
    SQLRETURN ret;
    int existe = 0;

    char query[512];

    sprintf_s(query, sizeof(query),
        "SELECT COUNT(*) "
        "FROM dbo.Users "
        "WHERE email='%s'",
        email);

    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    ret = SQLExecDirectA(hStmt, (SQLCHAR*)query, SQL_NTS);

    if (SQL_SUCCEEDED(ret))
    {
        SQLFetch(hStmt);

        SQLGetData(
            hStmt,
            1,
            SQL_C_LONG,
            &existe,
            0,
            NULL
        );
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    return existe;
}
int existeNIF(char nif[])
{
    SQLHSTMT hStmt;
    SQLRETURN ret;
    int existe = 0;

    char query[256];

    sprintf_s(query, sizeof(query),
        "SELECT COUNT(*) "
        "FROM dbo.Users "
        "WHERE NIF='%s'",
        nif);

    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    ret = SQLExecDirectA(hStmt, (SQLCHAR*)query, SQL_NTS);

    if (SQL_SUCCEEDED(ret))
    {
        SQLFetch(hStmt);

        SQLGetData(
            hStmt,
            1,
            SQL_C_LONG,
            &existe,
            0,
            NULL
        );
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    return existe;
}
int obterRole(char nome[], char nif[], char role[])
{
    SQLHSTMT hStmt;
    SQLRETURN ret;

    char query[512];

    sprintf_s(query, sizeof(query),
        "SELECT role "
        "FROM dbo.Users "
        "WHERE user_name='%s' AND NIF='%s'",
        nome,
        nif);

    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    ret = SQLExecDirectA(hStmt, (SQLCHAR*)query, SQL_NTS);

    if (SQL_SUCCEEDED(ret) && SQLFetch(hStmt) == SQL_SUCCESS)
    {
        SQLGetData(
            hStmt,
            1,
            SQL_C_CHAR,
            role,
            20,
            NULL
        );

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return 1;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return 0;
}
int obterIdUtilizador(char nome[], char nif[])
{
    SQLHSTMT hStmt;
    SQLRETURN ret;

    int id = 0;

    char query[512];

    sprintf_s(
        query,
        sizeof(query),
        "SELECT id_user "
        "FROM dbo.Users "
        "WHERE user_name='%s' "
        "AND NIF='%s'",
        nome,
        nif);

    SQLAllocHandle(
        SQL_HANDLE_STMT,
        hDbc,
        &hStmt);

    ret = SQLExecDirectA(
        hStmt,
        (SQLCHAR*)query,
        SQL_NTS);

    if (SQL_SUCCEEDED(ret))
    {
        if (SQLFetch(hStmt) == SQL_SUCCESS)
        {
            SQLGetData(
                hStmt,
                1,
                SQL_C_LONG,
                &id,
                0,
                NULL);
        }
    }

    SQLFreeHandle(
        SQL_HANDLE_STMT,
        hStmt);

    return id;
}


void login()
{
    int opcao;

    char nome[100];
    char email[150];
    char nif[10];

    printf("\n===== LOGIN =====\n");
    printf("1 - Login\n");
    printf("2 - Criar Utilizador\n");
    printf("Opcao: ");

    scanf_s("%d", &opcao);
    getchar();

    switch (opcao)
    {
    case 1:
    {
        printf("Nome de utilizador: ");
        gets_s(nome, sizeof(nome));

        printf("NIF: ");
        gets_s(nif, sizeof(nif));

        if (loginUtilizador(nome, nif))
        {
            char role[20];
            int idUser;

            obterRole(nome, nif, role);

            /* NOVO */
            idUser = obterIdUtilizador(nome, nif);

            printf("\nLogin efetuado com sucesso!\n");

            if (strcmp(role, "ADMIN") == 0)
            {
                printf("Bem-vindo Administrador!\n");

                menuAdmin(idUser);
            }
            else
            {
                printf("Bem-vindo Utilizador!\n");

                menuUtilizador(idUser);
            }
        }
        else
        {
            printf("\nUtilizador ou NIF incorretos!\n");
        }

        break;
    }

    case 2:
    {
        int valido = 0;

        while (!valido)
        {
            printf("Nome de utilizador: ");
            gets_s(nome, sizeof(nome));

            if (existeUtilizador(nome))
            {
                printf("\nEsse utilizador ja existe!\n\n");
                continue;
            }

            printf("Email: ");
            gets_s(email, sizeof(email));

            if (existeEmail(email))
            {
                printf("\nEsse email ja esta registado!\n\n");
                continue;
            }

            printf("NIF: ");
            gets_s(nif, sizeof(nif));

            if (existeNIF(nif))
            {
                printf("\nEsse NIF ja se encontra registado!\n\n");
                continue;
            }

            criarUtilizador(nome, email, nif);
            valido = 1;
        }

        break;
    }

    default:
        printf("\nOpcao invalida!\n");
        break;
    }
}
