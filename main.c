#include <stdio.h>
#include "basededados.h"

int main()
{
    if (ligarBD())
    {
        printf("Ligacao realizada com sucesso!\n");
    }
    else
    {
        printf("Erro ao ligar a base de dados!\n");
        return 1;
    }

    fecharBD();

    return 0;
}