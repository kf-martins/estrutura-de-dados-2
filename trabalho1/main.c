#include "arvore-n-aria.h"
#include <stdio.h>

void ShowMenu() {
    printf("\n--- MENU ---\n");
    printf("1 - Inserir Irmao\n");
    printf("2 - Inserir Mae\n");
    printf("3 - Inserir Pai\n");
    printf("4 - Imprimir Arvore\n");
    printf("5 - Sair\n");
    printf("Escolha uma opcao: ");
}

No* pedirDadosNovoNo() {
    char nome[50], sobrenome[200];
    int d, m, a;
    printf("Nome: ");
    scanf("%s", nome);
    printf("Sobrenome: ");
    scanf("%s", sobrenome);
    printf("Data de Nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &d, &m, &a);
    return criarNo(nome, sobrenome, data(d, m, a));
}

int main(void) {
    printf("Configuracao inicial da arvore (Raiz):\n");
    No *raiz = pedirDadosNovoNo();
    printf("Insira a mae da raiz:\n");
    No *mae_raiz = pedirDadosNovoNo();
    inserirMae(raiz, mae_raiz);
    printf("Insira o pai da raiz:\n");
    No *pai_raiz = pedirDadosNovoNo();
    inserirPai(raiz, pai_raiz);
    
    int opcao = 0;
    char buscaNome[50], buscaSobrenome[50];

    while (opcao != 5) {
        ShowMenu();
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 3) {
            printf("\nDe quem voce deseja inserir o parente?\n");
            printf("Nome: ");
            scanf("%s", buscaNome);
            printf("Sobrenome: ");
            scanf("%s", buscaSobrenome);

            No *referencia = buscarFamiliar(raiz, buscaNome, buscaSobrenome);

            if (referencia == NULL) {
                printf("Erro: Familiar nao encontrado!\n");
                continue;
            }

            printf("Dados do novo parente:\n");
            No *novo = pedirDadosNovoNo();

            switch (opcao) {
                case 1:
                    inserirIrmao(referencia, novo);
                    printf("Irmao inserido com sucesso.\n");
                    break;
                case 2:
                    inserirMae(referencia, novo);
                    printf("Mae inserida com sucesso.\n");
                    break;
                case 3:
                    inserirPai(referencia, novo);
                    printf("Pai inserido com sucesso.\n");
                    break;
            }
        } else if (opcao == 4) {
            printf("\n--- ARVORE GENEALOGICA ---\n");
            imprimirArvoreGenealogica(raiz);
        } else if (opcao == 5) {
            printf("Saindo e liberando memoria...\n");
        } else {
            printf("Opcao invalida!\n");
        }
    }

    freeArvore(raiz);
    return 0;
}





