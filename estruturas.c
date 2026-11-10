#include <stdio.h>
#include "estruturas.h"

void menuAdmin()
{
    int opcao;

    do
    {
        printf("\n===== MENU ADMIN =====\n");
        printf("1 - Gerir Espetaculos\n");
        printf("2 - Gerir Utilizadores\n");
        printf("3 - Ver Bilhetes Vendidos\n");
        printf("4 - Ver Recibos\n");
        printf("0 - Logout\n");

        printf("Opcao: ");
        scanf_s("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Gestao de espetaculos\n");
            break;

        case 2:
            printf("Gestao de utilizadores\n");
            break;

        case 3:
            printf("Bilhetes vendidos\n");
            break;

        case 4:
            printf("Recibos\n");
            break;

        case 0:
            printf("Logout efetuado.\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);
}

void menuUtilizador()
{
    int opcao;

    do
    {
        printf("\n===== MENU UTILIZADOR =====\n");
        printf("1 - Ver Espetaculos\n");
        printf("2 - Comprar Bilhete\n");
        printf("3 - Os Meus Bilhetes\n");
        printf("4 - Os Meus Recibos\n");
        printf("0 - Logout\n");

        printf("Opcao: ");
        scanf_s("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Lista de espetaculos\n");
            break;

        case 2:
            printf("Comprar bilhete\n");
            break;

        case 3:
            printf("Os meus bilhetes\n");
            break;

        case 4:
            printf("Os meus recibos\n");
            break;

        case 0:
            printf("Logout efetuado.\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);
}