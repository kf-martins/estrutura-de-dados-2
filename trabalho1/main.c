#include "arvore-n-aria.h"
#include <stdio.h>

void ShowMenu() {
    printf("\n--- MENU ---\n");
    printf("1 - Inserir Irmao\n");
    printf("2 - Inserir Mae\n");
    printf("3 - Inserir Pai\n");
    printf("4 - Remover Irmao\n");
    printf("5 - Remover Mae\n");
    printf("6 - Remover Pai\n");
    printf("7 - Imprimir Arvore Completa\n");
    printf("8 - Buscar e Imprimir Pessoa por ID\n");
    printf("9 - Buscar e Imprimir Pessoa por Nome\n");
    printf("10 - Sair\n");
    printf("Escolha uma opcao: ");
}

No* pedirDadosNovoNo() {
    char nome[26], sobrenome[51];
    int d, m, a;
    printf("Nome: ");
    scanf("%s", nome);
    printf("Sobrenome: ");
    scanf("%s", sobrenome);
    printf("Data de Nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &d, &m, &a);
    return criarNo(nome, sobrenome, data(d, m, a));
}

No* obterOuCriarParente(No *raiz, char *tipoParente) {
    int jaExiste;
    int idParente;
    No *parente;

    printf("Esse %s ja esta na arvore? (1=Sim, 0=Nao): ", tipoParente);
    scanf("%d", &jaExiste);

    if (jaExiste) {
        printf("Informe o ID do %s: ", tipoParente);
        scanf("%d", &idParente);

        parente = buscarId(raiz, idParente);
        if (parente == NULL) {
            printf("Erro: %s com ID #%d nao encontrado(a).\n", tipoParente, idParente);
            return NULL;
        }

        return parente;
    }

    printf("Dados do novo(a) %s:\n", tipoParente);
    return pedirDadosNovoNo();
}

int main(void) {
    printf("Configuracao inicial da arvore (Raiz):\n");
    No *raiz = pedirDadosNovoNo();
    printf("ID da raiz: #%d\n\n", raiz->id);
    
    printf("Insira a mae da raiz:\n");
    No *mae_raiz = pedirDadosNovoNo();
    inserirMae(raiz, mae_raiz);
    printf("Mae inserida com sucesso! ID: #%d\n\n", mae_raiz->id);
    
    printf("Insira o pai da raiz:\n");
    No *pai_raiz = pedirDadosNovoNo();
    inserirPai(raiz, pai_raiz);
    printf("Pai inserido com sucesso! ID: #%d\n\n", pai_raiz->id);
    
    int opcao = 0;
    int idPessoa;
    int idIrmaoRemover;
    int mesmosPais;
    char nomeBusca[26], sobrenomeBusca[51];
    No *referencia, *novo;

    while (opcao != 10) {
        ShowMenu();
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 3) {
            printf("\nID da pessoa para inserir o parente: ");
            scanf("%d", &idPessoa);

            referencia = buscarId(raiz, idPessoa);

            if (referencia == NULL) {
                printf("Erro: Pessoa com ID #%d nao encontrada!\n", idPessoa);
                continue;
            }

            switch (opcao) {
                case 1:
                    printf("Dados do novo irmao:\n");
                    novo = pedirDadosNovoNo();

                    printf("Usar mesmos pais da pessoa de referencia? (1=Sim, 0=Nao): ");
                    scanf("%d", &mesmosPais);
                    mesmosPais = mesmosPais ? 1 : 0;

                    inserirIrmao(referencia, novo, mesmosPais);
                    printf("Irmao inserido com sucesso. ID: #%d\n", novo->id);
                    break;
                case 2:
                    novo = obterOuCriarParente(raiz, "mae");
                    if (novo == NULL)
                        break;

                    inserirMae(referencia, novo);
                    printf("Mae inserida com sucesso. ID: #%d\n", novo->id);
                    break;
                case 3:
                    novo = obterOuCriarParente(raiz, "pai");
                    if (novo == NULL)
                        break;

                    inserirPai(referencia, novo);
                    printf("Pai inserido com sucesso. ID: #%d\n", novo->id);
                    break;
            }
        } else if (opcao == 4) {
            printf("ID do irmao a remover: ");
            scanf("%d", &idIrmaoRemover);

            if (idIrmaoRemover == raiz->id) {
                printf("Nao e permitido remover a raiz por esta opcao.\n");
                continue;
            }

            if (removerIrmao(raiz, idIrmaoRemover))
                printf("Irmao removido com sucesso.\n");
            else
                printf("Falha ao remover irmao. Verifique o ID informado.\n");
        } else if (opcao == 5) {
            printf("\nID da pessoa para remover a mae: ");
            scanf("%d", &idPessoa);
            referencia = buscarId(raiz, idPessoa);

            if (referencia == NULL) {
                printf("Erro: Pessoa com ID #%d nao encontrada!\n", idPessoa);
                continue;
            }

            if (removerMae(referencia))
                printf("Mae removida com sucesso.\n");
            else
                printf("Falha ao remover mae.\n");
        } else if (opcao == 6) {
            printf("\nID da pessoa para remover o pai: ");
            scanf("%d", &idPessoa);
            referencia = buscarId(raiz, idPessoa);

            if (referencia == NULL) {
                printf("Erro: Pessoa com ID #%d nao encontrada!\n", idPessoa);
                continue;
            }

            if (removerPai(referencia))
                printf("Pai removido com sucesso.\n");
            else
                printf("Falha ao remover pai.\n");
        } else if (opcao == 7) {
            printf("\n--- ARVORE GENEALOGICA ---\n");
            imprimirArvoreGenealogica(raiz);
        } else if (opcao == 8) {
            printf("\nID da pessoa a buscar: ");
            scanf("%d", &idPessoa);
            referencia = buscarId(raiz, idPessoa);
            imprimirDadosPessoa(referencia);
        } else if (opcao == 9) {
            printf("\nNome da pessoa a buscar: ");
            scanf("%25s", nomeBusca);
            printf("Sobrenome da pessoa a buscar: ");
            scanf("%50s", sobrenomeBusca);

            referencia = buscarFamiliar(raiz, nomeBusca, sobrenomeBusca);
            imprimirDadosPessoa(referencia);
        } else if (opcao == 10) {
            printf("Saindo e liberando memoria...\n");
        } else {
            printf("Opcao invalida!\n");
        }
    }

    freeArvore(raiz);
    return 0;
}





