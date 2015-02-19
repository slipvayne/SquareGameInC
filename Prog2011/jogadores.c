#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//====Headers====
#include "jogadores.h"
#include "jogo.h"
#include "outros.h"


// ========== INSERIR JOGADOR ==========
pjogador insere_jogador(pjogador p,int totaljogadores)
{
pjogador novo;

	if((novo=(pjogador)malloc(sizeof(jogador)))==NULL){ // aloca espaço para um novo registo 
	printf("Erro na alocacao de memoria\n"); // novo=(pjogador)malloc(sizeof(jogador)))==NULL
	}else{

	preenche(novo,totaljogadores,p);       //chama funcao preenche para a nova estrutura da lista

	novo->prox=p;                       //o 1º registo dessa lista vai passar a ser apontado pelo prox do novo registo alocado
	p=novo;                            // o novo registo vai ser inserido no ínicio da lista

	}
gravar_lista(p);                     //grava a lista para o ficheiro (outros.c)
return p;                           //retorna o ponteiro para o inicio da lista
}

pjogador insere_convidado(pjogador p,int totaljogadores)
{
	pjogador novo;

	if((novo=(pjogador)malloc(sizeof(jogador)))==NULL){ // aloca espaço para um novo registo 
	printf("Erro na alocacao de memoria\n"); // novo=(pjogador)malloc(sizeof(jogador)))==NULL
	}else{

	novo->id=totaljogadores;
	strcpy(novo->nickname,"Convidado");
	strcpy(novo->nome,"Conta Convidado");
	novo->vitorias=0;
	novo->derrotas=0;

	//chama funcao preenche para a nova estrutura da lista

	novo->prox=p;                       //o 1º registo dessa lista vai passar a ser apontado pelo prox do novo registo alocado
	p=novo;                            // o novo registo vai ser inserido no ínicio da lista

	}
                    //grava a lista para o ficheiro (outros.c)
return p;  

}


//======== PREENCHE INFO JOGADOR =========
void preenche(pjogador a,int totaljogadores,pjogador p) //ponteiro para p só é necessario para verificar o nickname
{
	char password[15],password2[15];   //somente é necessário para comparar as passwords (repita password) e nickname
	char nickname[25];
	a->id=totaljogadores;             //automaticamente associa um ID (ultimo consoante o nº de registados(vai incrementando))

clrscr();

    printf(" :::::::::::::::::::::::::::::\n");
	printf(" ::                         ::\n");
	printf(" ::  REGISTAR NOVO JOGADOR  ::\n");
	printf(" ::                         ::\n");
	printf(" :::::::::::::::::::::::::::::\n\n");

printf("\n\n Introduza o seu Nome: ");
gets(a->nome);

do{
printf("\n Introduza um Nickname: ");
gets(nickname);
if(verifica_nickname(p,nickname)==0) { printf("\n Ja existe um nickname com esse nome, pff escolha outro!\n\n"); }
}while( verifica_nickname(p,nickname)==0 ); //a funcao devolve 0 se existir um nickname identico, caso contrario retorna 1
strcpy(a->nickname,nickname);

do{
printf("\n Introduza a Password: ");
gets(password);

printf("\n Repita a Password: ");
gets(password2);

if (strcmp(password2,password)!=0) //o strcmp devolve 0 se as passwords coincidirem (isto é, 0 caracteres diferentes)
{
	printf("\n\n\tAs passwords nao coincidem! Tente Novamente...\n\n");
}

}while( strcmp(password2,password)!=0 );

strcpy(a->password,password);
a->vitorias=0;
a->derrotas=0;

printf("\n\n Bem-vindo %s ! A sua conta foi criada com sucesso! [ID: %d] \n\n",a->nome,a->id);
system("pause");
}


//============= VERIFICA NICKNAME ===========
int verifica_nickname(pjogador p,char *nickname)
{

	while(p!=NULL)
	{
		if(strcmp(p->nickname, nickname) == 0)
		{
		return 0; //existe igual
		}
		p=p->prox;
	
	}
return 1; //nao existe
}

