#ifndef ARVORE_N_ARIA_H
#define ARVORE_N_ARIA_H

typedef struct Data {
  int dia;
  int mes;
  int ano;
} Date;

typedef struct No {
  struct No *proximoIrmao;
  struct No *pai;
  struct No *mae;

  Date dataNascimento;

  char nome[21];
  char sobrenome[21];
} No;

Date data(int dia, int mes, int ano);

No *criarNo(char *nome, char *sobrenome, Date dataNascimento);
No *inicializar(char *nome, char *sobrenome, Date dataNascimento);
No *buscarFamiliar(No *raiz, char *nome, char *sobrenome);

int inserirPai(No *individuo, No *novoPai);
int inserirMae(No *individuo, No *novaMae);
int inserirIrmao(No *individuo, No *novoIrmao);

void imprimirArvoreGenealogica(No *raiz);
void freeArvore(No *raiz);

#endif
