#include <stdio.h>
#include <string.h>
#include "estruturas.h"
#include "concertos.h"

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
            gerirConcerto();

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
 
void menuUtilizador(int idUser)
{
    int opcao;

    do
    {
        printf("\n");
        printf("=================================\n");
        printf("         MENU UTILIZADOR\n");
        printf("=================================\n");
        printf("1 - Ver Concertos\n");
        printf("2 - Comprar Bilhete\n");
        printf("3 - Consultar Bilhetes\n");
        printf("4 - Cancelar Bilhete\n");
        printf("5 - Consultar Faturas\n");
        printf("0 - Logout\n");

        printf("\nOpcao: ");
        scanf_s("%d", &opcao);

        switch (opcao)
        {
        case 1:
            listarConcertos();
            break;

        case 2:
            comprarBilhete(idUser);
            break;

        case 3:
            consultarBilhetes();
            break;

        case 4:
            cancelarBilhete();
            break;

        case 5:
            listarFaturas();
            break;

        case 0:
            printf("\nLogout efetuado.\n");
            break;

        default:
            printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);
}