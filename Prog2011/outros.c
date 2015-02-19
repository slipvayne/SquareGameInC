#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//====Headers====
#include "jogadores.h"
#include "jogo.h"
#include "outros.h"


//======GRAVAR LISTA DE JOGADORES PARA FICHEIRO =====

void gravar_lista(pjogador p){              //recebe uma copia do ponteiro para estrutura jogadores
	
	FILE *f;
	f = fopen("jogadores_backup.dat","wb"); //abre o ficheiro binario para escrita
	while(p!=NULL){                         //enquanto a lista nao chegar ao fim
		fwrite(p, sizeof(jogador),1,f);     //grava para o ficheiro a informaçao apontado por p (esse no)
		p=p->prox;                          //p toma o valor apontado por p->prox (proximo nó)
	}
	fclose(f);		                        //fecha o ficheiro
}


//======GRAVAR LISTA DE JOGOS PARA FICHEIRO =====

void gravar_jogo(pgravarjogo p){                  //recebe uma copia do ponteiro para estrutura gravarjogo

	pjogadas aux;  //ponteiro auxiliar

	FILE *f;
	f = fopen("jogo_backup.dat","wb");           //abre o ficheiro binario de jogos para escrita
	while(p!=NULL){                             //enquanto a lista nao chegar ao fim
		fwrite(p, sizeof(gravarjogo),1,f);      //grava para ficheiro a informacao do no da estrutura gravarjogo
		fwrite(&p->jogadas,sizeof(int),1,f);    //grava para o ficheiro o numero de jogadas tambem (inteiro)
		aux=p->jlista;                         //o ponteiro auxiliar toma o valor inicial para a lista de jogadas  
		while(p->jlista!=NULL)                 //enquanto a lista de jogadas nao atingir o final (null)
		{
		fwrite(p->jlista, sizeof(jogadas),1,f);  //grava para o ficheiro as varias jogadas desse jogo
		p->jlista=p->jlista->prox;               //p->jlista toma o valor apontado por p->jlista->prox (proximo nó)    
		} 
		p->jlista=aux;                           //quando acaba de gravar as jogadas todas desse jogo é necessario repor o ponteiro inicial da lista
		p=p->prox;                              //passa para o proximo no de jogos enquanto nao for NULL

	}

		fclose(f);
}


//======RECUPERAR LISTA DE JOGADORES PARA MEMORIA =====

pjogador recuperar_lista(pjogador p,int *totaljogadores){

	FILE *f;
	jogador aux;
	pjogador novo;

	f = fopen("jogadores_backup.dat", "rb");                   //abre ficheiro binario para leitura

	if(f != NULL){                                            //se nao ocorrer problemas ao abrir o ficheiro..
		while(fread(&aux, sizeof(jogador), 1, f) == 1)        // enquanto for lido 1 elemento (de cada vez) para aux
		{	
		if((novo=(pjogador)malloc(sizeof(jogador)))==NULL){       // aloca espaço para novo
		printf("Erro na alocacao de memoria\n");
	}else{
			*novo=aux;                                        //novo(anteriormente alocado) toma o valor de aux

			novo->prox=p;                                    //como os novos nós sao adicionados no inicio da lista novo->prox vai ficar a pontar para o no anterior
			p=novo;                                         //o novo nó alocado será entao apontado por p(inicio da lista)

			++*totaljogadores;		                       //incrementa o total de jogadores (pointeiro->altera na variavel alocada no main)				
		}
		}
		fclose(f);
		return p;                                           //retorna ponteiro para inicio da lista
	}else
		printf("Erro ao abrir o ficheiro jogadores_backup.dat\n");
	    f = fopen("jogadores_backup.dat","wb"); //se nao houver ficheiro, criar
	fclose(f);

	return NULL; //caso nao haja o ficheiro, retorna NULL na mesma (como se a lista estiver vazia)
	
}


