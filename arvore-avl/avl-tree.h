#ifndef AVL_TREE_
#define AVL_TREE_

#include <stdio.h>
#include <malloc.h>

typedef int ElementType;

typedef struct no {
    ElementType ch;
    struct Node *left, *right;
    int bal;
} Node;

Node* criarNo(ElementType key);
Node* rotacaoL(Node* p);
Node* rotacaoR(Node* p);
Node* buscaBinaria(Node* raiz, ElementType ch);

int height(Node* r);
int max(int a, int b);

void inserirAVL(Node** pp, ElementType ch, int *alterou);

#endif