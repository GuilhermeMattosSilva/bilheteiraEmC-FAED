#ifndef BASEDEDADOS_H
#define BASEDEDADOS_H

#include <windows.h>
#include <sql.h>
#include <sqlext.h>

extern SQLHENV hEnv;
extern SQLHDBC hDbc;

int ligarBD();
void desligarBD();

#endif