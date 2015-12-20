/*-------------------------------------------------*/
/* Carlos Daniel de Sousa Pinho       2014208236   */
/* Dinis Coelho Marques               2014206409   */
/*-------------------------------------------------*/

#include "header.h"

void registo(List lespera, List lglobal){
	Doente *novo_doente = malloc(sizeof(Doente));

	printf("Insira nome:\n");
	do{
		fgets(novo_doente->nome,NAME_SIZE,stdin);
	}while(confirma_nome(novo_doente->nome)!=1);

	printf("Insira o bi:\n");
	do{
		scanf("%d",&novo_doente->bi);

		while(getchar()!='\n')
			novo_doente->bi=0;

	}while(confirma_bi(novo_doente->bi,lespera,lglobal)!=1);

	/* Data do sistema no momento da inscrição */
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	novo_doente->data.dia = t->tm_mday;
	novo_doente->data.mes = t->tm_mon+1;
	novo_doente->data.ano = t->tm_year+1900;
	novo_doente->data.hora = t->tm_hour;
	novo_doente->data.min = t->tm_min;
	novo_doente->data.sec = t->tm_sec;

	novo_doente->pul=0;

	insere_doente_fim(lespera,novo_doente);
	insere_doente_fim_ficheiro(novo_doente,"lespera.txt");
}

int confirma_nome(char *nome){
	int i=0,spaces=0;
	if(*nome == ' '){
		printf("Nome invalido, insira novamente o nome:\n");
		return 0;
	}
	while(*nome!='\n'){
		if((*nome>='a' && *nome<='z') || (*nome>='A' && *nome<='Z') || (*nome==' ')){
			if (*nome==' ')
				spaces++;
			nome++;
			i++;
		}
		else{
			printf("Nome invalido, insira novamente o nome:\n");
			return 0;
		}
	}
	if (i==0 || i==spaces){
		printf("Nome invalido, insira novamente o nome:\n");
		return 0;
	}
	else
		return 1;
}

int confirma_bi(int bi,List lespera,List lglobal){
	int n=0,aux=bi;
	while(aux!=0){
		aux/=10;
		n++;
	}
	if (n==BI_SIZE){
		int confirma_espera, confirma_global;
		confirma_global=procura_doente(lglobal,bi);
		confirma_espera=procura_doente(lespera,bi);
		if(confirma_espera==1 || confirma_global==1){
			printf("BI ja registado, insira novamente o bi:\n");
			return 0;
		}
		else
			return 1;
	}
	else{
		printf("BI invalido, insira novamente o bi:\n");
		return 0;
	}
}


void triagem(List lglobal,List  lespera, List lvermelha, List lamarela, List lverde){
	int p;
	List doente_na_triagem=lespera->next;
	printf("Pulseiras:\n");
	printf("Verde=1  |  Amarela=2  |  Vermelha=3\n");
	do{
		printf("Qual a prioridade que pretende atribuir ao doente %s(%d)?",doente_na_triagem->info->nome,doente_na_triagem->info->bi);
		scanf("%d",&p);
		
		while(getchar()!='\n')
			p=0;

	}while((p>3 || p<1));
	/* Inserir doente na lista global(os mais recentes primeiro)*/
	doente_na_triagem->info->pul=p;
	insere_doente_inicio(lglobal,doente_na_triagem->info);

	lista_para_ficheiro(lglobal,"lglobal.txt");

	/* VERDE */
	if (p==1){
		insere_doente_fim(lverde,lglobal->next->info);
	}
	/* AMARELA */
	else if (p==2){
		insere_doente_fim(lamarela,lglobal->next->info);
	}
	/* VERMELHA */
	else{
		insere_doente_fim(lvermelha,lglobal->next->info);
	}
	cancelar_doente(lespera,doente_na_triagem->info->bi);

	lista_para_ficheiro(lespera,"lespera.txt");
}


void consultar_doente(List lvermelha,List lamarela,List lverde,List lglobal){
	FILE *f;
	f=fopen("contagem.txt","r");
	int nvermelho,namarelo,nvermelho_aux;
	fscanf(f,"%d %d %d",&nvermelho,&namarelo,&nvermelho_aux);
	if((nvermelho<0 || nvermelho >3) && (namarelo<0 || namarelo>5) && (nvermelho_aux<0 || nvermelho_aux>15) ){
		printf("Ficheiro corrompido, o programa ira encerrar. Por favor verifique o ficheiro contagem.txt.\n");
		printf("Pressione ENTER para sair.");
		while(getchar()!='\n');
		exit(0);
	}
	fclose(f);

	if(lvermelha->next!=NULL || lamarela->next!=NULL || lverde->next!=NULL){
		if(lverde->next!=NULL && (namarelo==5 || (nvermelho_aux==15 && lamarela->next==NULL) || (lamarela->next==NULL && lvermelha->next==NULL))){
			printf("A proxima pessoa a ser atendida e portadora de pulseira verde, com o numero de BI:%d e Nome:%s\n",lverde->next->info->bi,lverde->next->info->nome);
			
			cancelar_doente(lglobal,lverde->next->info->bi);
			lista_para_ficheiro(lglobal,"lglobal.txt");
			
			cancelar_doente(lverde,lverde->next->info->bi);
			
			namarelo=0;
			nvermelho=0;
			nvermelho_aux=0;
		}

		else if(lamarela->next!=NULL && ((namarelo<5 && nvermelho==3) || (namarelo<5 && lvermelha->next==NULL) || (lverde->next==NULL && lvermelha->next==NULL))){
			printf("A proxima pessoa a ser atendida e portadora de pulseira amarela, com o numero de BI:%d e Nome:%s\n",lamarela->next->info->bi,lamarela->next->info->nome);
				
			cancelar_doente(lglobal,lamarela->next->info->bi);
			lista_para_ficheiro(lglobal,"lglobal.txt");
				
			cancelar_doente(lamarela,lamarela->next->info->bi);
				
			if(namarelo<5){
				namarelo++;
				nvermelho=0;
			}
			else{
				namarelo=1;
				nvermelho=0;
			}
		}
		
		else{
			printf("A proxima pessoa a ser atendida e portadora de pulseira vermelha, com o numero de BI:%d e Nome:%s\n",lvermelha->next->info->bi,lvermelha->next->info->nome);
			
			cancelar_doente(lglobal,lvermelha->next->info->bi);
			lista_para_ficheiro(lglobal,"lglobal.txt");
			
			cancelar_doente(lvermelha,lvermelha->next->info->bi);
			
			if(nvermelho < 3 && nvermelho_aux<15){
				nvermelho++;
				nvermelho_aux++;
			}
			else{
				nvermelho=1;
				nvermelho_aux=1;
			}
			if(namarelo==5)
				namarelo=0;
		}
	}
	else
		printf("Não existem doentes para consulta.\n\n");

	f=fopen("contagem.txt","w");
	fprintf(f,"%d %d %d",nvermelho,namarelo,nvermelho_aux);
	fclose(f);
}