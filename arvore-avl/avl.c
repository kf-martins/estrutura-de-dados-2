/******************************************************************************/
/*              Este programa gerencia arvores AVL                            */
/*  Arvores AVL sao arvores balanceadas na altura.                            */
/*  O nome AVL vem de seus criadores Adelson Velsky e Landis, cuja primeira   */
/*    referência encontra-se no documento "Algoritmos para organização da     */
/*    informação" de 1962.                                                    */
/******************************************************************************/

#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux {
	TIPOCHAVE chave;
	struct aux *esq;
	struct aux *dir;
	int bal; // fator de balanceamento (0, -1 ou +1) => alt. direita - alt. esquerda
} NO, *PONT;

/* cria um novo (aloca memoria e preenche valores) no com chave=ch e retorna 
       seu endereco */
PONT criarNovoNo(TIPOCHAVE ch){
	PONT novoNo = (PONT)malloc(sizeof(NO));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->chave = ch;
	novoNo->bal = 0;
	return novoNo;
}


// Retorna o maior valor entre dois inteiros
int max(int a, int b){
	if (a>b) return a;
	return b;
}

// Retorna a altura de uma (sub-)arvore
int altura(PONT p){
	if (!p) return -1;
	else return 1 + max(altura(p->esq),altura(p->dir));
}


/* Exibe arvore Em Ordem         */
void exibirArvoreEmOrdem(PONT raiz){
	if (raiz == NULL) return;
	exibirArvoreEmOrdem(raiz->esq);
	printf("%i ",raiz->chave);
	exibirArvoreEmOrdem(raiz->dir);
}

/* Exibe arvore Pre Ordem         */
void exibirArvorePreOrdem(PONT raiz){
	if (raiz == NULL) return;
	printf("%i ",raiz->chave);
	exibirArvorePreOrdem(raiz->esq);
	exibirArvorePreOrdem(raiz->dir);
}

/* Exibe arvore Pos Ordem         */
void exibirArvorePosOrdem(PONT raiz){
	if (raiz == NULL) return;
	exibirArvorePreOrdem(raiz->esq);
	exibirArvorePreOrdem(raiz->dir);
	printf("%i ",raiz->chave);
}

/* Exibe arvore Em Ordem (com parenteses para os filhos)    */
void exibirArvore(PONT raiz){
	if (raiz == NULL) return;
	printf("%i[%i]",raiz->chave,raiz->bal);
	printf("(");     
	exibirArvore(raiz->esq);
	exibirArvore(raiz->dir);
	printf(")");     
}



/* Rotações à direita (LL e LR) 
   Retornará o endereço do nó que será a nova raiz da subárvore originalmente 
   iniciada por p */
PONT rotacaoL(PONT p){ // rotações Left
	printf("Rotacao a esquerda, problema no no: %i\n",p->chave); // debug para acompanhar o processo de rotação.
	PONT u, v; // pronteiros auxiliares para os nós envolvidos na rotação.
	u = p->esq; // u recebe o filho a esquerda de p.
	if(u->bal == -1) {   // LL
		printf("Rotacao LL\n");
		p->esq = u->dir; // o filho a direita de u se torna o filho a esquerda de p, pois u sobe para a posição de p.
		u->dir = p; // p se torna o filho a direita de u.
		p->bal = 0; // após a rotação, o fator de balanceamento de p e u se torna 0, pois a altura das subárvores se iguala.
		u->bal = 0; // o fator de balanceamento de u também é atualizado para 0.
		return u;
	} else if (u->bal == 1) {  // LR
		printf("Rotacao LR\n");
		v = u->dir; // v recebe o filho a direita de u, que será o novo nó raiz da subárvore após a rotação.
		u->dir = v->esq; // o filho a esquerda de v se torna o filho a direita de u, pois v sobe para a posição de p.
		v->esq = u; // u se torna o filho a esquerda de v.
		p->esq = v->dir; // o filho a direita de v se torna o filho a esquerda de p, pois v sobe para a posição de p.
		v->dir = p; // p se torna o filho a direita de v.
		if(v->bal == -1) p->bal = 1; // se o fator de balanceamento de v era -1, significa que a subárvore esquerda de v era mais alta, então após a rotação, o fator de balanceamento de p se torna 1.
		else p->bal = 0; // caso contrário, o fator de balanceamento de p se torna 0, pois a altura das subárvores se iguala.
		if(v->bal == 1) u->bal = -1; // se o fator de balanceamento de v era 1, significa que a subárvore direita de v era mais alta, então após a rotação, o fator de balanceamento de u se torna -1.
		else u->bal = 0; // caso contrário, o fator de balanceamento de u se torna 0, pois a altura das subárvores se iguala.
		v->bal = 0;
		return v;
	}else{   // caso necessario apenas para a exclusao (u->bal == 0)
		printf("Rotacao LL (exclusao)\n");
		p->esq = u->dir; // o filho a direita de u se torna o filho a esquerda de p, pois u sobe para a posição de p.
		u->dir = p; // p se torna o filho a direita de u.
		// p->bal = -1;    desnecessario pois o balanceamento de p nao chegou a ser mudado para -2
		u->bal = 1; // necessário para diferenciar o caso de exclusão do caso de inserção, pois nesse caso a altura da subárvore não mudou, mas a rotação é necessária para corrigir o balanceamento.
		return u;
	}
}

