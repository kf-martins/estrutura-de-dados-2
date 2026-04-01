#include "arvore-n-aria.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Date data(int dia, int mes, int ano) {
    Date d;
    d.dia = dia;
    d.mes = mes;
    d.ano = ano;

    return d;
}

int mesmoNome(No *no, char *nome, char *sobrenome) {
    if (no == NULL || nome == NULL || sobrenome == NULL)
        return 0;
    return strcmp(no->nome, nome) == 0 && strcmp(no->sobrenome, sobrenome) == 0;
}

No *criarNo(char *nome, char *sobrenome, Date dataNascimento) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
        return NULL;

    strncpy(novoNo->nome, nome ? nome : "", sizeof(novoNo->nome) - 1);
    novoNo->nome[sizeof(novoNo->nome) - 1] = '\0';

    strncpy(novoNo->sobrenome, sobrenome ? sobrenome : "", sizeof(novoNo->sobrenome) - 1);
    novoNo->sobrenome[sizeof(novoNo->sobrenome) - 1] = '\0';

    novoNo->dataNascimento = dataNascimento;
    novoNo->pai = NULL;
    novoNo->mae = NULL;
    novoNo->proximoIrmao = NULL;

    return novoNo;
}

No *inicializar(char *nome, char *sobrenome, Date dataNascimento) {
    return criarNo(nome, sobrenome, dataNascimento);
}

No *buscarFamiliar(No *raiz, char *nome, char *sobrenome) {
    No *p;

    if (raiz == NULL) return NULL;

    if (mesmoNome(raiz, nome, sobrenome)) return raiz;

    p = buscarFamiliar(raiz->pai, nome, sobrenome);
    if (p != NULL) return p;

    p = buscarFamiliar(raiz->mae, nome, sobrenome);
    if (p != NULL) return p;

    return buscarFamiliar(raiz->proximoIrmao, nome, sobrenome);
}

int inserirPai(No *individuo, No *novoPai) {
    if (individuo == NULL || novoPai == NULL)
        return 0;

    individuo->pai = novoPai;
    return 1;
}

int inserirMae(No *individuo, No *novaMae) {
    if (individuo == NULL || novaMae == NULL)
        return 0;

    individuo->mae = novaMae;
    return 1;
}

int inserirIrmao(No *individuo, No *novoIrmao) {
    No *atual;

    if (individuo == NULL || novoIrmao == NULL) return 0;

    novoIrmao->pai = individuo->pai;
    novoIrmao->mae = individuo->mae;
    novoIrmao->proximoIrmao = NULL;

    atual = individuo;
    while (atual->proximoIrmao != NULL)
        atual = atual->proximoIrmao;

    atual->proximoIrmao = novoIrmao;
    return 1;
}

void imprimirIndentacao(int nivel) {
    int i;
    for (i = 0; i < nivel; i++)
        printf("    ");
}

void imprimirPessoa(char *rotulo, No *pessoa, int nivel) {
    if (pessoa == NULL)
        return;

    imprimirIndentacao(nivel);
    printf("%s: %s %s\n", rotulo, pessoa->nome, pessoa->sobrenome);
}

void imprimirArvoreRecursiva(No *raiz, int nivel, int imprimeRaiz, int esconderPai, int esconderMae) {
    No *irmao;

    if (raiz == NULL) return;
 
    if (imprimeRaiz)
        imprimirPessoa("Raiz", raiz, nivel);

    irmao = raiz->proximoIrmao;
    while (irmao != NULL) {
        imprimirPessoa("Irmao", irmao, nivel + 1);

        if (irmao->pai != raiz->pai)
            imprimirArvoreRecursiva(irmao, nivel+2, 0, 0, 1);
        if(irmao->mae != raiz->mae)
            imprimirArvoreRecursiva(irmao, nivel+2, 0, 1, 0);

        irmao = irmao->proximoIrmao;
    }

    if (!esconderMae && raiz->mae != NULL) {
        imprimirPessoa(esconderPai ? "Mae (diferente)" : "Mae", raiz->mae, nivel + 1);
        imprimirArvoreRecursiva(raiz->mae, nivel + 2, 0, 0, 0);
    }

    if (!esconderPai && raiz->pai != NULL) {
        imprimirPessoa(esconderMae ? "Pai (difernte)" : "Pai", raiz->pai, nivel + 1);
        imprimirArvoreRecursiva(raiz->pai, nivel + 2, 0, 0, 0);
    }
}

void imprimirArvoreGenealogica(No *raiz) {
    imprimirArvoreRecursiva(raiz, 0, 0, 0, 0);
}

void desvincularPaisDosIrmaosSeguintes(No *irmao, No *pai, No *mae) {
    No *atual = irmao;

    while (atual != NULL) {
        if (atual->pai == pai)
            atual->pai = NULL;
        if (atual->mae == mae)
            atual->mae = NULL;
        atual = atual->proximoIrmao;
    }
}

void freeArvore(No *raiz) {
    No *pai;
    No *mae;
    No *proximoIrmao;

    if (raiz == NULL)
        return;

    pai = raiz->pai;
    mae = raiz->mae;
    proximoIrmao = raiz->proximoIrmao;

    if (proximoIrmao != NULL)
        desvincularPaisDosIrmaosSeguintes(proximoIrmao, pai, mae);

    freeArvore(pai);
    freeArvore(mae);
    freeArvore(proximoIrmao);
    free(raiz);
}

