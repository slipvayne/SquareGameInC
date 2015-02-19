#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//====Headers====
#include "jogadores.h"
#include "jogo.h"
#include "outros.h"

pgravarjogo inicjogo(pjogador *ptrj,pgravarjogo jogo,int opcao,int *totaljogadores){

	pgravarjogo novo, aux;                   
	int x,y,i,j,zc,zl,njogadores,jvencedor,njogadoresEmjogo,colunas,linhas,jogadas=1,conta=0,jogadaescolhida=1,vemdeundo=0,skip=0,gravar=0;
	int **matrizquadrado=NULL;               //posicoes da matriz em memoria
	int *jogadores,*undo;                   //array de jogadores e array undo(para saber se já usaram essa pontuação ou não)
	char codigo[6];                        //codifo alfanumerico que é fornecido, aquando da pausa do jogo
	pjogadas ljogadas=NULL, auxj, aux2;   //inicialização da lista jogadas a NULL e ponteiros auxiliares
	pjogador p;                           


	p=*ptrj;  //cópia do ponteiro para o inicio da lista do jogadores (para o registo de jogadores é "usado" o original)
	aux=jogo; //ponteiro auxiliar para o inicio da lista dos jogos




	//========= INICIA JOGO NOVO ========== INICIA JOGO NOVO ========== INICIA JOGO NOVO ==========

do{
	 i=1; //comeca do 1º jogador (caso a opção escolhida seja a de retomar um jogo esta vai ser alterada consoante o ultimo que jogou)

	if(opcao==1) //se a opcao escolhida for iniciar um novo jogo
	{

 do{
	 clrscr();
	printf(" :::::::::::::::::::::::::::::\n");
	printf(" ::                         ::\n");
	printf(" ::        NOVO JOGO        ::\n");
	printf(" ::                         ::\n");
	printf(" :::::::::::::::::::::::::::::\n\n");
	printf("\nIntroduza o numero total de jogadores que vao jogar (2-7): "); 
	scanf("%d",&njogadores);
	}while(njogadores<=1 || njogadores>7);

	jogadores=criaarrayuni(njogadores+1,-1); //cria array dinamico com o numero total de jogadores(-1 em jogo(!=0))


	for(i=1;i<=njogadores;i++) // =====LOGIN/REGISTO DOS JOGADORES====
	{
		getchar(); clrscr();
		if(loginjogadores(ptrj,jogadores,i,njogadores,totaljogadores,&gravar)==0) { i--; } //caso seja diferente de 0 decrementa o i (repete login)  
		p=*ptrj; //se o ponteiro para o inicio da lista for alterado (com o registo)		
				
	}	
do{
	clrscr();
	printf(" ::::::::::::::::::::::::::::::::::::::\n");
	printf(" ::      Numero de Jogadores: %d      ::\n",njogadores);
	printf(" ::                                  ::\n");
	printf(" ::   MAX: %d  Linhas                 ::\n",(10-njogadores));
	printf(" ::                                  ::\n");
	printf(" ::   MAX: %d  Colunas               ::\n",(17-njogadores));
	printf(" ::                                  ::\n");
	printf(" ::::::::::::::::::::::::::::::::::::::\n\n");
	printf("\n\n\nQuantas linhas e colunas vai conter a matriz do quadrado? [L]_[C]: ");
	scanf("%d %d",&linhas,&colunas); //existe um numero max, ja que se forem 7 jogadores e usando uma matriz inicial grande nao "cabe" no ecra
  }while(linhas>(10-njogadores) || linhas<2 || colunas>(17-njogadores) || colunas<2);

	construirmatriz(colunas,linhas);                   //constroi a matriz no ecrã                 
	matrizquadrado=criaarraymulti(linhas+2,colunas+2); //adicionar mais 2 colunas/linhas ao criar o array (comeca 1 1 e nao 0 0 no grafico)
	undo=criaarrayuni(njogadores+1,0);                 //criar array dinâmico para a opção undo(inicializado a 0-ninguém usou)
	njogadoresEmjogo=njogadores;                      //njogadoresEmjogo vai tomar o valor dos jogadores totais a jogar
	i=1;                                              
	opcao=0;
	}
	

	 //================ RETOMA JOGO ============= RETOMA JOGO ============= RETOMA JOGO ============= RETOMA JOGO =============

	if (opcao==2)                 //se a opção escolhida foi a 2-retomar jogo
	{

		jogo=retomarjogo(jogo);  //devolve ponteiro com a lista correcta do codigo introduzido -retorna NULL se incorrecto
		if(jogo==NULL) { return aux; } //se o código não for válido retorna para o main 

		//copia a informação da estrutura desse jogo para as variaveis locais:

		njogadores=jogo->njogadores;               //numero de jogadores (total)
		jogadas=jogo->jogadas;                     //numero de jogadas
		jogadores=criaarrayuni(1,njogadores+1);    //cria array para os jogadores
		njogadoresEmjogo=jogo->njogadoresEmjogo;   //numero de jogadores em jogo(que ainda não foram eliminados)
		linhas=jogo->linhas;
		colunas=jogo->colunas;

			for(i=1;i<=njogadores;i++) 
				{ jogadores[i]=jogo->jogadores[i]; } //copia a informaçao dos jogadores (quem está em jogo ainda)
			
		construirmatriz(colunas,linhas);                         //constroi a matriz no ecrã
		matrizquadrado=criaarraymulti(linhas+2,colunas+2);	     //matriz que contêm a informação das posições ja escolhidas	
		
		ljogadas=jogo->jlista;		             //ponteiro para o inico da lista de jogadas deste jogo			
		auxj=jogo->jlista;                       //ponteiro para o inico da lista de jogadas deste jogo para uma var auxiliar
	    jogo->jlista=auxj;			             //necessário ainda?
			
		undo=criaarrayuni(njogadores+1,0);       //cria array para o undo também

			for(i=1;i<=njogadores;i++) 
			{ undo[i]=jogo->undo[i]; }         //necessário repor a informação para a variavel local
		
		for(i=0;i<=colunas;i++) 
			{ for(j=0;j<=linhas;j++)
				{
				matrizquadrado[i][j]=jogo->matrizquadrado[i][j];	
					if (matrizquadrado[i][j]==1) 
					{ gotoxy(i*4+3,j*2); printf("*"); }    //coloca as posiçoes escolhidas no ecrã
		}
		}

		i=jogo->i; //ultimo jogador
		jogo=libertarjogo(aux,jogo->codigo); //ja se pode libertar da memoria o jogo gravado e post/ gravar (aux é o inicio da lista)		
	    gravar_jogo(jogo);
		
		opcao=0;

	}
	




		// =========COMECA JOGO==========================COMECA JOGO==========================COMECA JOGO=================

for(;i<=njogadores;i++) //caso seja novo jogo o i é igual a 1, se foi carregado será o ultimo jogador que jogou)
{
	if(gravar==0){     //se a opçao gravar estiver disponível
		gotoxy(44, 0); printf("( 0 - Pausar Jogo | Undo Inactivo ) ");}else{
		gotoxy(44, 0); printf("(  Pausa Inactiva | Undo Inactivo ) "); }
	    if(jogadas>njogadores && njogadores==njogadoresEmjogo && undo[i]==0 && gravar==0) //onde e gravar disponivel
        {gotoxy(44, 0);  printf("( 0 - Pausar Jogo  |  99 - Undo   ) "); } //undo so no minimo se todos ja tiverem jogado uma vez,etc
        if(jogadas>njogadores && njogadores==njogadoresEmjogo && undo[i]==0 && gravar>=1)
		{gotoxy(44, 0);  printf("(  Pausa Inactiva  |  99 - Undo   ) ");}
	    gotoxy(0, 22); printf("                                                                            "); //"apagar linhas"
		gotoxy(0, 23); printf("                                                                            ");
	
       if(jogadores[i]!=0){                                        //se este jogador ainda nao foi eliminado..(1=em jogo)
		gotoxy(30, 0); printf("Jogada [ %d ]",jogadas);	  
		
		do{
			do{
		gotoxy(2, 19);  printf("                                                                ");
		gotoxy(2, 19);  printf("  [ Jogador %d - %s ]\n", i,devolvenick(p,jogadores[i]));
		printf("  Introduza uma nova posicao com as coordenadas [x]_[y]: ");  scanf("%d %d",&x,&y);			
		gotoxy(0, 21);   printf("                 ");   gotoxy(53, 20);  printf("                 ");
		x=abs(x); y=abs(y); 

		if((x>colunas && x!=99) || (y>linhas && x!=99)){ 
			gotoxy(2, 23); printf("Posicao nao valida! Tente novamente...\n");
			gotoxy(53, 20);  printf("                 "); // Limpa coordenadas
			gotoxy(0, 21);   printf("                 "); } 
		}while( (x>colunas && x!=99) || (y>linhas && x!=99) );   //valor sempre positivo ( |x| && |y| )





		//===============GRAVAR JOGO=================GRAVAR JOGO==============GRAVAR JOGO==============	
		if( (x==0 || y==0) && gravar==0){ //caso seja escolhida a opção gravar jogo e esta esteja disponivel
		
		if((novo=(pgravarjogo)malloc(sizeof(gravarjogo)))==NULL) // aloca espaço para novo (gravarjogo)
			{ 
			gotoxy(2, 22); printf("Erro na alocacao de memoria\n");
			}else{
		
			geracodigo(novo->codigo); 	//gera novo codigo que vai ficar associado a este jogo

			novo->njogadores=njogadores;
			novo->i=i;
			novo->jogadas=jogadas;
			novo->njogadoresEmjogo=njogadoresEmjogo;
			novo->linhas=linhas;
			novo->colunas=colunas;

			for(i=1;i<=njogadores;i++)
			{				
				novo->jogadores[i]=jogadores[i];			
			} 

			for(i=0;i<=colunas;i++){
				 for(j=0;j<=linhas;j++) { 				
				 novo->matrizquadrado[i][j]=matrizquadrado[i][j];  
				}
			}				

				novo->jlista=ljogadas;	//ponteiro para o inicio da lista de jogadas
				auxj=novo->jlista;     //ponteiro auxiliar
				novo->jlista=auxj;    //necessário?!

			for(i=1;i<=njogadores;i++) 
			{ novo->undo[i]=undo[i]; }

			novo->prox=jogo;     //insere nó no inicio da lista de jogos
			jogo=novo;			
			
		}
		    //grava para ficheiro
			gravar_lista(p);
		    gravar_jogo(jogo);

			gotoxy(2, 22); printf("Para no futuro voltar ao jogo use o seguinte codigo: %s\n",novo->codigo);
			system("pause"); 

			return jogo;
		}
			


      //===============UNDO==================UNDO=============UNDO================UNDO==============UNDO========
			if(x==99 || y==99) //caso seja escolhida a opcao undo
			{
				vemdeundo=1;  //para nao apresentar a mensagem de posição invalida(mais abaixo)
				skip=0;      //para saltar caso a jogada seleccionada for invalida

			  if(jogadas<=njogadores) //caso o numero de jogadas for inferior ao numero de jogadores(tem que dar uma volta no minimo)
			  {
				  gotoxy(2, 22); printf("A opcao undo nao esta activa! Ainda nao jogaram todos os jogadores!\n");
				  system("pause");
	              gotoxy(0, 22); printf("                                                                            "); //"apagar linhas"
		          gotoxy(0, 23); printf("                                                                            ");
			  }else{
				if(njogadores!=njogadoresEmjogo) //se o numero de jogadores em jogo for diferente do total de jogadores
				{
					gotoxy(2, 22); printf("Undo ja nao e' possivel! Um jogador ja foi eliminado\n");	
					system("pause");
					gotoxy(0, 22); printf("                                                                            "); //"apagar linhas"
			        gotoxy(0, 23); printf("                                                                            ");
				}else{

					if(undo[i]==0 && njogadores==njogadoresEmjogo && jogadas>njogadores) //se ainda nao tiver usado a opção undo
					{
					gotoxy(0, 22); printf("                                                                            "); //"apagar linhas"
			        gotoxy(0, 23); printf("                                                                            ");
					gotoxy(0, 22); printf("[UNDO] Qual a jogada: ");
						scanf("%d",&jogadaescolhida);

					auxj=ljogadas; //ponteiro auxiliar para o inicio da lista de jogadas
					
					ljogadas=auxj; //ponteiro inicio da lista, necessário!?
					ljogadas=procura_jogada(ljogadas,jogadaescolhida,i); //verifica se a jogada existe e se foi jogada por esse jogador e devolve no
					
					aux2=ljogadas; // ponteiro para o no dessa jogada
					
					if(ljogadas==NULL) //se devolver null, essa jogada nao existe ou nao foi jogada pelo jogador
					{
						ljogadas=auxj;  skip=1; // ljogadas volta a apontar para o inicio da lista e vai saltar o proximo passo
					}
					
				if(skip!=1){
				while(ljogadas!=NULL)
					{
						//vai percorrer a lista de jogadas posteriores a esse no e cada jogada na matrizquadrado vai tomar o valor de 0
						matrizquadrado[ljogadas->x][ljogadas->y]=0; 						
						ljogadas=ljogadas->prox;
		
					}									
				        ljogadas=aux2; // ponteiro para o no da jogada a eliminar
						ljogadas=elimina_jogadas(ljogadas,jogadaescolhida,auxj); //elimina as jogadas posteriores da lista

						if(ljogadas!=NULL){ ljogadas=auxj;} // se ainda restarem jogadas, ljogadas volta a apontar para o inicio da lista

						jogadas=jogadaescolhida;  //numero de jogadas total vai ser o numero da jogada escolhida

					
									
					construirmatriz(colunas,linhas); //reconstruir matriz sem as ultimas posicoes

					for(zl=0;zl<=colunas;zl++){
							for(zc=0;zc<=linhas;zc++){ 
								if (matrizquadrado[zl][zc]==1) 
										{ gotoxy(zl*4+3,zc*2); printf("*"); } } }  // repor posicoes escolhidas que ja nao foram abrangidas pelo undo

					gotoxy(2, 22); printf("Undo usado com sucesso! \n");
					undo[i]=1; //este jogador ja usou a opçao undo
					system("pause");
		            gotoxy(0, 22); printf("                                                                            "); //"apagar linhas"
		            gotoxy(0, 23); printf("                                                                            ");
		            vemdeundo=1;
				}}else{
					gotoxy(2, 22); printf("Undo ja nao e' possivel! Voce ja usou essa opcao! \n");
					system("pause");
		            gotoxy(0, 22); printf("                                                                            "); //"apagar linhas"
		            gotoxy(0, 23); printf("                                                                            ");
				
				}
				}
			  }
			}

			//=============FIM UNDO=================POSICAO NAO VALIDA=====================
		    if(vemdeundo==0)
			{
			if(matrizquadrado[x][y]==1)
			{
			gotoxy(2, 23); printf("Posicao ja escolhida! Tente novamente...\n");
			gotoxy(53, 20);  printf("                 "); // Limpa coordenadas
			gotoxy(0, 21);   printf("                 "); 
			}}        
			vemdeundo=0;

		 if(jogadores[i]!=0){ //se este jogador ainda nao foi eliminado..
			 gotoxy(30, 0); printf("Jogada [ %d ]",jogadas);}  
		 if(gravar==0) 
		 { gotoxy(44, 0); printf("( 0 - Pausar Jogo | Undo Inactivo ) "); }else
		 { gotoxy(44, 0); printf("( Pausa Inactiva  | Undo Inactivo ) "); }
		
	    if(jogadas>njogadores && njogadores==njogadoresEmjogo && undo[i]==0 && gravar==0)
        {gotoxy(44, 0);  printf("( 0 - Pausar Jogo  |  99 - Undo   ) "); } //undo so no minimo se todos ja tiverem jogado uma vez,etc
		if(jogadas>njogadores && njogadores==njogadoresEmjogo && undo[i]==0 && gravar>=1)
        {gotoxy(44, 0);  printf("(  Pausa Inactiva  |  99 - Undo   ) "); } 
		
		gotoxy(53, 20);  printf("                 "); // Limpa coordenadas
		gotoxy(0, 21);   printf("                 "); 

   }while(x>colunas || y>linhas || matrizquadrado[x][y]==1 || x==0 || y==0);


			gotoxy(x*4+3, y*2); printf("*"); // define posicao na matriz do quadrado

			gotoxy(53, 20);  printf("                 "); // Limpa coordenadas antigas
			gotoxy(0, 21);   printf("                 "); 
			

		
	//============DEFINE ARRAY-MATRIZ===============    

    matrizquadrado[x][y]=1;  // esta posicao fica assim "activa" e "escolhida" no array

	ljogadas=jogada(ljogadas,i,x,y,jogadas); // adiciona nova jogada/novo nó à lista de jogadas

	jogadas++; // incrementa o nº de jogadas totais

	conta=0; //servirá para contar o total de jogadores em jogo que servira para o codigo a seguir

	


	//===============VERIFICA SE EXISTE ALGUM QUADRADO NA MATRIZ===============VERIFICA SE EXISTE ALGUM QUADRADO NA MATRIZ=======

	if(verificaquadrado(x,y,matrizquadrado,linhas+1,colunas+1)==1) // +1 (visto que a posicao 0 0 nao conta)
	{	
		gotoxy(2, 19);  printf("                                                                          "); 
		gotoxy(2, 20);  printf("                                                                          ");
		gotoxy(2, 21);  printf("                                                                          "); 
		gotoxy(2, 20);  printf("Foi encontrado um QUADRADO na matriz! O jogador %d esta assim eliminado!\n\n",i);
		system("pause");
		gotoxy(2, 20);  printf("                                                                          "); 
		
		adicionarderrota(p,jogadores[i]); //adiciona uma derrota a um utilizador com esse id

		if(strcmp(devolvenick(p,jogadores[i]),"Convidado")==0) { gravar--; if(gravar==0){ //se é convidado decrementa a var gravar
		gotoxy(2, 20);  printf("Nova Opcao: Agora ja e' possivel gravar! (Um convidado foi eliminado)\n\n");
		system("pause"); gotoxy(2, 20);  printf("                                                                          "); 
		} }

		jogadores[i]=0; // como foi eliminado, este jogador ficara inactivo (a 0) assim ja nao passa no for (acima)

		njogadoresEmjogo--; //decrementa jogadores em jogo! (deixara que o undo esteja activo também)
		
		for(j=1;j<=njogadores;j++){
			if(jogadores[j]>=1) { conta++; jvencedor=j; } }
				if(conta==1) // Se houver somente um jogador.... esse mesmo ganha!
					{	
						clrscr();
	printf("\n\n\n\t ::::::::::::::::::::::::::::::::::::\n");
	printf("\t ::                                ::\n");
	printf("\t ::           VENCEDOR!!           ::\n");
	printf("\t ::                                ::\n");
	printf("\t ::::::::::::::::::::::::::::::::::::\n\n\n\t PARABENS!");

		printf("\n\n\n\tO jogador %d com o nickname ' %s ' ganhou este jogo!\n\n\n\n",jvencedor,devolvenick(p,jogadores[jvencedor])); 
		
	    vencedorvictoria(p,jogadores[jvencedor]); // adiciona uma victoria ao vencedor deste jogo!

		gravar_lista(p); //actualiza ficheiro com a info alterada de vitorias/derrotas/etc
		
		system("pause");
	
		
		return jogo; //============VOLTA AO MAIN========================

				}



	//============CASO AINDA HAJA MAIS QUE UM JOGADOR EM JOGO CONTINUA.. E ADICIONA LINHA/COLUNA=============
		    
		construirmatriz(++colunas,++linhas); //adiciona mais uma linha e coluna a matriz e reconstroi a matriz..
		
		for(zl=0;zl<=colunas-1;zl++){
		  for(zc=0;zc<=linhas-1;zc++){
			   if (matrizquadrado[zl][zc]==1)
			   { gotoxy(zl*4+3,zc*2); printf("*"); } } }  // e' necessario repor posicoes ja utilizadas...
				
			
		matrizquadrado=alocaMaisEspaco(matrizquadrado,colunas+1,linhas+1); // aloca mais espaco para a matriz
	}

   }	

   }
	
 }while(1);

}
//====== FIM JOGO====






