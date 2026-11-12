#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

void menuAdmin();
void menuUtilizador();

int loginUtilizador(char nome[], char nif[]);
void criarUtilizador(char nome[], char email[], char nif[]);

int existeUtilizador(char nome[]);
int existeEmail(char email[]);
int existeNIF(char nif[]);

int obterRole(char nome[], char nif[], char role[]);

#endif