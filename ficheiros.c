/*-------------------------------------------------*/
/* Carlos Daniel de Sousa Pinho       2014208236   */
/* Dinis Coelho Marques               2014206409   */
/*-------------------------------------------------*/

#include "header.h"

void verifica_ficheiros(){
	if (access("lglobal.txt",F_OK)==-1){
    	FILE *f1;
    	f1=fopen("lglobal.txt","w");
    	fclose(f1);
	}
	if (access("lespera.txt",F_OK)==-1){
    	FILE *f2;
    	f2=fopen("lespera.txt","w");
    	fclose(f2);
	}
	if (access("contagem.txt",F_OK)==-1){
    	FILE *f3;
    	f3=fopen("contagem.txt","w");
    	fprintf(f3,"%d %d %d",0,0,0);
    	fclose(f3);
	}

}

void insere_doente_fim_ficheiro(Doente *d,char *fname){
	FILE *f;
	f=fopen(fname,"a");

	/*BI*/
	fprintf(f,"%d ",d->bi);
	/*DD/MM/AAAA HH:MM:SS*/
	fprintf(f,"%.2d/%.2d/%d %.2d:%.2d:%.2d ",d->data.dia,d->data.mes,d->data.ano,d->data.hora,d->data.min,d->data.sec);
	/*PULSEIRA*/
	fprintf(f,"%d ",d->pul);
	/*NOME*/
	fputs(d->nome,f);

	fclose(f);
}

void ficheiro_para_lista(List lespera,List lglobal, char *fname){
	FILE *f;
	f=fopen(fname,"r");
	int pos=0;
	while(fgetc(f) != EOF){
		fseek(f,pos,SEEK_SET);
		Doente *aux = malloc(sizeof(Doente));
		fscanf(f,"%d %d/%d/%d %d:%d:%d %d ",&aux->bi,&aux->data.dia,&aux->data.mes,&aux->data.ano,&aux->data.hora,&aux->data.min,&aux->data.sec,&aux->pul);
		fgets(aux->nome,NAME_SIZE,f);
		if (verifica_linha(aux,lglobal,lespera)==1)
			insere_doente_fim(lespera,aux);
		else{
			printf("Ficheiro corrompido, o programa ira encerrar. Por favor verifique o ficheiro %s.\n",fname);
			printf("Pressione ENTER para sair.");
			while(getchar()!='\n');
			exit(0);
		}
		pos=ftell(f);
	}
	fclose(f);
}

void ficheiro_para_lista_global(List lespera, List lglobal, List lverde, List lamarela, List lvermelha, char *fname){
	FILE *f;
	f=fopen(fname,"r");
	int pos=0;
	while(fgetc(f) != EOF){
		fseek(f,pos,SEEK_SET);
		Doente *aux = malloc(sizeof(Doente));
		fscanf(f,"%d %d/%d/%d %d:%d:%d %d ",&aux->bi,&aux->data.dia,&aux->data.mes,&aux->data.ano,&aux->data.hora,&aux->data.min,&aux->data.sec,&aux->pul);
		fgets(aux->nome,NAME_SIZE,f);
		if (verifica_linha(aux,lglobal,lespera)==1){
			insere_doente_fim(lglobal,aux);
			if (aux->pul==1)
				insere_doente_inicio(lverde,aux);
			else if(aux->pul==2)
				insere_doente_inicio(lamarela,aux);
			else
				insere_doente_inicio(lvermelha,aux);
		}
		else{
			printf("Ficheiro corrompido, o programa ira encerrar. Por favor verifique o ficheiro %s.\n",fname);
			printf("Pressione ENTER para sair.");
			while(getchar()!='\n');
			exit(0);
		}
		pos=ftell(f);
	}
	fclose(f);
}

void lista_para_ficheiro(List lista, char *fname){
	FILE *f;
	f=fopen(fname,"w");
	List ant,atual;
	ant=lista;
	atual=lista->next;
	while(atual!=NULL){
		fprintf(f,"%d %d/%d/%d %d:%d:%d %d %s",atual->info->bi,atual->info->data.dia,atual->info->data.mes,atual->info->data.ano,atual->info->data.hora,atual->info->data.min,atual->info->data.sec,atual->info->pul,atual->info->nome);
		ant=atual;
		atual=atual->next;
	}
	fclose(f);
}

int verifica_linha(Doente *d, List lglobal, List lespera){
	/*Testa BI*/
	int n=0,aux=d->bi;
	while(aux!=0){
		aux/=10;
		n++;
	}
	if (n!=BI_SIZE || procura_doente(lglobal,d->bi)==1 || procura_doente(lespera,d->bi)==1)
		return 0;

	/*Testa Data e Hora*/
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	int ano = t->tm_year+1900;
	if ( (d->data.dia<1 || d->data.dia>31) || (d->data.mes<1 || d->data.mes>12) || d->data.ano!=ano || (d->data.hora<0 || d->data.hora>23) || (d->data.min<0 || d->data.min>59) || (d->data.sec<0 || d->data.sec>59))
		return 0;

	/*Testa pulseira*/
	if (d->pul<0 || d->pul>3)
		return 0;

	/*Testa Nome*/
	char *nome=d->nome;
	while(*nome!='\n'){
		if((*nome>='a' && *nome<='z') || (*nome>='A' && *nome<='Z') || (*nome==' ')){
			nome++;
		}
		else{
			return 0;
		}
	}
	return 1;

}
