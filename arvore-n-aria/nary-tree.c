#include "nary-tree.h"

ElementType stdElement = 0;

No *criarNo(ElementType ch) {
  No *novoNo = (No *)malloc(sizeof(No));

  novoNo->chave = ch;
  novoNo->firstChild = NULL;
  novoNo->next = NULL;

  return novoNo;
}

No *inicializar(ElementType ch) { return criarNo(ch); }

No *buscarChave(No *raiz, ElementType ch) {
  if (raiz == NULL)
    return NULL;
  if (raiz->chave == ch)
    return raiz;

  No *p = raiz->firstChild;

  while (p) {
    No *r = buscarChave(p, ch);
    if (r)
      return r;

    p = p->next;
  }
  return NULL;
}

void exibirArvore(No *raiz) {
  if (raiz == NULL)
    return;

  printf("%d(", raiz->chave);

  No *p = raiz->firstChild;

  while (p) {
    exibirArvore(p);
    p = p->next;
  }
  printf(")");
}

// void exibirArvoreIndent(No* raiz, int nivel) {
//     if(raiz == NULL) return;

//     printf("%*s- %d\n", nivel * 2, "", raiz->chave);

//     No* p = raiz->firstChild;
//     while (p) {
//         exibirArvoreIndent(p, nivel + 1);
//         p = p->next;
//     }
// }

static void exibirArvoreConectores(No *no, const char *prefixo, int ehUltimo) {
  if (no == NULL)
    return;

  printf("%s%s %d\n", prefixo, ehUltimo ? "\\--" : "|--", no->chave);

  char novoPrefixo[256];
  snprintf(novoPrefixo, sizeof(novoPrefixo), "%s%s", prefixo,
           ehUltimo ? "    " : "|   ");

  No *filho = no->firstChild;
  while (filho) {
    int filhoEhUltimo = (filho->next == NULL);
    exibirArvoreConectores(filho, novoPrefixo, filhoEhUltimo);
    filho = filho->next;
  }
}

void exibirArvoreIndent(No *raiz, int nivel) {
  (void)nivel;
  if (raiz == NULL)
    return;

  printf("%d\n", raiz->chave);

  No *filho = raiz->firstChild;
  while (filho) {
    int filhoEhUltimo = (filho->next == NULL);
    exibirArvoreConectores(filho, "", filhoEhUltimo);
    filho = filho->next;
  }
}

int inserir(No *raiz, ElementType chavePai, ElementType chaveNova) {
  No *pai = buscarChave(raiz, chavePai);
  if (!pai)
    return 0;

  No *filho = criarNo(chaveNova);
  No *p = pai->firstChild;

  if (!p)
    pai->firstChild = filho;
  else {
    while (p->next) {
      p = p->next;
    }
    p->next = filho;
  }
  return 1;
}

void freeArvore(No *raiz) {
  if (raiz == NULL)
    return;

  No *filho = raiz->firstChild;
  while (filho) {
    No *next = filho->next;
    freeArvore(filho);
    filho = next;
  }

  raiz->chave = stdElement;
  raiz->firstChild = NULL;
  raiz->next = NULL;

  free(raiz);
}