//===============FUNCOES PARA O JOGO=======================FUNCOES PARA O JOGO=======================FUNCOES PARA O JOGO===========



pgravarjogo retomarjogo(pgravarjogo jogo)

{
		pgravarjogo aux;    //se falhar no codigo para voltar ao inicio do ponteiro pra estrutura
		char codigoinput[6];

		aux=jogo;



do{
	clrscr();
	printf(" :::::::::::::::::::::::::::::\n");
	printf(" ::                         ::\n");
	printf(" ::     RETOMAR UM JOGO     ::   ( [0]-Sair) \n");
	printf(" ::                         ::\n");
	printf(" :::::::::::::::::::::::::::::\n\n");
	printf("\n\n\n\tIntroduza o codigo alfanumerico que lhe foi fornecido: ");
	gets(codigoinput);
	if(codigoinput[0]=='0' && codigoinput[1]=='\0') { return NULL; }
	
	while(jogo!=NULL && strcmp(jogo->codigo, codigoinput) != 0)
		{ jogo=jogo->prox; }
		if(jogo!=NULL)
		{

		printf("\n\n\tO codigo foi lido com sucesso! O jogo vai continuar...\n\n\n\n");
		system("pause");

		return jogo;
							
		}else{
				printf("\n\n\tO codigo que introduziu nao e' valido! Tente Novamente!\n\n\n\n");				
				system("pause");
				jogo=aux;
		}
	}while(1);
}




