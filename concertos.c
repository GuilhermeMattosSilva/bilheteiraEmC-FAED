#include <stdio.h>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

extern SQLHDBC hDbc;

void listarConcertos()
{
    SQLHSTMT stmt;

    SQLAllocHandle(SQL_HANDLE_STMT,
        hDbc,
        &stmt);

    SQLExecDirectA(stmt,
        (SQLCHAR*)
        "SELECT id_show,"
        "show_name,"
        "location,"
        "price_ticket "
        "FROM dbo.Shows",
        SQL_NTS);

    int id;
    char nome[150];
    char local[150];
    double preco;

    printf("\n==============================\n");
    printf("CONCERTOS DISPONIVEIS\n");
    printf("==============================\n");

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
            nome,
            sizeof(nome),
            NULL);

        SQLGetData(stmt,
            3,
            SQL_C_CHAR,
            local,
            sizeof(local),
            NULL);

        SQLGetData(stmt,
            4,
            SQL_C_DOUBLE,
            &preco,
            0,
            NULL);

        printf("%d - %s (%s) %.2f€\n",
            id,
            nome,
            local,
            preco);
    }

    SQLFreeHandle(SQL_HANDLE_STMT,
        stmt);
}

int existeConcerto(int idShow)
{
    SQLHSTMT stmt;

    char sql[200];

    sprintf_s(sql,
        sizeof(sql),
        "SELECT COUNT(*) "
        "FROM dbo.Shows "
        "WHERE id_show=%d",
        idShow);

    SQLAllocHandle(SQL_HANDLE_STMT,
        hDbc,
        &stmt);

    SQLExecDirectA(stmt,
        (SQLCHAR*)sql,
        SQL_NTS);

    int total = 0;

    if (SQLFetch(stmt) == SQL_SUCCESS)
    {
        SQLGetData(stmt,
            1,
            SQL_C_LONG,
            &total,
            0,
            NULL);
    }

    SQLFreeHandle(SQL_HANDLE_STMT,
        stmt);

    return total;
}