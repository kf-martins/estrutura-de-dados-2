#include "arvore-n-aria.h"
#include <stdio.h>

int main(void) {
    No *raiz = inicializar("Lucas", "Oliveira", data(10, 5, 2000));
    No *pai = criarNo("Joao", "Oliveira", data(2, 3, 1970));
    No *mae = criarNo("Maria", "Souza", data(15, 7, 1975));

    inserirPai(raiz, pai);
    inserirMae(raiz, mae);

    No *irmao1 = criarNo("Pedro", "Oliveira", data(1, 1, 1998));
    No *irmao2 = criarNo("Julia", "Oliveira", data(20, 8, 2002));

    inserirIrmao(raiz, irmao1);
    inserirIrmao(raiz, irmao2);

    No *irmaoDif = criarNo("Bruno", "Oliveira", data(5, 5, 2005));
    inserirIrmao(raiz, irmaoDif);

    No *paiDif = criarNo("Carlos", "Ferreira", data(10, 10, 1972));
    No *bruno = buscarFamiliar(raiz, "Bruno", "Oliveira");
    inserirPai(bruno, paiDif);
    inserirMae(bruno, mae);

    No *avoMaterno = criarNo("Jose", "Souza", data(1, 1, 1950));
    No *avoMaterna = criarNo("Ana", "Souza", data(2, 2, 1952));
    No *tia = criarNo("Clara", "Souza", data(3, 3, 1980));

    No *maria = buscarFamiliar(raiz, "Maria", "Souza");
    inserirPai(maria, avoMaterno);
    inserirMae(maria, avoMaterna);
    inserirIrmao(maria, tia);

    No *avoPaterno = criarNo("Antonio", "Oliveira", data(4, 4, 1945));
    No *avoPaterna = criarNo("Rita", "Oliveira", data(5, 5, 1948));
    No *tio = criarNo("Paulo", "Oliveira", data(6, 6, 1972));

    No *joao = buscarFamiliar(raiz, "Joao", "Oliveira");
    inserirPai(joao, avoPaterno);
    inserirMae(joao, avoPaterna);
    inserirIrmao(joao, tio);

    No *avoDif1 = criarNo("Roberto", "Ferreira", data(8, 8, 1940));
    No *avoDif2 = criarNo("Helena", "Ferreira", data(9, 9, 1943));

    No *carlos = buscarFamiliar(raiz, "Carlos", "Ferreira");
    inserirPai(carlos, avoDif1);
    inserirMae(carlos, avoDif2);


    printf("Arvore genealogica:\n");
    imprimirArvoreGenealogica(raiz);

    freeArvore(raiz);
    return 0;
}