//============= CONSULTA DE JOGADORES ===========
void mostra_info(pjogador p) //recebe ponteiro para o inicio da lista de jogadores
{
	printf("\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
while(p!=NULL)
{	printf("\n\n            [ ID:%d ] Nickname: %s                           ",p->id,p->nickname);
	printf("\n   Nome: %s  |  Vitorias:%d / Derrotas:%d                    \n",p->nome,p->vitorias,p->derrotas);
if(p->prox!=NULL)
   {printf("\n::::::::::::::::::::::::::::::::::::::::::::[    MAIS   ]:::::\n\n");}else
   {printf("\n::::::::::::::::::::::::::::::::::::::::::::[    FIM    ]:::::\n\n\n");}
	
system("pause");
p=p->prox;
}}

//==========CONSULTA UM JOGADOR SOMENTE============

void mostra_info2(pjogador p) //somente imprime no ecra o jogador 
{
	clrscr();
	printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
	printf("\n\n            [ ID:%d ] Nickname: %s                            ",p->id,p->nickname);
	printf("\n   Nome: %s  |  Vitorias:%d / Derrotas:%d                      \n\n",p->nome,p->vitorias,p->derrotas);
	printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
}

// ========= PESQUISA DE JOGADORES =========

void procura_jogador(pjogador p,int opcao) //Opcao-> 1-Pesquisa por ID | 2-Pesquisa por Nome | 3-Pesquisa por Nickname
{
	int id;
    char nome[50];
	char nickname[25];

	clrscr();

if(opcao==1) //ID
{
	printf("\n\n\tID a pesquisar: ");
	scanf("%d",&id);

	while(p!=NULL && p->id!=id)
	p=p->prox;
	if(p!=NULL){ 
	mostra_info2(p);
	}else{ printf("\n\n\tJogador inexistente!\n\n");}

}

if(opcao==2) // Nome
{
	printf("\n\n\tNome a pesquisar: ");  // CASE SENSITIVE
	getchar(); gets(nome);

	while(p!=NULL && strcmp(p->nome, nome) != 0)
	p=p->prox;
	if(p!=NULL){ 
	mostra_info2(p);
	}else{ printf("\n\nJogador inexistente!\n\n");}
}

if(opcao==3) // Nickname
{
	printf("\n\n\tNickname a pesquisar: ");  // CASE SENSITIVE
	getchar(); gets(nickname);

	while(p!=NULL && strcmp(p->nickname, nickname) != 0)
	p=p->prox;
	if(p!=NULL){
	mostra_info2(p);
	}else{ printf("\n\nJogador inexistente!\n\n");}
}

}

// ========== ELIMINA JOGADORES DA LISTA ===========
pjogador elimina(pjogador p, int id)           //recebe ponteiro para o inicio da lista e o id do player a eliminar
{
pjogador actual, anterior = NULL;              //auxiliares, o anterior é inicializado a null caso esteja no inicio da lista

actual = p;

while(actual != NULL && actual->id != id)
{
	anterior = actual;
	actual = actual->prox;
}
	if(actual == NULL)                          //no nao encontrado
	{
		printf("\n\nNenhum jogador com esse ID encontrado!\n\n");
		system("pause");
		return p;
	}
	if(anterior == NULL)                      //primeiro no da lista
	{
		p = actual->prox;
	}else{                                    //caso n esteja no inicio da lista.. esta pelo meio..
			anterior->prox = actual->prox;
		 }
	free(actual);                              //liberta da memoria o registo desse jogador
	printf("\n\nJogador com o ID %d eliminado com sucesso!\n\n",id);
	system("pause");
	return p;	
}

// ========== DESTRUIR LISTA ========= (utilizado na estatistica/ordenacao)
void liberta_lista(pjogador p) //sera usado na funcao de ordenacao 
{                              //(nessa funcao cria uma lista nova e ordena e liberta a anterior(usando esta f.))
	pjogador aux;

	while(p!=NULL)
	{
	aux=p;
	p=p->prox;
	free(aux);
	}
}