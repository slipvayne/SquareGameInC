//====TYPEDEF DA ESTRUTURA=====
typedef struct jogador jogador,*pjogador;


//====== Estrutura JOGADOR =====
struct jogador{
	int id, vitorias, derrotas;                    // id do jogador / vitorias e derrotas desse jogador
	char nome[50], nickname[20], password[15];
	pjogador prox;
};


//======= Funções presentes em 'jogadores.c'========

pjogador insere_jogador(pjogador p,int totaljogadores);

pjogador insere_convidado(pjogador p,int totaljogadores);

pjogador elimina(pjogador p,int c);

void preenche(pjogador a,int totaljogadores,pjogador p);

void mostra_info(pjogador p);

void mostra_info2(pjogador p);

void liberta_lista(pjogador p);

void procura_jogador(pjogador p,int opcao);

pjogador insere_jogador(pjogador p,int totaljogadores);

pjogador elimina(pjogador p, int c);

int verifica_nickname(pjogador p,char *nickname);