void adicionarderrota(pjogador p, int id)
{
	while(p!=NULL && p->id!=id)
		p=p->prox;
		if(p!=NULL)
		{
			p->derrotas++;
			//printf("\nFoi atribuido ao jogador com ID %d uma derrota!\n",id);
		}	
}

void vencedorvictoria(pjogador p, int id)
{
	while(p!=NULL && p->id!=id)
		p=p->prox;
		if(p!=NULL)
		{
			p->vitorias++;
			//printf("\nFoi atribuido ao jogador com ID %d mais uma victoria!\n",id);
		}
		
}


int loginjogadores(pjogador *ptr, int *jogadores, int i, int njogadores, int *totaljogadores, int *gravar)
{
	pjogador p;
	char nickname[21],password[16],opcao;
	int j;

	p=*ptr;

	do{
				printf("\n\t [ JOGADOR %d ]: Tem conta registada?\n\n [ [S]-Sim | [N]-Jogar como Convidado | [R]-Registar ] : ",i);
				scanf(" %c",&opcao);
				}while(opcao!='S' && opcao!='s' && opcao!='n' && opcao!='N' && opcao!='R' && opcao!='r');
	
	  if(opcao=='N' || opcao=='n'){
		  while(p!=NULL && strcmp(p->nickname,"Convidado") != 0){
			p=p->prox;}
		if(p==NULL){ //criar conta convidado
			*ptr=insere_convidado(*ptr,*totaljogadores);
		  ++*totaljogadores;
		   p=*ptr;
		  gravar_lista(p);		 
		  jogadores[i]=p->id; 
		  printf("\n\n\n\tO jogador %d vai jogar com conta de convidado!\n\n\n",i);
		  system("pause");
		  ++*gravar; //so da para gravar o jogo se todos estiverem registados (se gravar for diferente de 0...nao da)
		  return 1; 
		     }else{
				jogadores[i]=p->id;
		  printf("\n\n\n\tO jogador %d vai jogar com conta de convidado!\n\n\n",i);
		  system("pause");
		  ++*gravar;
				return 1;
			}}

	 if(opcao=='R' || opcao=='r'){ clrscr(); getchar();
	
		 *ptr=insere_jogador(*ptr,*totaljogadores);
		 p=*ptr;
		 jogadores[i]=p->id;
		 ++*totaljogadores; 
		 printf("\n\n O jogador %d com o nickname ' %s ' foi registado com sucesso para este jogo!\n",i,p->nickname);
		 gravar_lista(*ptr);
		 return 1;
	 }
	 if(opcao=='S' || opcao=='s') { getchar(); clrscr();		
	    printf("\n\n\t   [ Login: JOGADOR %d ]  \n\n Introduza o seu NICKNAME: ",i);
		gets(nickname);
		printf("\n Introduza a sua PASSWORD: ");
		gets(password);

		while(p!=NULL && strcmp(p->nickname, nickname) != 0){
			p=p->prox;}
		if(p!=NULL){
			if(strcmp(p->password, password)==0)
			{
			for(j=1;j<=njogadores;j++)
			{ 				
			  if(jogadores[j]==p->id) 				  
			  {
				  
			    printf("\n\n\n\tEsta conta ja esta registada para este jogo!\n\n",p->id);
				return 0;
			  }}			   
			    printf("\n\n\n\tO Jogador %d com o nome ' %s ',\n\tfoi registado com sucesso para este jogo!\n\n",i,p->nome);
				jogadores[i]=p->id; // Jogador X tem o ID X
				return 1;			
		}else{
				printf("\n\n\tPASSWORD INCORRECTA! - Tente Novamente...\n\n");
				return 0;
			}
		}printf("\n\n\tDADOS INCORRECTOS! - Tente Novamente\n\n"); } 
		
return 0;
}

