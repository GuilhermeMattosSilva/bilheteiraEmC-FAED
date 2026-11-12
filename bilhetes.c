#include <stdio.h>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

#include "concertos.h"

extern SQLHDBC hDbc;

void comprarBilhete(int idUser)
{
    SQLHSTMT stmt;

    int idShow;
    int idTipo;
    int quantidade;

    listarConcertos();

    printf("\nEscolha o ID do concerto: ");
    scanf_s("%d", &idShow);

    if (!existeConcerto(idShow))
    {
        printf("Concerto inexistente!\n");
        return;
    }

    printf("\nTipos de Bilhete:\n");

    SQLAllocHandle(SQL_HANDLE_STMT,
        hDbc,
        &stmt);

    SQLExecDirect(stmt,
        (SQLCHAR*)
        "SELECT id_type,"
        "description,"
        "discount_percentage "
        "FROM dbo.Type_tickets",
        SQL_NTS);

    int id;
    char descricao[100];
    double desconto;

    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        SQLGetData(stmt,
            1,
            SQL_C_LONG,
            &id,
            0,
            NULL);

        SQLGetData(stmt,
            2,
            SQL_C_CHAR,
            descricao,
            sizeof(descricao),
            NULL);

        SQLGetData(stmt,
            3,
            SQL_C_DOUBLE,
            &desconto,
            0,
            NULL);

        printf("%d - %s (%.2f%%)\n",
            id,
            descricao,
            desconto);
    }

    SQLFreeHandle(SQL_HANDLE_STMT,
        stmt);

    printf("\nTipo: ");
    scanf_s("%d", &idTipo);

    printf("Quantidade: ");
    scanf_s("%d", &quantidade);

    char sql[300];

    sprintf_s(sql,
        sizeof(sql),
        "INSERT INTO dbo.Tickets "
        "(id_user,id_show,id_type,quantity) "
        "VALUES(%d,%d,%d,%d)",
        idUser,
        idShow,
        idTipo,
        quantidade);

    SQLAllocHandle(SQL_HANDLE_STMT,
        hDbc,
        &stmt);

    SQLExecDirectA(
        stmt,
        (SQLCHAR*)sql,
        SQL_NTS);

    SQLFreeHandle(SQL_HANDLE_STMT,
        stmt);

    printf("\nCompra realizada com sucesso!\n");
}

void consultarBilhetes(int idUser)
{
    printf("\nConsultar bilhetes do utilizador %d\n",
        idUser);
}

void cancelarBilhete()
{
    printf("\nCancelar bilhete\n");
}