/* Rotações à esquerda (RR e RL) 
   Retornará o endereço do nó que será a nova raiz da subárvore originalmente 
   iniciada por p */
PONT rotacaoR(PONT p){ // rotações Right
	printf("Rotacao a direita, problema no no: %i\n",p->chave);
	PONT u, v; // pronteiros auxiliares para os nós envolvidos na rotação.
	u = p->dir; // u recebe o filho a direita de p.
	if(u->bal == 1) {   // RR
		printf("Rotacao RR\n");
		p->dir = u->esq; // o filho a esquerda de u se torna o filho a direita de p, pois u sobe para a posição de p.
		u->esq = p; // p se torna o filho a esquerda de u.
		p->bal = 0; // após a rotação, o fator de balanceamento de p e u se torna 0, pois a altura das subárvores se iguala.
		u->bal = 0; // o fator de balanceamento de u também é atualizado para 0.
		return u;
	} else if (u->bal == -1){  // RL
		printf("Rotacao RL\n");
		v = u->esq; // v recebe o filho a esquerda de u, que será o novo nó raiz da subárvore após a rotação.
		u->esq = v->dir; // o filho a direita de v se torna o filho a esquerda de u, pois v sobe para a posição de p.
		v->dir = u; // u se torna o filho a direita de v.
		p->dir = v->esq; // o filho a esquerda de v se torna o filho a direita de p, pois v sobe para a posição de p.
		v->esq = p; // p se torna o filho a esquerda de v.
		if(v->bal == 1) p->bal = -1; // se o fator de balanceamento de v era 1, significa que a subárvore direita de v era mais alta, então após a rotação, o fator de balanceamento de p se torna -1.
		else p->bal = 0; // caso contrário, o fator de balanceamento de p se torna 0, pois a altura das subárvores se iguala.
		if(v->bal == -1) u->bal = 1; // se o fator de balanceamento de v era -1, significa que a subárvore esquerda de v era mais alta, então após a rotação, o fator de balanceamento de u se torna 1.
		else u->bal = 0; // caso contrário, o fator de balanceamento de u se torna 0, pois a altura das subárvores se iguala.
		v->bal = 0; // o fator de balanceamento de v se torna 0, pois após a rotação, a altura das subárvores se iguala.
		return v;
	}else{   // caso necessario apenas para a exclusao (u->bal == 0)
		printf("Rotacao RR (exclusao)\n");
		p->dir = u->esq; // o filho a esquerda de u se torna o filho a direita de p, pois u sobe para a posição de p.
		u->esq = p; // p se torna o filho a esquerda de u.
		u->bal = -1; // necessário para diferenciar o caso de exclusão do caso de inserção, pois nesse caso a altura da subárvore não mudou, mas a rotação é necessária para corrigir o balanceamento.
		// p->bal = 1;    desnecessario pois o balanceamento de p nao chegou a ser mudado para 2
		return u;	
	}
}



/* Inserção AVL: p é inicializado com o endereco do nó raiz e 
   *alterou com false                                         */