//======RECUPERAR LISTA DE JOGOS PARA MEMORIA =====
pgravarjogo recuperar_jogos(pgravarjogo p){

	FILE *f;
	gravarjogo aux;	
	pgravarjogo novo;
	jogadas aux2;
	pjogadas novo2,aux3;
	int i,jogadast;

	
	f = fopen("jogo_backup.dat", "rb");                              //abre ficheiro binario para leitura

	if(f != NULL){                                                   //se nao ocorrer problemas ao abrir o ficheiro..     
		while(fread(&aux, sizeof(gravarjogo), 1, f) == 1)            // enquanto for lido 1 elemento (de cada vez) para aux
		{	
		if((novo=(pgravarjogo)malloc(sizeof(gravarjogo)))==NULL){ 
		printf("Erro na alocacao de memoria\n");
	}else{
		    *novo=aux;                                               //novo(anteriormente alocado) recebe a informação contida em aux
	    	novo->jlista=NULL;                                       //a lista de jogadas no inicio esta vazia
			fread(&jogadast, sizeof(int), 1, f);                      //lê o numero de jogadas do ficheiro
			
		for(i=0;i<jogadast-1;i++)                                  //enquanto a var 'i' é menor que o numero de jogadas, incrementa i
		{
			fread(&aux2,sizeof(jogadas),1,f);                      //le a jogada desse nó
		if((novo2=(pjogadas)malloc(sizeof(jogadas)))==NULL){      //aloca memoria para um nó
			printf("Erro na alocacao de memoria\n");
		}else{

			*novo2 =aux2;			                         //novo2, anteriormente alocado recebe a informacao de aux2 (jogada lida)

	   if(novo->jlista==NULL){                             //se a lista de jogadas estiver vazia , isto é, novo->jlista está NULL
				novo->jlista = novo2;                     //ponteiro para a lista de jogadas - novo->jlista toma o endereço de novo2
				novo->jlista->prox=NULL;			     //o proximo no (prox) aponta para null
			}else{
					                                    //convém que o primeiro nó da lista seja a primeira jogada:
			aux3 = novo->jlista;                       //daí que os nós vao ser inseridos para o final da lista
			                                           //para tal é necessário usar uma var auxiliar com a posicao inicial da lista para nao ser alterada

			while(aux3->prox !=NULL)                  //enquanto aux3 for diferente de NULL / percorrer a lista até ao final..
			{ aux3 = aux3->prox; }
			aux3->prox = novo2;                       //aux3 é o ultimo nó agora, aux3->prox vai entao apontar para o novo nó (novo2)
			novo2->prox = NULL; 	                  //o novo nó (novo2->prox) vai apontar para NULL (ultimo da lista)
						
		}}}
		   
			novo->prox=p;                            //nao faz questao se o nó de jogos é inserido no inicio ou fim, opta-se por colocar no inicio
			p=novo;                                  //o inicio da lista fica a apontar para o novo no de jogos
		}
		//depois de ler um jogo e as suas jogadas, passa para o um proximo jogo se houver
		}
        fclose(f);                                   
		return p;
	}else
		printf("Erro ao abrir o ficheiro jogo_backup.dat\n");
      	f = fopen("jogo_backup.dat","wb");         //se nao houver ficheiro, cria
	fclose(f);
	return NULL;         //caso nao haja o ficheiro, retorna NULL na mesma (como se a lista estiver vazia)   
	
}

char geracodigo(char codigo[6])
{
	int i,aleatorio; 
    
	for(i=0;i<=4;i++)
	{
	aleatorio=(rand() % 3); //gera um numero entre 0 e 2 (que vai decidir se vai ser um numero ou letra)

	if(aleatorio==0)
	{
		codigo[i] = ((rand() % 8)+48); //um numero do codigo ascii entre 0-9 // +48 ASCII 
	}
	if(aleatorio==1)
	{
		codigo[i]  = ((rand() % 25)+65); // letra maiscula A->Z
	}
	if(aleatorio==2)
	{
		codigo[i] = ((rand() % 25)+97); // letra minuscula a-z
	}

	}
	codigo[5]='\0';	//é necessario 'fechar' a string..

	return *codigo;
}


