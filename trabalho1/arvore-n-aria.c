#include "arvore-n-aria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int proximoId = 1;

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
    novoNo->id = proximoId++;
    novoNo->refQuant = 0;

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

No *buscarId(No *raiz, int id) {
    No *p;

    if (raiz == NULL) return NULL;

    if (raiz->id == id) return raiz;

    p = buscarId(raiz->pai, id);
    if (p != NULL) return p;

    p = buscarId(raiz->mae, id);
    if (p != NULL) return p;

    return buscarId(raiz->proximoIrmao, id);
}

void reterNo(No *no) {
    if (no != NULL)
        no->refQuant++;
}

void atribuirReferencia(No **campo, No *novoValor) {
    if (campo == NULL)
        return;

    No *valorAntigo = *campo;
    if (valorAntigo == novoValor)
        return;

    if (novoValor != NULL)
        reterNo(novoValor);

    *campo = novoValor;

    if (valorAntigo != NULL)
        liberarNo(valorAntigo);
}

void liberarNo(No *no) {
    if (no == NULL)
        return;

    if (no->refQuant > 0)
        no->refQuant--;

    if (no->refQuant > 0)
        return;

    atribuirReferencia(&no->pai, NULL);
    atribuirReferencia(&no->mae, NULL);
    atribuirReferencia(&no->proximoIrmao, NULL);

    free(no);
}

int buscaIrmaoAux(No *raiz, int idIrmao, No **anterior, No **alvo) {
    if (raiz == NULL || anterior == NULL || alvo == NULL)
        return 0;

    No *prev = raiz;
    No *atual = raiz->proximoIrmao;

    while (atual != NULL) {
        if (atual->id == idIrmao) {
            *anterior = prev;
            *alvo = atual;
            return 1;
        }

        prev = atual;
        atual = atual->proximoIrmao;
    }

    if (buscaIrmaoAux(raiz->pai, idIrmao, anterior, alvo))
        return 1;

    if (buscaIrmaoAux(raiz->mae, idIrmao, anterior, alvo))
        return 1;

    return buscaIrmaoAux(raiz->proximoIrmao, idIrmao, anterior, alvo);
}

int inserirPai(No *individuo, No *novoPai) {
    if (individuo == NULL || novoPai == NULL)
        return 0;

    atribuirReferencia(&individuo->pai, novoPai);
    return 1;
}

int inserirMae(No *individuo, No *novaMae) {
    if (individuo == NULL || novaMae == NULL)
        return 0;

    atribuirReferencia(&individuo->mae, novaMae);
    return 1;
}

int inserirIrmao(No *individuo, No *novoIrmao, int mesmosPais) {
    No *atual;

    if (individuo == NULL || novoIrmao == NULL) return 0;

    atribuirReferencia(&novoIrmao->pai, mesmosPais ? individuo->pai : NULL);
    atribuirReferencia(&novoIrmao->mae, mesmosPais ? individuo->mae : NULL);
    atribuirReferencia(&novoIrmao->proximoIrmao, NULL);

    atual = individuo;
    while (atual->proximoIrmao != NULL)
        atual = atual->proximoIrmao;

    atribuirReferencia(&atual->proximoIrmao, novoIrmao);
    return 1;
}

int removerPai(No *individuo) {
    if (individuo == NULL || individuo->pai == NULL)
        return 0;

    atribuirReferencia(&individuo->pai, NULL);
    return 1;
}

int removerMae(No *individuo) {
    if (individuo == NULL || individuo->mae == NULL)
        return 0;

    atribuirReferencia(&individuo->mae, NULL);
    return 1;
}

int removerIrmao(No *raiz, int idIrmao) {
    if (raiz == NULL)
        return 0;

    No *anterior = NULL;
    No *alvo = NULL;

    if (!buscaIrmaoAux(raiz, idIrmao, &anterior, &alvo))
        return 0;

    reterNo(alvo);

    No *proximoDoAlvo = alvo->proximoIrmao;
    
    atribuirReferencia(&anterior->proximoIrmao, proximoDoAlvo);
    atribuirReferencia(&alvo->proximoIrmao, NULL);

    liberarNo(alvo);

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
    printf("%s: #%d %s %s\n", rotulo, pessoa->id, pessoa->nome, pessoa->sobrenome);
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
    imprimirArvoreRecursiva(raiz, 0, 1, 0, 0);
}

void imprimirDadosPessoa(No *pessoa) {
    No *irmao;

    if (pessoa == NULL) {
        printf("Pessoa nao encontrada!\n");
        return;
    }

    printf("\n----- DADOS DA PESSOA -----\n");
    printf("ID: #%d\n", pessoa->id);
    printf("Nome: %s %s\n", pessoa->nome, pessoa->sobrenome);
    printf("Data de Nascimento: %02d/%02d/%04d\n", pessoa->dataNascimento.dia, pessoa->dataNascimento.mes, pessoa->dataNascimento.ano);

    if (pessoa->pai != NULL)
        printf("Pai: #%d %s %s\n", pessoa->pai->id, pessoa->pai->nome, pessoa->pai->sobrenome);
    else
        printf("Pai: (desconhecido)\n");

    if (pessoa->mae != NULL)
        printf("Mae: #%d %s %s\n", pessoa->mae->id, pessoa->mae->nome, pessoa->mae->sobrenome);
    else
        printf("Mae: (desconhecida)\n");

    if (pessoa->proximoIrmao != NULL) {
        printf("\nIrmaos:\n");
        irmao = pessoa->proximoIrmao;
        while (irmao != NULL) {
            printf("  - #%d %s %s\n", irmao->id, irmao->nome, irmao->sobrenome);
            irmao = irmao->proximoIrmao;
        }
    } else {
        printf("\nIrmaos: nenhum\n");
    }
    printf("\n");
}

void freeArvore(No *raiz) {
    reterNo(raiz);
    liberarNo(raiz);
}

