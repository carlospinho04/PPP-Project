/*-------------------------------------------------*/
/* Carlos Daniel de Sousa Pinho       2014208236   */
/* Dinis Coelho Marques               2014206409   */
/*-------------------------------------------------*/

#include "header.h"

List cria_lista (void){
	List aux;
	aux = (List) malloc (sizeof (List_node));
	if (aux != NULL) {
		aux->next = NULL;
	}
	return aux;
}

void insere_doente_fim(List lista, Doente *it){
	List no, ant, atual;
	atual=lista->next;
	ant=lista;
	no = (List) malloc (sizeof (List_node));
	no->info = malloc(sizeof(Doente));
	while (atual != NULL){
		ant = atual;
		atual = atual->next;
	}
	if (no!=NULL){
		no->info=it;
		no->next = NULL;
		ant->next = no;
	}
}

void insere_doente_inicio(List lista, Doente *it){
	List no;
	List anterior, atual;
	no = (List) malloc (sizeof (List_node));
	no->info = malloc(sizeof(Doente));
	
	atual=lista->next;
	anterior=lista;
    
    if (no!=NULL){
		no->info=it;
		no->next=atual;
		anterior->next=no;
	}
}

void cancelar_doente(List lista, int bi){
	List atual=lista->next;
	List anterior=lista;
	while(atual!=NULL){
		if(atual->info->bi == bi){
			anterior->next=atual->next;
			free(atual);
			break;
		}
		anterior=atual;
		atual=atual->next;
	}
}

void imprime_lista_pre_triagem(List lista){
	List l = lista->next;
	while (l){
		printf("Nome do paciente:%s",l->info->nome);
		printf("Bi do paciente:%d\n",l->info->bi);
		printf("Data de inscricao:%.2d/%.2d/%d\t",l->info->data.dia,l->info->data.mes,l->info->data.ano);
		printf("Hora de inscricao:%.2d:%.2d:%.2d\n\n",l->info->data.hora,l->info->data.min,l->info->data.sec);
		l=l->next;
	}
}

void imprime_lista_pos_triagem(List lista){
	List l = lista->next;
	while (l){
		printf("Nome do paciente:%s",l->info->nome);
		printf("Bi do paciente:%d\n",l->info->bi);
		printf("Data de inscricao:%.2d/%.2d/%d\t",l->info->data.dia,l->info->data.mes,l->info->data.ano);
		printf("Hora de inscricao:%.2d:%.2d:%.2d\n",l->info->data.hora,l->info->data.min,l->info->data.sec);
		int p = l->info->pul;
		switch(p){
			case 1:
				printf("Pulseira Verde.\n\n");
				break;
			case 2:
				printf("Pulseira Amarela.\n\n");
				break;
			case 3:
				printf("Pulseira Vermelha.\n\n");
				break;
		}
		l=l->next;
	}
}

int prioridade_doente(List lista, int bi){
	List atual=lista->next;
	List anterior=lista;
	while(atual!=NULL){
		if(atual->info->bi == bi){
			return atual->info->pul;
		}
		anterior=atual;
		atual=atual->next;
	}
	return 0;
}

int procura_doente(List lista, int bi){
	List atual=lista->next;
	List anterior=lista;
	while(atual!=NULL){
		if(atual->info->bi == bi){
			return 1;
		}
		anterior=atual;
		atual=atual->next;
	}
	return 0;
}