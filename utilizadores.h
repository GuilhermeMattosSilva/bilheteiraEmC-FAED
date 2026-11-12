#ifndef UTILIZADORES_H
#define UTILIZADORES_H

void login();

int existeUtilizador(char nome[]);
int existeNIF(char nif[]);
int existeEmail(char email[]);

int loginUtilizador(char nome[], char nif[]);

void criarUtilizador(char nome[], char email[], char nif[]);

int obterRole(char nome[], char nif[], char role[]);

/* NOVO */
int obterIdUtilizador(char nome[], char nif[]);

/* MENUS */
void menuAdmin(int idUser);
void menuUtilizador(int idUser);

#endif