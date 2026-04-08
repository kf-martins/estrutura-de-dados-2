# Arvore Genealogica (N-aria)

Biblioteca em C para representar uma arvore de antecessores (pai/mae) com encadeamento de irmaos. Feito para a disciplina de Estrutura de Dados II da Universidade Estadual de Londrina (UEL). 
- Professor: Arthur Alexandre Artoni
- Alunos/autores: 
    - Kauã Felipe Martins
    - Leonardo Madeira Alves Pereira

## Estrutura base

- Estrutura `No`: [arvore-n-aria.h#L10](arvore-n-aria.h#L10)
- Estrutura `Date`: [arvore-n-aria.h#L4](arvore-n-aria.h#L4)

## Funcoes publicas

### Criacao e busca

- [data](arvore-n-aria.c#L8): cria uma data (`dia/mes/ano`).
- [criarNo](arvore-n-aria.c#L23): aloca e inicializa um no (com `id` automatico).
- [inicializar](arvore-n-aria.c#L44): atalho para criar a raiz.
- [buscarFamiliar](arvore-n-aria.c#L48): busca por `nome + sobrenome`.
- [buscarId](arvore-n-aria.c#L64): busca por `id`.

### Insercoes

- [inserirPai](arvore-n-aria.c#L146): atribui/troca o pai de um individuo.
- [inserirMae](arvore-n-aria.c#L154): atribui/troca a mae de um individuo.
- [inserirIrmao](arvore-n-aria.c#L162): adiciona irmao ao final da lista de irmaos. `mesmosPais=1` herda pai/mae do individuo base.

### Remocoes

- [removerPai](arvore-n-aria.c#L179): remove o vinculo de pai.
- [removerMae](arvore-n-aria.c#L187): remove o vinculo de mae.
- [removerIrmao](arvore-n-aria.c#L195): remove um irmao por `id` na arvore toda.
- [buscaIrmaoAux](arvore-n-aria.c#L119): auxiliar para achar `anterior + alvo` na remocao de irmao.

### Impressao e liberacao

- [imprimirArvoreGenealogica](arvore-n-aria.c#L262): imprime a arvore completa.
- [imprimirDadosPessoa](arvore-n-aria.c#L266): imprime os dados de uma pessoa.
- [freeArvore](arvore-n-aria.c#L302): libera a estrutura a partir da raiz.

## Como funciona a gerencia de memoria (reterNo/liberarNo/atribuirReferencia)

Funcoes envolvidas:

- [reterNo](arvore-n-aria.c#L97)
- [liberarNo](arvore-n-aria.c#L80)
- [atribuirReferencia](arvore-n-aria.c#L102)

Resumo:

1. `atribuirReferencia` troca um ponteiro com seguranca.
2. Antes de trocar, ela faz `reterNo(novoValor)` (incrementa `refQuant` do novo alvo).
3. Depois de trocar, ela chama `liberarNo(valorAntigo)` para soltar a referencia antiga.
4. `liberarNo` decrementa `refQuant`; so libera de fato quando chega a zero.

Por que nao entra em loop infinito:

- `atribuirReferencia` retorna imediatamente se `valorAntigo == novoValor`.
- Em `liberarNo`, ao limpar `pai/mae/proximoIrmao`, cada campo e setado para `NULL` via `atribuirReferencia`; na proxima passagem nao existe mais referencia para processar naquele campo.
- O `refQuant` impede liberar no ainda referenciado por outros caminhos da arvore.

## Uso rapido

Compilar app principal:

```bash
gcc -Wall -Wextra -pedantic -std=c11 main.c arvore-n-aria.c -o main
```

Compilar teste simples:

```bash
gcc -Wall -Wextra -pedantic -std=c11 testes.c arvore-n-aria.c -o testes
```
