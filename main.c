/*-------------------------------------------------*/
/* Carlos Daniel de Sousa Pinho       2014208236   */
/* Dinis Coelho Marques               2014206409   */
/*-------------------------------------------------*/

#include "header.h"

/* Listas: Lista_global, Lista_espera , Lista_vermelha, Lista_amarela, Lista_verde   */

void clear_screen(){
	#ifdef WINDOWS
    	system("cls");
    #else
    	system("clear");
    #endif
}

void menu(List lglobal,List lespera,List lvermelha,List lamarela,List lverde){
	
	int escolha,bi,prioridade;

	printf("----- Serviço de Urgência Hospitalar ------ \n\n");
	printf("1-Introduzir novo doente à fila de espera para a triagem.\n");
	printf("2-Visualizar lista de espera para a triagem.\n");
	printf("3-Cancelar doente da lista de espera para a triagem.\n");
	printf("4-Atribuir prioridade(pulseira) ao próximo doente em espera.\n");
	printf("5-Visualizar lista global com as prioridades.\n");
	printf("6-Cancelar doente da lista de espera para a consulta.\n");
	printf("7-Visualizar lista de espera de doentes para a consulta.\n");
	printf("8-Próximo doente a ser atendido.\n\n");
	printf("0-Fechar Programa.\n");

	scanf("%d",&escolha);

	while(getchar()!='\n')
		escolha=-1;

	clear_screen();
	switch(escolha){
		case 1:
			registo(lespera,lglobal);
			clear_screen();
			break;

		case 2:
			if(lespera->next!=NULL){
				printf("Lista de espera para triagem:\n\n");
				imprime_lista_pre_triagem(lespera);
			}
			else{
				printf("Nao existem doentes na lista de espera.\n\n");
			}
			printf("Pressione ENTER para voltar ao menu.");
			while(getchar()!='\n');
			clear_screen();
			break;

		case 3:
			if(lespera->next!=NULL){
				printf("Introduza o numero de BI do paciente que quer cancelar:\n");
				do{
					scanf("%d",&bi);
					while(getchar()!='\n')
						bi=-1;
				}while(procura_doente(lespera,bi)!=1 && printf("Insira novamente o bi:\n"));
				cancelar_doente(lespera,bi);
				lista_para_ficheiro(lespera,"lespera.txt");
				clear_screen();
				printf("Doente cancelado com sucesso!\n\n");
			}
			else{
				printf("Nao existem doentes na lista de espera.\n\n");
			}
			printf("Pressione ENTER para voltar ao menu.");
			while(getchar()!='\n');
			clear_screen();
			break;
		case 4:
			if(lespera->next!=NULL){
				triagem(lglobal, lespera, lvermelha, lamarela, lverde);
				clear_screen();
			}
			else{
				printf("Nao existem doentes na lista de espera.\n\n");
				printf("Pressione ENTER para voltar ao menu.");
				while(getchar()!='\n');
				clear_screen();
			}
			break;

		case 5:
			if(lglobal->next!=NULL){
				printf("Lista global com as prioridades:\n\n");
				imprime_lista_pos_triagem(lglobal);
			}
			else{
				printf("Nao existem doentes na lista global.\n\n");
			}
			printf("Pressione ENTER para voltar ao menu.");
			while(getchar()!='\n');
			clear_screen();
			break;

		case 6:
			if(lglobal->next!=NULL){
				int pul;
				printf("Introduza o numero de BI do paciente que quer cancelar:");
				do{
					scanf("%d",&bi);
					while(getchar()!='\n')
						bi=-1;
				}while(procura_doente(lglobal,bi)!=1 && printf("Insira novamente o bi:\n"));

				pul=prioridade_doente(lglobal,bi);
								
				if(pul==1){
					cancelar_doente(lverde,bi);
					cancelar_doente(lglobal,bi);
					lista_para_ficheiro(lglobal,"lglobal.txt");
					clear_screen();
					printf("Doente cancelado com sucesso!\n\n");
				}
				else if(pul==2){
					cancelar_doente(lamarela,bi);
					cancelar_doente(lglobal,bi);
					lista_para_ficheiro(lglobal,"lglobal.txt");
					clear_screen();
					printf("Doente cancelado com sucesso!\n\n");
				}
				else if(pul==3){
					cancelar_doente(lvermelha,bi);
					cancelar_doente(lglobal,bi);
					lista_para_ficheiro(lglobal,"lglobal.txt");
					clear_screen();
					printf("Doente cancelado com sucesso!\n\n");
				}
				else{
					clear_screen();
					printf("Doente nao encontrado.\n");
				}
			}
			else{
				printf("Nao existem doentes na lista global.\n\n");
				printf("Pressione ENTER para voltar ao menu.");
				while(getchar()!='\n');
				clear_screen();
			}
			break;

		case 7:
			printf("Qual a lista de prioridade que deseja visualizar(Verde=1, Amarelo=2, Vermelho=3):");
			
			do{
				scanf("%d",&prioridade);
				while(getchar()!='\n')
					prioridade=-1;
			}while((prioridade<1 || prioridade >3) && printf("Insira novamente a prioridade:\n"));

			if (prioridade==1){
				if(lverde->next!=NULL){
					printf("Lista verde:\n");
					imprime_lista_pre_triagem(lverde);
				}
				else{
					printf("Nao existem doentes na lista verde.\n\n");
				}
			}
			else if (prioridade==2){
				if(lamarela->next!=NULL){
					printf("Lista amarela:\n");
					imprime_lista_pre_triagem(lamarela);
				}
				else{
					printf("Nao existem doentes na lista amarela.\n\n");
				}
			}
			else{
				if(lvermelha->next!=NULL){
					printf("Lista vermelha:\n");
					imprime_lista_pre_triagem(lvermelha);
				}
				else{
					printf("Nao existem doentes na lista vermelha.\n\n");
				}
			}
			printf("Pressione ENTER para voltar ao menu.");
			while(getchar()!='\n');
			clear_screen();
			break;

		case 8:
			consultar_doente(lvermelha,lamarela,lverde,lglobal);
			printf("Pressione ENTER para voltar ao menu.");
			while(getchar()!='\n');
			clear_screen();
			break;

		case 0:
			exit(0);
			break;
	}
	menu(lglobal,lespera,lvermelha,lamarela,lverde);
}



int main(){
	List lglobal, lespera, lvermelha, lamarela, lverde;
	
	lglobal=cria_lista();
	lespera=cria_lista();
	lvermelha=cria_lista();
	lamarela=cria_lista();
	lverde=cria_lista();

	verifica_ficheiros();
	ficheiro_para_lista(lespera,lglobal,"lespera.txt");
	ficheiro_para_lista_global(lespera,lglobal,lverde,lamarela,lvermelha,"lglobal.txt");
	menu(lglobal,lespera,lvermelha,lamarela,lverde);
}