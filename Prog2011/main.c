#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h> //para o getch (opcao com return/enter "auto")

//====Headers====
#include "jogadores.h"
#include "jogo.h"
#include "outros.h"

void menu(){

	clrscr();

	printf("                                                       \n");
	printf(" ::::::::::::::::::::[ Menu Principal ]::::::::::::::::::::\n");
	printf(" ::                                                      ::\n");
	printf(" ::                                                      ::\n");
	printf(" ::                    JOGO DO QUADRADO:                 ::\n");
	printf(" ::                                                      ::\n");
	printf(" ::                 1- JOGAR                             ::\n");
	printf(" ::                                                      ::\n");
	printf(" ::                                                      ::\n");
	printf(" ::                    JOGADORES:                        ::\n");
	printf(" ::                                                      ::\n");
	printf(" ::                 2- REGISTAR                          ::\n");
	printf(" ::                 3- ALTERAR                           ::\n");
	printf(" ::                 4- ELIMINAR                          ::\n");
	printf(" ::                 5- CONSULTAR                         ::\n");
    printf(" ::                 6- PESQUISA                          ::\n");
    printf(" ::                                                      ::\n");
	printf(" ::                                                      ::\n");
	printf(" ::                 7- ESTATISTICAS                      ::\n");
	printf(" ::                                                      ::\n");
	printf(" ::                 8- SAIR                              ::\n");
	printf(" ::                                                      ::\n");
	printf(" ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");

}

void main(){

	char op=0;
	int totaljogadores=1;
	pjogador lista=NULL;                         // no inicio as listas estão vazias
	pgravarjogo jogo=NULL,aux;
	
    lista=recuperar_lista(lista,&totaljogadores); //recuperar lista jogadores do ficheiro para memoria
	jogo=recuperar_jogos(jogo);                   //recuperar lista de jogos "pausados" do ficheiro

	srand((unsigned)time(NULL));                  // inicia srand para o random do codigo

	while (op< 1 || op > 8)
	{
	menu();                                       //apresenta menu principal

	printf(" Opcao: "); 
	op=getch();
	switch (op)
	{



// ============== AO SELECCIONAR OPÇÃO 1 -> JOGAR ==============
		case '1': printf("\n INICIAR JOGO\n ");  
	
	do{
	clrscr();
	printf("                                                   \n");
	printf(" ::::::::::::::::::::::[ Jogar ]:::::::::::::::::::\n");
	printf(" ::                                              ::\n");
	printf(" ::    1. NOVO JOGO                              ::\n");
	printf(" ::                                              ::\n");
	printf(" ::                                              ::\n");
	printf(" ::    2. RETOMAR UM JOGO                        ::\n");
	printf(" ::                                              ::\n");
	printf(" ::                                              ::\n");
	printf(" ::                                              ::\n");
	printf(" ::    3. <-- MENU                               ::\n");
	printf(" ::                                              ::\n");
	printf(" ::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
	printf(" Opcao: "); 
	op=getch();
	}while (op!= '1' && op!= '2' && op!='3');		
	if(op=='1'){ jogo=inicjogo(&lista,jogo,1,&totaljogadores); op=0; break;}
	if(op=='2'){ jogo=inicjogo(&lista,jogo,2,&totaljogadores); op=0; break;}
	if(op=='3'){ op=0; break; }	





// ============== AO SELECCIONAR OPÇÃO 2 -> REGISTAR JOGADORES ==============

		case '2':
		lista=insere_jogador(lista,totaljogadores); 
		totaljogadores++; 
		
		op=0; break;




	   
// ============== AO SELECCIONAR OPÇÃO 3 -> ALTERAR JOGADORES ==============			
		case '3': 

			clrscr();
	printf(" :::::::::::::::::::::::::::::\n");
	printf(" ::                         ::\n");
	printf(" ::      ALTERAR JOGADOR    ::\n");
	printf(" ::                         ::\n");
	printf(" :::::::::::::::::::::::::::::\n\n");
			
			
			while(loginjogadores2(lista)==0);

			op=0; break;




// ============== AO SELECCIONAR OPÇÃO 4 -> ELIMINAR JOGADORES ==============
		case '4': 

		clrscr();
	printf(" :::::::::::::::::::::::::::::\n");
	printf(" ::                         ::\n");
	printf(" ::     ELIMINAR JOGADOR    ::\n");
	printf(" ::                         ::\n");
	printf(" :::::::::::::::::::::::::::::\n\n");

		lista=loginEeliminar(lista); 
		
		op=0; break;
		



// ============== AO SELECCIONAR OPÇÃO 5 -> MOSTRA/CONSULTA DE JOGADORES ==============
		case '5': 
    clrscr();
	printf(" :::::::::::::::::::::::::::::\n");
	printf(" ::                         ::\n");
	printf(" ::   LISTA DE JOGADORES    ::\n");
	printf(" ::                         ::\n");
	printf(" :::::::::::::::::::::::::::::\n\n");
			mostra_info(lista); 
				
			op=0; break;	




// ============== AO SELECCIONAR OPÇÃO 6 -> PESQUISA DE JOGADORES ==============
		case '6': printf("\n PESQUISA JOGADORES\n"); 	
		do
		{
	clrscr();
	printf("                                                   \n");
	printf(" ::::::::::::::::::[ PESQUISA ]:::::::::::::::::::\n");
	printf(" ::                                             ::\n");
	printf(" ::  1. PESQUISAR POR ID                        ::\n");
	printf(" ::                                             ::\n");
	printf(" ::  2. PESQUISAR POR NOME                      ::\n");
	printf(" ::                                             ::\n");
	printf(" ::  3. PESQUISAR POR NICKNAME                  ::\n");
	printf(" ::                                             ::\n");
	printf(" ::                                             ::\n");
	printf(" ::  4. <-- MENU                                ::\n");
	printf(" ::                                             ::\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
	printf(" Opcao: ");
	op=getch();		
	}while(op!='1' && op!='2' && op!='3' && op!='4');
		if(op=='4') {op=0; break; }

	procura_jogador(lista,op-48);
	system("pause"); op=0; break;




// ============== AO SELECCIONAR OPÇÃO 7 -> ESTATISTICAS/TOP/ORDENACAO ==============
		case '7': 

        lista=mostra_estatisticas(lista);
				
		system("pause"); 
		op=0; break;

		
	
// ============== AO SELECCIONAR OPÇÃO 8 -> SAIR DA APLICACAO  ==============
		case '8': 

  clrscr();
	printf(" \n\n\n\t:::::::::::::::::::::::::::::::::::::::::::::::\n");
	printf(" \t::                                           ::\n");
	printf(" \t::                [CREDITOS]                 ::\n");
	printf(" \t::                                           ::\n");
	printf(" \t::        Ricardo Germano - 21190726         ::\n");
	printf(" \t::                                           ::\n");
	printf(" \t::                   2011                    ::\n");
	printf(" \t::                                           ::\n");
    printf(" \t::                                           ::\n");
	printf(" \t::                                           ::\n");
	printf(" \t::          A sair do programa...            ::\n");
	printf(" \t::                                           ::\n");
	printf(" \t:::::::::::::::::::::::::::::::::::::::::::::::\n\n\n\n\n");
		system("pause"); 
		exit(1); break;			

	}
	}
}