void inserirAVL(PONT* pp, TIPOCHAVE ch, bool* alterou){
	PONT p = *pp; // ponteiro auxiliar para percorrer a árvore, iniciando pela raiz (pp é um ponteiro para ponteiro, então *pp é o nó raiz).
	if(!p){
		*pp = criarNovoNo(ch); // achou o local para inserir o novo nó
		*alterou = true; // a altura da subárvore aumentou, o que pode desbalancear a árvore
	} else { // nó já existe, deve-se continuar a busca
if(ch == p->chave) *alterou = false; //chave repetida, não altera a árvore pq não insere.
		else if(ch <= p->chave) { // regra avl menor vai a esquerda.
			inserirAVL(&(p->esq), ch, alterou); // chama recursão a esquerda.
			if(*alterou) // Se alterou.
				switch (p->bal) { // calcula balance factor
					case 1 : p->bal = 0; // se era 1 ao colocar um nó a esquerda fica 0.
					*alterou = false; // como nó a direita já existia não muda altura.
					break;
					case 0 : p->bal = -1; // Se era 0 então agora é -1 e altura mudou
					break;
					case -1: *pp = rotacaoL(p); // era -1, ficaria -2, então rotação a esquerda.
					*alterou = false; // a rotação corrige a altura, então não altera mais.
					break;
				}
		} else {
			inserirAVL(&(p->dir), ch, alterou); // regra avl maior vai a direita.
			if(*alterou) // Se alterou.
				switch (p->bal) { // calcula balance factor
					case -1: p->bal = 0; // se era -1 ao colocar um nó a direita fica 0.
					*alterou = false; // como nó a esquerda já existia não muda altura.
					break;
					case 0 : p->bal = 1; // Se era 0 então agora é 1 e altura mudou
					break;
					case 1 : *pp = rotacaoR(p); // era 1, ficaria 2, então rotação a direita.
					*alterou = false;
					break;
				}
		}
	}
}


/* retorna o endereco do NO que contem chave=ch ou NULL caso a chave nao seja
       encontrada. Utiliza busca binaria recursiva                                */
PONT buscaBinaria(TIPOCHAVE ch, PONT raiz){
	if (raiz == NULL) return NULL;
	if (raiz->chave == ch) return raiz;
	if (raiz->chave<ch) 
		return buscaBinaria(ch,raiz->dir);
	return buscaBinaria(ch,raiz->esq);
}  


// Busca binária não recursiva devolvendo o nó pai
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai){
	PONT atual = raiz;
	*pai = NULL;
	while (atual) {
		if(atual->chave == ch)
			return(atual);
		*pai = atual;
		if(ch < atual->chave) atual = atual->esq;
		else atual = atual->dir;
	}
	return(NULL);
}

/* Auxilir da funcao excluirChave, procura a maior chave menor que a chave que 
   serah excluida            */
PONT maiorAEsquerda(PONT p, PONT *ant){
  *ant = p;
  p = p->esq;
  while (p->dir) {
    *ant = p;
    p = p->dir;
  }
  return(p);
}


