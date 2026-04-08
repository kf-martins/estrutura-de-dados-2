#include "arvore-n-aria.h"
#include <stdio.h>

void printResultado(char *nome, int ok) {
    printf("[%s] %s\n", ok ? "OK" : "ERRO", nome);
}

int main(void) {
    printf("=== TESTES DA ARVORE ===\n\n");

    No *raiz = criarNo("Ana", "Silva", data(10, 1, 2000));
    No *pai1 = criarNo("Joao", "Silva", data(20, 2, 1970));
    No *mae1 = criarNo("Maria", "Silva", data(30, 3, 1972));
    No *irmao1 = criarNo("Bruno", "Silva", data(5, 5, 2002));
    No *irmao2 = criarNo("Carla", "Silva", data(6, 6, 2004));
    No *pai2 = criarNo("Pedro", "Silva", data(1, 1, 1968));

    if (!raiz || !pai1 || !mae1 || !irmao1 || !irmao2 || !pai2) {
        printf("Falha ao criar nos. Encerrando.\n");
        return 1;
    }

    printf("IDs criados:\n");
    printf("  raiz=%d pai1=%d mae1=%d irmao1=%d irmao2=%d pai2=%d\n\n",
           raiz->id, pai1->id, mae1->id, irmao1->id, irmao2->id, pai2->id);

    printResultado("Inserir pai da raiz", inserirPai(raiz, pai1));
    printResultado("Inserir mae da raiz", inserirMae(raiz, mae1));
    printResultado("Inserir irmao1 com mesmosPais=1", inserirIrmao(raiz, irmao1, 1));
    printResultado("Inserir irmao2 com mesmosPais=0", inserirIrmao(raiz, irmao2, 0));

    printResultado("irmao1 herdou pai", irmao1->pai == pai1);
    printResultado("irmao1 herdou mae", irmao1->mae == mae1);
    printResultado("irmao2 sem pai", irmao2->pai == NULL);
    printResultado("irmao2 sem mae", irmao2->mae == NULL);

    printf("\nArvore apos insercoes:\n");
    imprimirArvoreGenealogica(raiz);

    printResultado("Buscar raiz por ID", buscarId(raiz, raiz->id) == raiz);
    printResultado("Buscar irmao2 por ID", buscarId(raiz, irmao2->id) == irmao2);
    printResultado("Buscar por nome (Ana Silva)", buscarFamiliar(raiz, "Ana", "Silva") == raiz);

    printf("\nRemovendo irmao1 (id=%d) ...\n", irmao1->id);
    printResultado("Remover irmao1", removerIrmao(raiz, irmao1->id));
    printResultado("irmao1 nao encontrado apos remover", buscarId(raiz, irmao1->id) == NULL);
    printResultado("irmao2 continua na arvore", buscarId(raiz, irmao2->id) == irmao2);
    printResultado("encadeamento de irmaos preservado", raiz->proximoIrmao == irmao2);

    printResultado("Remover pai da raiz", removerPai(raiz));
    printResultado("Remover mae da raiz", removerMae(raiz));
    printResultado("raiz ficou sem pai", raiz->pai == NULL);
    printResultado("raiz ficou sem mae", raiz->mae == NULL);

    printResultado("Inserir novo pai da raiz", inserirPai(raiz, pai2));
    printResultado("novo pai atribuido", raiz->pai == pai2);

    printf("\nArvore final antes do free:\n");
    imprimirArvoreGenealogica(raiz);

    printf("\nLiberando arvore...\n");
    freeArvore(raiz);

    printf("Fim dos testes manuais.\n");
    return 0;
}
