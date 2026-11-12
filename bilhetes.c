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

    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &stmt);

    SQLExecDirectA(
        stmt,
        (SQLCHAR*)
        "SELECT id_type, description, discount_percentage "
        "FROM dbo.Type_tickets",
        SQL_NTS);

    int id;
    char descricao[100];
    double desconto = 0;

    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        SQLGetData(stmt, 1, SQL_C_LONG, &id, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR, descricao, sizeof(descricao), NULL);
        SQLGetData(stmt, 3, SQL_C_DOUBLE, &desconto, 0, NULL);

        printf("%d - %s (%.2f%%)\n",
            id,
            descricao,
            desconto);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    printf("\nTipo: ");
    scanf_s("%d", &idTipo);

    printf("Quantidade: ");
    scanf_s("%d", &quantidade);

    double preco = 0;
    desconto = 0;

    char sql[300];

    /* Buscar preço do concerto */
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &stmt);

    sprintf_s(sql,
        sizeof(sql),
        "SELECT price_ticket "
        "FROM dbo.Shows "
        "WHERE id_show = %d",
        idShow);

    SQLExecDirectA(stmt, (SQLCHAR*)sql, SQL_NTS);

    if (SQLFetch(stmt) == SQL_SUCCESS)
    {
        SQLGetData(stmt,
            1,
            SQL_C_DOUBLE,
            &preco,
            0,
            NULL);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* Buscar desconto do tipo */
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &stmt);

    sprintf_s(sql,
        sizeof(sql),
        "SELECT discount_percentage "
        "FROM dbo.Type_tickets "
        "WHERE id_type = %d",
        idTipo);

    SQLExecDirectA(stmt, (SQLCHAR*)sql, SQL_NTS);

    if (SQLFetch(stmt) == SQL_SUCCESS)
    {
        SQLGetData(stmt,
            1,
            SQL_C_DOUBLE,
            &desconto,
            0,
            NULL);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    double subtotal = preco * quantidade;
    double valorDesconto = subtotal * (desconto / 100.0);
    double total = subtotal - valorDesconto;

    printf("\n==============================");
    printf("\nRESUMO DA COMPRA");
    printf("\n==============================");
    printf("\nPreco unitario : %.2f EUR", preco);
    printf("\nQuantidade     : %d", quantidade);
    printf("\nSubtotal       : %.2f EUR", subtotal);
    printf("\nDesconto       : %.2f%%", desconto);
    printf("\nValor desconto : %.2f EUR", valorDesconto);
    printf("\nTOTAL          : %.2f EUR", total);
    printf("\n==============================\n");

    char confirmar;

    printf("\nConfirmar compra? (S/N): ");
    scanf_s(" %c", &confirmar, 1);

    if (confirmar != 'S' &&
        confirmar != 's')
    {
        printf("\nCompra cancelada!\n");
        return;
    }

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

    SQLRETURN ret =
        SQLExecDirectA(
            stmt,
            (SQLCHAR*)sql,
            SQL_NTS);

    if (!SQL_SUCCEEDED(ret))
    {
        SQLCHAR sqlState[6];
        SQLCHAR message[256];
        SQLINTEGER nativeError;
        SQLSMALLINT textLength;

        SQLGetDiagRecA(
            SQL_HANDLE_STMT,
            stmt,
            1,
            sqlState,
            &nativeError,
            message,
            sizeof(message),
            &textLength);

    }
    else
    {
        printf("\nCompra realizada com sucesso!\n");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
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