/* exclui a chave com valor igual a ch   */
bool excluirAVL(PONT* raiz, TIPOCHAVE ch, bool* alterou){
  PONT atual = *raiz; // inicia a busca pela chave a ser excluida a partir da raiz
  if (!atual) { //chave não é a que buscamos
    *alterou = false; // não removi nada, altura não muda.
    return false;
  }
  if (atual->chave == ch){ //achei a chave a ser removida
    PONT substituto, pai_substituto; // ponteiro para eleger substituto.
    if(!atual->esq || !atual->dir) { // tem zero ou um filho
      if(atual->esq) substituto = atual->esq; // se tem filho a esquerda, ele é o substituto
      else substituto = atual->dir; // se tem filho a direita, ele é o substituto. Se não é NULL.
      *raiz = substituto; // o pai do atual agora aponta para o substituto, que pode ser NULL se não tinha filhos.
      free(atual); // libera memória
      *alterou = true; //removi um nó, altura PODE ter mudado.
      return true;
    }
    else {   // tem dois filhos
      substituto = maiorAEsquerda(atual,&pai_substituto); // substituto é o maior nó da subárvore esquerda, pai_substituto é seu pai.
      atual->chave = substituto->chave; // copia a chave do substituto para o nó atual, mantendo a estrutura da árvore. Agora preciso remover o nó substituto, que tem no máximo um filho (filho a esquerda).
      ch = substituto->chave; // continua o codigo excluindo o substituto
    }
  }
  
  bool res; // variável para guardar o resultado da exclusão recursiva.
  if (ch > atual->chave) {
    res = excluirAVL(&(atual->dir), ch, alterou); // chama recursão a direita.
    printf("Excluir recursivo a direita: %i(%i)\n", atual->chave, atual->bal); // debug para acompanhar o processo de exclusão.
    if (*alterou){ // Se alterou, preciso verificar o balanceamento do nó atual e possivelmente realizar rotações.
       switch (atual->bal){ // calcula balance factor
          case 1: atual->bal = 0; // se era 1 ao remover um nó a direita fica 0.
          return true;
          case 0: atual->bal = -1; // Se era 0 então agora é -1 e altura mudou
          *alterou = false; // como nó a esquerda já existia não muda altura.
          return true;
          case -1: *raiz = rotacaoL(atual); // era -1, ficaria -2, então rotação a esquerda.
          if (atual->bal != 0) *alterou = false; // a rotação corrige a altura, então não altera mais.
          return true;
       }
    }
  }else{
    res = excluirAVL(&(atual->esq), ch, alterou); // chama recursão a esquerda.
    printf("Excluir recursivo a esquerda: %i(%i)\n", atual->chave, atual->bal); // debug para acompanhar o processo de exclusão.
    if (*alterou){ // Se alterou, preciso verificar o balanceamento do nó atual e possivelmente realizar rotações.
       switch (atual->bal){ // calcula balance factor
          case -1: atual->bal = 0; // se era -1 ao remover um nó a esquerda fica 0.
          return true;
          case 0: atual->bal = 1; // Se era 0 então agora é 1 e altura mudou
          *alterou = false; // como nó a direita já existia não muda altura.
          return true;
          case 1: *raiz = rotacaoR(atual); // era 1, ficaria 2, então rotação a direita.
          if (atual->bal != 0) *alterou = false; // a rotação corrige a altura, então não altera mais.
          return true;
       }
    }
  }
  return res;
}




/* funcao auxiliar na destruicao (liberacao da memoria) de uma arvore */
void destruirAux(PONT subRaiz){
	if (subRaiz){
		destruirAux(subRaiz->esq);
		destruirAux(subRaiz->dir);
		free(subRaiz);
	}
}

/* libera toda memoria de uma arvore e coloca NULL no valor da raiz    */
void destruirArvore(PONT * raiz){
	destruirAux(*raiz);
	*raiz = NULL;
}


/* inicializa arvore: raiz=NULL */
void inicializar(PONT * raiz){
	*raiz = NULL;
}

int main() {
    PONT raiz;
    inicializar(&raiz);
    bool alterou;
    int opcao, chave;

    printf("--- Gerenciador de Arvore AVL ---\n");

    do {
        printf("\n1 - Inserir chave\n");
        printf("2 - Excluir chave\n");
        printf("3 - Exibir arvore (Parenteses)\n");
        printf("4 - Exibir Em Ordem\n");
        printf("5 - Altura da arvore\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor para inserir: ");
                scanf("%d", &chave);
                inserirAVL(&raiz, chave, &alterou);
                printf("Chave %d inserida.\n", chave);
                break;

            case 2:
                printf("Digite o valor para excluir: ");
                scanf("%d", &chave);
                if (excluirAVL(&raiz, chave, &alterou)) {
                    printf("Chave %d removida com sucesso.\n", chave);
                } else {
                    printf("Chave %d nao encontrada.\n", chave);
                }
                break;

            case 3:
                printf("Estrutura atual: ");
                exibirArvore(raiz);
                printf("\n");
                break;

            case 4:
                printf("Elementos em ordem: ");
                exibirArvoreEmOrdem(raiz);
                printf("\n");
                break;

            case 5:
                printf("Altura da arvore: %d\n", altura(raiz));
                break;

            case 0:
                printf("Destruindo arvore e saindo...\n");
                destruirArvore(&raiz);
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}