int loginjogadores2(pjogador p) //alterar conta
{
	char nickname[50],password[50];
	int opcao;
	    
	    clrscr();
	    printf("\n\tLogin: ([0]-Sair)\n\n Introduza o seu NICKNAME: ");
		gets(nickname);
		if(nickname[0]=='0') { return 1; }
		printf("\n Introduza a sua PASSWORD: ");
		gets(password);

		while(p!=NULL && strcmp(p->nickname, nickname) != 0) //enquanto p for diferente de NULL e o nickname n coincidir..
		p=p->prox;
		if(p!=NULL){ //encontrou um jogador com esse nickname e nao chegou ao final da lista
			if(strcmp(p->password, password)==0) //confirmar se as passwords coincidem
			{
				clrscr();
	printf("\n\n\n\n:::[ DADOS DA SUA CONTA: ]:::::::::::::[ ID:%d ]:::::::::::::::::::::::\n\n",p->id);
	printf("\n [1]-> Nickname: %s\n\n [2]-> Nome: %s\n\n [3]-> Password: ****** \n\n",p->nickname,p->nome);
	printf("\n\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
		
				do{
				printf("\n\n  Qual o campo a alterar ([1] | [2] | [3] | [0]-Sair): ");
				scanf("%d",&opcao);
				if(opcao==0) { return 1; }
				}while(opcao!=1 && opcao!=2 && opcao!=3);

				alteracampos(p,opcao);

				gravar_lista(p); //grava no ficheiro

				printf("\n\n\tEste jogador foi alterado com sucesso!\n\n");	
				system("pause");
				return 1;
		}else{
				printf("\n\nPASSWORD INCORRECTA! - Tente Novamente\n");
				return 0;
		}
		printf("\n\nDADOS INCORRECTOS! - Tente Novamente\n");
		}
	return 0;
}

pjogador loginEeliminar(pjogador p) //funcao que elimina jogador após login com sucesso
{
	char nickname[21],password[16];
	char opcao;
	int id;
	pjogador aux;

	aux=p; //var auxiliar para o inicio da lista

   clrscr();
	    printf("\n\tLogin: ([0]-Sair)\n\n Introduza o seu NICKNAME: ");
		gets(nickname);
		if(nickname[0]=='0'){ return p; }
		printf("\n Introduza a sua PASSWORD: ");
		gets(password);

		while(p!=NULL && strcmp(p->nickname, nickname) != 0){
			p=p->prox;}
		if(p!=NULL){
			if(strcmp(p->password, password)==0)
			{
				printf("\n\n\tJogador com ID %d foi logado com sucesso!\n\n",p->id);

				mostra_info2(p);

				do{
				printf("\n\nTem a certeza que deseja eliminar a sua conta? ( [S]-Sim | [N]-Nao ) : ");
				scanf(" %c",&opcao);
				}while(opcao!='S' && opcao!='s' && opcao!='n' && opcao!='N');

				if(opcao=='S' || opcao=='s')
				{
					id=p->id;
					p=aux;            //volta ao inicio da lista
					p=elimina(p,id);  //envia para a funcao o id do jogador a eliminar e o ponteiro para o inicio da lista	
					gravar_lista(p); //grava a alteracao no ficheiro
          		return p;
				}else{   //se ja nao quiser eliminar a conta..
					p=aux;
					return p;}
			}else{
				printf("\n\nPassword Incorrecta! - Tente Novamente\n\n");
				system("pause");
			    p=aux;
				return p;}
		}else{				
		printf("\n\nDados Incorrectos! - Tente Novamente\n\n");
		system("pause");
		p=aux;
		return p;
		     }
}



void alteracampos(pjogador p,int opcao){

	getchar();

	if(opcao==1)
	{
		printf("\nNovo Nickname: ");
	    gets(p->nickname);
	}

	if(opcao==2)
	{
		printf("\nNovo Nome: ");
	    gets(p->nome);
	}

	if(opcao==3)
	{
		printf("\nNova Password: ");
	    gets(p->password);
	}

}

pjogador mostra_estatisticas(pjogador p)             //funcao de estatistica/ordenacao
{                                                  //vai ser criada uma nova estrutura e vai-se armazenar no a no nessa ordenando 1 a 1
pjogador novalista=NULL,novo,aux;                //(igual a função de inserir ordenadadamente, mas neste caso ja existe, usa-se 2 estruturas)
int registados=0,totaljogos=0,i=1;

while(p!=NULL){ //enquanto nao for o final da lista..

	novo =(pjogador)malloc(sizeof(jogador));   //aloca espaço para um novo nó da nova estrutura ke vai ser ordenada
	if(novo == NULL)
	{
	printf("Erro na alocacao de memoria\n");
	return p;
	}

	*novo=*p;                                //novo vai tomar o valor de um determinado nó da estrutura "antiga"
	
	                                         //processo de ordenação:
	if(novalista == NULL || (novo->vitorias-novo->derrotas) > (novalista->vitorias-novalista->derrotas) )
	{   //novalista é o ponteiro para a nova estrutura/lista
	   //caso esta esteja vazia ou a pontuçao dessse jogador do nó copiado for maior que a pontuaçao do actual nó da novalista
       //(depreende-se claro, que se a lista nao estiver vazia, o 1º nó contem o jogador com melhor pontuação)

	novo->prox = novalista; //como a pontuação de 'novo' é maior ou a lista está vazia, este nó vai ser inserido no inicio da lista
	novalista = novo;
	}else{               //caso a pontuação for inferior ao do jogador do primeiro nó.. 

	aux = novalista;    //aux recebe o endereço do ponteiro para o inicio da novalista, para a percorrer

	while(aux->prox != NULL && (novo->vitorias-novo->derrotas) < (aux->prox->vitorias-aux->prox->derrotas)){
		aux = aux->prox;} //enquanto nao for o final da novalista e a pontuacao for menor que o próximo nó / percorre lista
	novo->prox = aux->prox;  // o proximo nó tem pontuação inferior ao novo, é necessário colocar o novo nó no "meio" dos dois 
	aux->prox = novo;	     //o novo nó fica entao a apontar para o proximo nó(com a pontuaçao inferior)
	
	}

	p=p->prox;
	
}

liberta_lista(p); // liberta a memoria ocupada pela estrutura da antiga lista!!

aux=novalista;  //aux obtem ponteiro para inicio da lista

while(novalista!=NULL){
registados++;                        //percorre a lista, cada no é um utilizador registado
totaljogos+=novalista->vitorias;   //para contar o total de jogos basta para isso saber o numero de vitorias (cada jogo tem um vencedor, jogos em pausa nao contam) 
novalista=novalista->prox;
}
novalista=aux;  //volta ao inicio da lista



	clrscr();
		
	printf("                                                   \n");
	printf(" #=====================TOP 5======================#\n");
	printf("                                                   \n");
	while(novalista!=NULL && i<=5){
    printf("  %d.  ID: %d  -  %s  -  %s  \n\tVitorias:%d (%.0f%%) | Derrotas:%d \n\n",i,novalista->id,novalista->nickname,novalista->nome,novalista->vitorias,(((float)novalista->vitorias/(float)totaljogos)*100),novalista->derrotas);
	novalista=novalista->prox;
	i++;}
	printf("                                                    \n");
	printf("                                                    \n");
    printf("      Total de Jogos Realizados: %d                 \n",totaljogos);
	printf("  Total de Jogadores Registados: %d                 \n",registados);
	printf(" #================================================#\n\n");

	novalista=aux;

	return novalista;
}


//===FUNCAO CLEAR SCREEN=== (fornecida pelo Docente responsável @moodle)
void clrscr()
{
 HANDLE h_stdout;
 CONSOLE_SCREEN_BUFFER_INFO csbi;
 DWORD dwConSize;
 COORD coordScreen = { 0, 0 };    
 DWORD dwCharsWritten;
 
 h_stdout = GetStdHandle(STD_OUTPUT_HANDLE); 
 
 GetConsoleScreenBufferInfo( h_stdout, &csbi );
 dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
 
 FillConsoleOutputCharacter( h_stdout, (TCHAR) ' ', dwConSize, coordScreen, &dwCharsWritten );
 
 SetConsoleCursorPosition( h_stdout, coordScreen ); 
}

//===Funcao para o 'cursor' ir para a coordenada x e y do ecrã (fornecida pelo Docente responsável @moodle)
void gotoxy(int x, int y)
{
 HANDLE h_stdout;
 COORD coordScreen;    
 
 h_stdout = GetStdHandle(STD_OUTPUT_HANDLE); 
 
 coordScreen.X = x;
 coordScreen.Y = y;
 
 SetConsoleCursorPosition(h_stdout,coordScreen);
}
