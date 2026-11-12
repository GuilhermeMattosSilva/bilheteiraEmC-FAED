#include <stdio.h>

#include "basededados.h"
#include "utilizadores.h"

int main()
{
    if (!ligarBD())
    {
        printf("Erro ao ligar a base de dados.\n");
        return 1;
    }

    login();

    desligarBD();

    return 0;
}