#include <stdio.h>

#include "n-tree.h"

int main(int argc, char *argv[]) {

  No *raiz = inicializar(5);

  inserir(raiz, 5, 2);
  inserir(raiz, 5, 3);
  inserir(raiz, 3, 4);
  inserir(raiz, 2, 1);

  exibirArvore(raiz);

  printf("\n\n\n");

  exibirArvoreIndent(raiz, 0);

  freeArvore(raiz);
  printf("\n");

  // exibirArvore(raiz); // Deve ocorrer o erro: segmentation fault core dumped
  // (freeArvore libera `raiz`, deixa de exisir).

  return 0;
}