char* devolvenick(pjogador p, int id)
{
	    
	    while(p!=NULL && p->id!=id)
		p=p->prox;
		if(p!=NULL){

				return p->nickname;			
		}else{
				return 0;
}
return 0;
}

pgravarjogo libertarjogo(pgravarjogo p,char* codigo)
{
pgravarjogo actual, anterior = NULL;

actual = p; 

while(actual != NULL && strcmp(actual->codigo,codigo)!=0)
{
	anterior = actual;
	actual = actual->prox;
}
	if(anterior == NULL)    //primeiro no da lista
	{
		p = actual->prox;
	}else{
			anterior->prox = actual->prox;
		 }
	free(actual);
	return p;
}

int** criaarraymulti(int colunas,int linhas) // http://www.eskimo.com/~scs/cclass/int/sx9b.html
{ 

	int **array,i,j;
	array = (int**)malloc(linhas * sizeof(int *));
	if(array == NULL)
		{
		printf("\n Sem memoria disponivel! \n");
		}
   	for(i = 0; i < linhas; i++)
		{
		array[i] = (int*)malloc(colunas * sizeof(int));
		if(array[i] == NULL)
			{
			printf("\n Sem memoria disponivel! \n");		
			}
		}
	
	return array;
}

int** alocaMaisEspaco(int **matrizquadrado,int linhas,int colunas)
{
	
int **matriztemp,i,j;

matriztemp=criaarraymulti(colunas,linhas);

for(i=1;i<linhas-1;i++){
	for(j=1;j<colunas-1;j++){
		matriztemp[i][j]=matrizquadrado[i][j]; }}

free(matrizquadrado); //liberta espaco da matriz anterior

return (matriztemp);
}

