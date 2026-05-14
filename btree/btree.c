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
    n->ehFolha = filho->ehFolha;
    n->numChaves = T - 1;

    int j;
    for(j = 0; j < T-1; j++) 
        n->Registros[j] = filho->Registros[j+T];

    if(!(filho->ehFolha))
        for(j=0; j<T; j++)
            n->filhos[j] = filho->filhos[j+T];
    
    filho->numChaves = T - 1;

    for(j = pai->numChaves; j > i; j--)
        pai->filhos[j+1] = pai->filhos[j];
    
    pai->filhos[i+1] = n;

    for(j=pai->numChaves-1; j>=i; j--)
        pai->Registros[j+1] = pai->Registros[j];

    pai->Registros[i] = filho->Registros[T-1];
    pai->numChaves++;

    //salvar no disco o pai, filho e o novo n
    // savarDisco(pai); salvarDisco(filho); salvarDisco(n);
}

// Neste caso, o próprio registro é a chave, mas pode-se criar um TipoChave e incluir um atributo chave na struct do Registro e compara TipoChave chave e Registro.chave
bool buscaRegAux(No* atual, Registro r, Registro *aux) {
    if(atual == NULL) return false;
    
    int i = 0;
    while(i < atual->numChaves && r > atual->Registros[i])
        i++;
    
    if(i < atual->numChaves && r == atual->Registros[i]) {
        *aux = atual->Registros[i];
        return true;
   } else {
        if(!atual->ehFolha)
            return buscaRegAux(atual->filhos[i], r, aux);
   }

   return false;
}

bool buscarRegistro(arvB* a, Registro r, Registro* aux) {
    return buscaRegAux(a->raiz, r, aux);
}

void inserirNoNaoCheio(No* atual, Registro* r) {
    int i = atual->numChaves-1;

    if(atual->ehFolha){
        while(i>=0 && *r < atual->Registros[i]) {
            atual->Registros[i+1] = atual->Registros[i];
            i--;
        }
    atual->Registros[i+1] = *r;
    atual->numChaves++;
    //savlarDisco(atual)
    
    } else {
        while(i>=0 && *r < atual->Registros[i])
            i--;
        i++;
        //lerDisco(atual->filhos[i])

        if(atual->filhos[i]->numChaves == 2*T-1) { // Filho está cheio
            divideNoFilho(atual, i, atual->filhos[i]);
            
            if(*r > atual->Registros[i]) // se chave for maior que a chave do registro i, a chave deve ir para a direita do filho dividido que subiu, ou seja, indice+1.
                i++;
        }
        inserirNoNaoCheio(atual->filhos[i], r);
            
    }
}

void inserirReg(arvB* a, Registro *r) {
    if(a->raiz->numChaves < 2*T-1)
        inserirNoNaoCheio(a->raiz, r);
    else {
        No* n = (No*)malloc(sizeof(No));
        No* aux = a->raiz;
        a->raiz = n;
        n->numChaves = 0;
        n->ehFolha = false;
        n->filhos[0] = aux;

        divideNoFilho(n, 0, aux);
        inserirNoNaoCheio(n, r);
    } 
}