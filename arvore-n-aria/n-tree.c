#include "n-tree.h"

No* criarNo(ElementType ch) {
    No* novoNo = (No*)malloc(sizeof(No));
    
    novoNo->chave = ch;
    novoNo->firstChild = NULL;
    novoNo->next = NULL;

    return novoNo;
}

No* inicializar(ElementType ch) {
    return criarNo(ch);
}

No* buscarChave(No* raiz, ElementType ch) {
    if (raiz == NULL) return NULL;
    if (raiz->chave == ch) return raiz;

    No* p = raiz->firstChild;

    while(p) {
        No* r = buscarChave(p, ch);
        if (r) 
            return r;
        
        p = p->next;
    }
    return NULL;
}

void exibirArvore(No* raiz) {
    if(raiz == NULL) return;

    prinf("%d(", raiz->chave);

    No* p = raiz->firstChild;

    while(p){
        exibirArvore(p);
        p = p->next;
    }
    printf(")");
}

int inserir(No* raiz, ElementType ch) {
    
}