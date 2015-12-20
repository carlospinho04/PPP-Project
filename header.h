/*-------------------------------------------------*/
/* Carlos Daniel de Sousa Pinho       2014208236   */
/* Dinis Coelho Marques               2014206409   */
/*-------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NAME_SIZE 75
#define BI_SIZE 8

/* ----- ESTRUTURAS ----- */

typedef struct{
	int dia, mes, ano, hora, min, sec;
}Data_Hora;

typedef struct{
	char nome[NAME_SIZE];        /*Nome*/
	int bi;                      /*Numero de BI*/
	int pul;                     /*Pulseira 0(por atribuir), 1(verde), 2(amarela), 3(vermelha)*/
	Data_Hora data;              /*Data e hora de inscrição*/
}Doente;

typedef struct lnode *List;
typedef struct lnode{
	Doente *info;
	List next;
}List_node;


/* ----- FUNÇÕES ----- */


/* atendimento.c */
void registo(List, List);
int confirma_nome(char *);
int confirma_bi(int, List, List);
void triagem(List, List, List, List, List);
void consultar_doente(List, List, List, List);

/* listas.c */
List cria_lista (void);
void insere_doente_fim(List, Doente *);
void insere_doente_inicio(List, Doente *);
void cancelar_doente(List, int);
void imprime_lista_pre_triagem(List);
void imprime_lista_pos_triagem(List);
int prioridade_doente(List, int);
int procura_doente(List, int);

/* ficheiros.c */
void verifica_ficheiros();
void insere_doente_fim_ficheiro(Doente *, char *);
void ficheiro_para_lista(List, List, char *);
void ficheiro_para_lista_global(List, List, List, List, List, char *);
void lista_para_ficheiro(List, char *);
int verifica_linha(Doente *, List, List);