int* criaarrayuni(int elementos,int arg)
{
	int *array,i;
	array = (int*)malloc(elementos * sizeof(int *));

	for(i=0;i<elementos;i++){
		array[i]=arg; } // inicializar array a 1 ou a 0 consoante o argumento

	if(array == NULL)
		{
		printf("\n Sem memoria disponivel! \n");
		}
	return array;
}

void construirmatriz(int colunas,int linhas){

	int i,j;
	
	clrscr();

	gotoxy(6,1); printf("X");
	gotoxy(3,2); printf("Y");

	for(i=2;i<=colunas+1;i++){
	gotoxy(i*4-1,1);
	printf("%d",i-1);} // NUMEROS EM CIMA HORIZONTAL

	for(i=2;i<=colunas;i++){
	gotoxy(i*4,2);
	printf("___");}  // PARTE DE CIMA DA MATRIZ

	for(j=2;j<=linhas;j++)
		{	gotoxy(4,j*2-2);
			printf("%d",j-1); // NUMEROS Y	VERTICAL
			if(j==linhas) { gotoxy(4,j*2); printf("%d",j); } //ULTIMO

		for(i=2;i<=colunas;i++)
			{
			if(i==2){ gotoxy(i*4-1,j*2-1); printf("|"); gotoxy(i*4-1,j*2); printf("|"); }
			gotoxy(i*4,j*2-1);
			printf("   |");
			gotoxy(i*4,j*2);		
			printf("___|");
			}		
		}
}



