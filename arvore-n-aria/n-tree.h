#ifndef NTREE_H_
#define NTREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct no {
  ElementType chave;
  struct no *firstChild;
  struct no *next;
} No;

No* criarNo(ElementType ch);
No* inicializar(ElementType ch);
No* buscarChave(No *raiz, ElementType ch);
No* remover(No *raiz, ElementType ch);

int inserir(No *raiz, ElementType chavePai, ElementType chaveNova);

void exibirArvore(No *raiz);
void exibirArvoreIndent(No* raiz, int nivel);

void freeArvore(No* raiz);

#endif
