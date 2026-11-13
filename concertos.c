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
void criacaoConcerto(char show_name[], char location[], char show_date[], float price_ticket) {
        SQLHSTMT hStmt;
        SQLRETURN ret;

        char query[512];

        sprintf_s(query, sizeof(query),
            "INSERT INTO dbo.Shows(show_name, location, show_date, price_ticket) "
            "VALUES('%s', '%s', '%s', '%f')",
            show_name,
            location,
            show_date,
            price_ticket);

        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        ret = SQLExecDirectA(hStmt, (SQLCHAR*)query, SQL_NTS);

        if (SQL_SUCCEEDED(ret))
        {
            printf("\nConcerto criado!\n");
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


void gerirConcerto() {
    int opcao;

    printf("\n===== GERIR CONCERTOS =====\n");
    printf("1 - Criar concerto\n");
    printf("2 - Cancelar concerto\n");
    printf("Opcao: ");

    if (scanf_s("%d", &opcao) != 1) {
        printf("Erro: Opcao invalida!\n");

        while (getchar() != '\n');
        return;
    }

    switch (opcao) {

    case 1: {
        char show_name[100];
        char location[100];
        char show_date[30];
        float price_ticket;

        printf("\n--- Criar Concerto ---\n");

        while (getchar() != '\n');

        printf("Nome do concerto: ");
        if (gets_s(show_name, sizeof(show_name)) == NULL ||
            strlen(show_name) == 0) {

            printf("Erro: Nome do concerto invalido!\n");
            break;
        }

        printf("Localizacao: ");
        if (gets_s(location, sizeof(location)) == NULL ||
            strlen(location) == 0) {

            printf("Erro: Localizacao invalida!\n");
            break;
        }

        printf("Data e horario (YYYY-MM-DD HH:MM): ");
        if (gets_s(show_date, sizeof(show_date)) == NULL ||
            strlen(show_date) == 0) {

            printf("Erro: Data ou horario invalido!\n");
            break;
        }

        printf("Preco do bilhete: ");
        if (scanf_s("%f", &price_ticket) != 1) {

            printf("Erro: Preco invalido!\n");

            while (getchar() != '\n');
            break;
        }

        while (getchar() != '\n');

        if (price_ticket <= 0) {
            printf("Erro: O preco deve ser superior a zero!\n");
        }
        else {
            criacaoConcerto(
                show_name,
                location,
                show_date,
                price_ticket
            );
        }

        break;
    }

    case 2:
        printf("Cancelar concerto\n");
        break;

    default:
        printf("Opcao invalida!\n");
        break;
    }
}
