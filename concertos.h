#ifndef CONCERTOS_H
#define CONCERTOS_H

void listarConcertos();
int existeConcerto(int idShow);
void criacaoConcerto(char show_name[], char location[], char show_date[], float price_ticket);
void gerirConcerto();

#endif