int verificaquadrado(int x,int y,int **matrizquadrado,int colunas,int linhas)
{
	int contaX=0,contaY=0;
	int *pontosX,*pontosY,*pontosX2,*pontosY2;
	int i,j;

	pontosX=pontosX2=criaarrayuni(linhas,0);
    pontosY=pontosY2=criaarrayuni(colunas,0);

	//VERIFICA SE HA MAIS ALGUM PONTO NA MESMA LINHA:

	for(i=0;i<linhas;i++)
	{
		if (matrizquadrado[i][y]==1 && i!=x)
		{ 
			pontosX[contaX]=i;
			contaX++;

		}
	}

	//VERIFICA SE HA MAIS ALGUM PONTO NA MESMA COLUNA:

	for(i=0;i<colunas;i++)
	{
		if (matrizquadrado[x][i]==1 && i!=y)
		{ 
			pontosY[contaY]=i;
			contaY++;

		}
	}
	for(i=0;i<contaX;i++)
	{
		for(j=0;j<contaY;j++)
		{ 
		if(abs(pontosX[i]-x)==abs(pontosY[j]-y))
			{
			x=pontosX[i];  
			y=pontosY[j];

			// COMPARA COM OUTRO PONTO=====

				//VERIFICA SE HA MAIS ALGUM PONTO NA MESMA LINHA:
			contaX=0;
			contaY=0;			
	for(i=0;i<linhas;i++)
	{
		if (matrizquadrado[i][y]==1 && i!=x)
		{ 
			pontosX2[contaX]=i;
			contaX++;

		}
	}

	//VERIFICA SE HA MAIS ALGUM PONTO NA MESMA COLUNA:

	for(i=0;i<colunas;i++)
	{
		if (matrizquadrado[x][i]==1 && i!=y)
		{ 
			pontosY2[contaY]=i;
			contaY++;

		}
	}
			for(i=0;i<=contaX;i++)
				{
				for(j=0;j<=contaY;j++)
					{ 
					//  === QUADRADO(ultimo ponto) ===
					
					if(abs(pontosX2[i]-x)==abs(pontosY2[j]-y) && matrizquadrado[x][y]==1)
					{					
						return 1;
					}			
		}
	  }
	 }
   }
  } 
return 0;
} 

