typedef struct gravarjogo gravarjogo, *pgravarjogo;
typedef struct jogadas jogadas, *pjogadas;

//====== Estrutura Gravar Jogo =====
struct gravarjogo{
	char codigo[6];	                              //codigo gerado apos pausa do jogo
	int njogadores, njogadoresEmjogo, jogadas, i; // i=ultimo player que jogou / njogadores=total de jogadores /jogadas total
	int linhas,colunas;                           //linhas e colunas da matriz do quadrado na altura da pausa
	int jogadores[7], undo[7];                    //max jogadores -7 // undo- se 0 nao foi usado, se 1 foi usado
	int matrizquadrado[20][20];                   //posicoes ja jogadas na matriz
	pgravarjogo prox;                             //proximo no de jogos
	pjogadas jlista;                              //ponteiro para o inicio da lista da estrutura jogadas
};

//====== Estrutura das Jogadas de um Jogo =====
struct jogadas{
	int jogada;                   //numero da jogada
	int jogador;                  //numero do jogador
	int x,y;                     //coords x e y
	pjogadas prox;               //proximo no de jogadas
};


//======= Funções presentes em 'jogo.c'========

pgravarjogo inicjogo(pjogador *p,pgravarjogo jogo,int opcao,int *totaljogadores);

void construirmatriz(int colunas,int linhas);

int verificaquadrado(int x,int y,int **matrizquadrado,int colunas,int linhas);

int** criaarraymulti(int colunas,int linhas);

int* criaarrayuni(int elementos,int arg);

int** alocaMaisEspaco(int **pp,int nl,int nc);

int loginjogadores(pjogador *p, int *jogadores, int i, int njogadores, int *totaljogadores,int *gravar);

void vencedorvictoria(pjogador p, int id);

void adicionarderrota(pjogador p, int id);

pgravarjogo verificacodigo(pgravarjogo p);

pgravarjogo retomarjogo(pgravarjogo jogo);

char* devolvenick(pjogador p, int id);

pgravarjogo libertarjogo(pgravarjogo p,char* codigo);

pjogadas jogada(pjogadas p, int jogador, int x, int y, int jogada);

pjogadas procura_jogada(pjogadas p, int jogada, int jogador);

pjogadas elimina_jogadas(pjogadas p, int jogadaescolhida, pjogadas aux);

int lista_vazia(pjogadas p);