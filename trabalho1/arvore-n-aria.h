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

  int id;
  unsigned int refQuant; // Quantidade de outros nós que apontam para o nó

  Date dataNascimento;

  char nome[26];
  char sobrenome[51];
} No;

Date data(int dia, int mes, int ano);

No *criarNo(char *nome, char *sobrenome, Date dataNascimento);
No *inicializar(char *nome, char *sobrenome, Date dataNascimento);
No *buscarFamiliar(No *raiz, char *nome, char *sobrenome);
No *buscarId(No *raiz, int id);

int inserirPai(No *individuo, No *novoPai);
int inserirMae(No *individuo, No *novaMae);
int inserirIrmao(No *individuo, No *novoIrmao, int mesmosPais);

void imprimirArvoreGenealogica(No *raiz);
void imprimirDadosPessoa(No *pessoa);
void freeArvore(No *raiz);

#endif
