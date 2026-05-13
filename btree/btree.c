#include <stdio.h>
#include <malloc.h>

#define T 3
#define true 1
#define false 0

typedef int bool;
typedef int Registro;

typedef struct No {
    int numChaves;
    bool ehFolha;
    Registro Registros[2*T-1]; 
    struct No*  filhos[2*T];

} No;

typedef struct arvoreB {
    No* raiz;
} arvB;

void inicializarArvB(arvB* a) {
    No* n = (No*)malloc(sizeof(No));

    n->ehFolha = true;
    n->numChaves = 0;
    
    a->raiz = n;  
}

void divideNoFilho(No* pai, int i, No* filho) {
    No* n = (No*)malloc(sizeof(No));
    n->ehFolha = true;
    n->numChaves = T - 1;

    int j;
    for(j = 0; j < T-1; j++) 
        n->Registros[j] = filho->Registros[j+T];

    if(!(filho->ehFolha))
        for(j=0; j<T; j++)
            n->filhos[j] = filho->filhos[j+T];
    
    filho->numChaves = T - 1;

    for(j = pai->numChaves; j > 0; j--)
        pai->filhos[j+1] = pai->filhos[j];
    
    pai->filhos[i+1] = n;

    for(j=pai->numChaves-1; j>=i; j--)
        pai->Registros[j+1] = pai->Registros[j];

    pai->Registros[i] = filho->Registros[T-1];
    pai->numChaves++;

    //salvar no disco o pai, filho e o novo n

}

bool inserirArvB(arvB* a, Registro r) {

}