pjogadas jogada(pjogadas p, int jogador, int x, int y, int jogada) //insere jogada no final da lista
{
pjogadas nova, aux;

	if((nova=(pjogadas)malloc(sizeof(jogadas)))==NULL){ // aloca espaço para um novo registo
	printf("Erro na alocacao de memoria\n");
	return p;
	}
		nova->jogador=jogador;
		nova->x=x;
		nova->y=y;
		nova->jogada=jogada;

	if(lista_vazia(p)){
	p = nova;
	p->prox=NULL;
	}else{
		aux = p;
		while(aux->prox != NULL){
			  aux = aux->prox;}
		aux->prox = nova;
		nova->prox=NULL;
		}
	
	return p;
}


pjogadas procura_jogada(pjogadas p, int jogada, int jogador)
{
pjogadas anterior,actual;

   if(jogada==1 && p->jogador==jogador) //a primeira jogada é sempre o inicio da lista
   {
	   return p;
   }

	
	while(p!=NULL && p->jogada!=jogada){
	anterior=p;
	p=p->prox;}
	if(p!=NULL && p->jogador==jogador){
	anterior->prox=NULL; 	 
	return p; //retorna ponteiro para essa jogada	
	}else{ gotoxy(2, 21); printf("\nEssa jogada nao existe ou nao jogaste nessa jogada!\n"); return NULL;} 
	
}

pjogadas elimina_jogadas(pjogadas p, int jogadaescolhida, pjogadas aux) //recebe o no da jogada escolhida e continua a eliminar até ao fim
{
pjogadas actual,jogada;

jogada=p;

while(p != NULL)
{
	actual=p;
	p=p->prox;
	free(actual);
}

    //volta a posicao da jogada seleccionada e continua daí..
	if(jogadaescolhida==1) //se for a 1º jogada
	{p=NULL; return p;}
	return aux;	
}

int lista_vazia(pjogadas p)
{
if(p == NULL)
return 1;
else
return 0;
}