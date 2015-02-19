//======= Funções presentes em 'outros.c'========

void clrscr();

void gotoxy(int x, int y);

void gravar_lista(pjogador p);

pjogador recuperar_lista(pjogador p,int *totaljogadores);

char geracodigo(char codigo[6]);

pgravarjogo recuperar_jogos(pgravarjogo p);

void gravar_jogo(pgravarjogo p);

int loginjogadores2(pjogador p);

void alteracampos(pjogador p,int opcao);

pjogador loginEeliminar(pjogador p);

pjogador mostra_estatisticas(pjogador p);
