#include "basededados.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>

SQLHENV hEnv;
SQLHDBC hDbc;

int ligarBD()
{
    SQLRETURN ret;

    SQLAllocHandle(SQL_HANDLE_ENV,
        SQL_NULL_HANDLE,
        &hEnv);

    SQLSetEnvAttr(hEnv,
        SQL_ATTR_ODBC_VERSION,
        (void*)SQL_OV_ODBC3,
        0);

    SQLAllocHandle(SQL_HANDLE_DBC,
        hEnv,
        &hDbc);

    ret = SQLDriverConnectA(
        hDbc,
        NULL,
        (SQLCHAR*)
        "DRIVER={ODBC Driver 18 for SQL Server};"
        "SERVER=localhost\\SQLEXPRESS;"
        "DATABASE=Bilheteira;"
        "Trusted_Connection=yes;"
        "TrustServerCertificate=yes;",
        SQL_NTS,
        NULL,
        0,
        NULL,
        SQL_DRIVER_COMPLETE
    );

    return SQL_SUCCEEDED(ret);
}

void desligarBD()
{
    SQLDisconnect(hDbc);

    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}