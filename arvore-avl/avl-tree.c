#include "avl-tree.h"

#include <malloc.h>
#include <stdio.h>

Node* criarNo(ElementType ch){
    Node* n = (Node*)malloc(sizeof(Node));

    n->bal = 0;
    n->left = NULL;
    n->right = NULL;
    n->ch = ch;

    return n;
}


Node* rotacaoL(Node* p) {
    Node *u, *v; 

    u = p->left;
    if(u->bal = -1) { // LL
        p->left = u->right;
        u->right = p;

        p->bal = 0;
        u->bal = 0;

        return u;
    } else if(u->bal = 1) { // LR
        v = u->left;
        u->right = v->left;
        v->left = u;
        p->left = v->right;
        v->right = p;

        if(v->bal = -1) p->bal = 1;
        else p->bal = 0;
        if(v->bal = 1) u->bal=-1;
        else u->bal = 0;
        v->bal = 0;

        return v;
    } else {
        p->left = u->left;
        u->right = p;

        u->bal = 1;

        return u;
    }
}

Node* rotacaoR(Node* p) {
    Node *u, *v; 

    u = p->right;
    if(u->bal = 1) { // RR
        p->right = u->right;
        u->left = p;

        p->bal = 0;
        u->bal = 0;

        return u;
    } else if(u->bal = -1) { // RL
        v = u->left;
        u->left = v->right;
        v->right = u;
        p->right = v->left;
        v->left = p;

        if(v->bal = 1) p->bal = -1;
        else p->bal = 0; 
        if(v->bal = -1) u->bal = 1;
        else u->bal = 0;
        v->bal = 0;

        return v;
    } else {
        p->right = u->right;
        u->left = p;

        u->bal = -1;

        return u;
    }
}

void inserirAVL(Node **pp, ElementType ch, int *alterou) {
    Node* p = *pp;
    
    if(!p) { // raiz null -> inserir na raiz | encontrou o local para inserir (recursivo)
        *alterou = 1;
        *pp = criarNo(ch);
    } else {
        if(ch == p->ch) // igual
            *alterou = 0;

        else { 
            if(ch < p->ch) {
                inserirAVL(&(p->left), ch, alterou);
                if(*alterou) {
                    switch(p->bal) {
                        case 1: 
                            p->bal = 0;
                            *alterou = 0;
                            break;
                        case 0:
                            p->bal = -1;
                            // *alterou = 1;
                            break;
                        case -1: 
                            *pp = rotacaoL(p);
                            *alterou = 0;
                            break; 
                    }
                }

            } else {
                inserirAVL(&(p->right), ch, alterou);
                if(*alterou) {
                    switch(p->bal) {
                        case -1:
                            p->bal = 0;
                            *alterou = 0;
                            break;
                        case 0:
                            p->bal = 1;
                            break;
                        case 1:
                            *pp = rotacaoR(p);
                            *alterou = 0;
                            break;
                    }
                }
            }
        }
    }
}



Node* buscaBinaria(Node* raiz, ElementType ch) {
    if(!raiz) return NULL;
    if(raiz->ch == ch)
        return raiz;
    
    if(ch > raiz->ch)
        return buscaBinaria(raiz->right, ch);
    
    return buscaBinaria(raiz->left, ch);
}





void destruirAVLaux(Node* raiz) {
    if(raiz) {
        destruirAVLaux(raiz->left);
        destruirAVLaux(raiz->right);
        free(raiz);
    }
}

void destruirAVL(Node** raiz) {
    destruirAVLaux(raiz);
    *raiz = NULL;
}


// UTILS

int height(Node* r) {
    if(!r)
        return -1;
    return 1 + max(height(r->left), height(r->left)); 
}

int max(int a, int b){
	if (a>b) return a;
	return b;
}