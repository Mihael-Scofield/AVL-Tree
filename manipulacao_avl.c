/* Mihael Scofield de Azevedo - GRR 20182621 */
/* Aqui faço as manipulações da árvore em si. */

#include "includes.h"

/* ------------ Funções Utilitárias ------------ */

/* Responsável pela criação de nós */
struct noh* cria_no(int chave) {
	struct noh* novo_no;

	novo_no = (struct noh *) malloc(sizeof(struct noh));
	novo_no->esq = NULL;
	novo_no->dir = NULL;
	novo_no->chave = chave;
	novo_no->altura = 0;

	return novo_no;
}

/* Função que pega a altura da sub-árvore, afim de evitar Seg Fold com altura de NULL */
int sub_altura(struct noh* sub_raiz) {
	if (sub_raiz == NULL)
		return -1;
	return sub_raiz->altura;
}

/* Pequena função para retornar a maior altura entre duas sub-árvores. */
int num_maior(int a, int b) {
	return (a > b)? a : b;
}

/* Função que rotaciona a direita de um nó */
struct noh* rotacao_dir(struct noh* y) {
	/* Definição dos nós conforme diagrama de rotação */
	struct noh* x;
	struct noh* z;

	/* Definição de quem será rotacionado. */
	x = y->esq;
	z = x->dir;

	/* Rotação propripriamente dita, */
	x->dir = y;
	y->esq = z;

	/* Atualização das alturas. */
	y->altura = 1 + num_maior(sub_altura(y->esq), sub_altura(y->dir));
	x->altura = 1 + num_maior(sub_altura(x->esq), sub_altura(x->dir));

	/* Retorno do nó rotacionado. */
	return x;
}

/* Função que rotaciona a esquerda de um nó */
struct noh* rotacao_esq(struct noh* x) {
	/* Definição dos nós conforme diagrama de rotação */
	struct noh* y;
	struct noh* z; 

	/* Definição de quem será rotacionado */
	y = x->dir;
	z = y->esq;

	/* Rotação propriamente dita */
	y->esq = x;
	x->dir = z;

	/* Atualização das alturas */
	x->altura = 1 + num_maior(sub_altura(x->esq), sub_altura(x->dir));	
	y->altura = 1 + num_maior(sub_altura(y->esq), sub_altura(y->dir));

	/* Retorno do nó rotacionado */
	return y;
}

/* Função que imprime a árvore em ordem */
void em_ordem(struct noh* raiz, int profundidade) {
	if (raiz != NULL) {
		em_ordem(raiz->esq, profundidade+1); // Vai à extrema esquerda
		printf("%d,%d\n", raiz->chave, profundidade); // Imprime raiz
		em_ordem(raiz->dir, profundidade+1); // Extrema direita.
	}
}

/* Função que ira buscar nó mais a direita, da sub-árvore da esquerda do nó atual */
struct noh* busca_antecessor(struct noh* no) {
	struct noh* no_atual = no;
	while (no_atual->dir != NULL) { // Desço até encontrar a folha
		no_atual = no_atual->dir;
	}

	return no_atual;
}

/* Retorna o fator de balanceamento do nó atal */
int verif_equilibrio(struct noh* no) { 
    if (no == NULL) 
        return 0; 
    return (sub_altura(no->esq) - sub_altura(no->dir)); 
} 

/* -------- Fim das Funções Utilitárias -------- */


/* ------------ Funções Principais ------------ */

/* Função que faz inserção na AVL */
struct noh* insere_AVL(struct noh* raiz, int chave) {
	/* Inserção por propriedade BST */
	if (raiz == NULL) { // "Fim" da árvore.
		raiz = cria_no(chave);
		return raiz;
	}
	if (chave < raiz->chave) { // "Ramificação" da árvore.
		raiz->esq = insere_AVL(raiz->esq, chave);
	}
	else if (chave > raiz-> chave) {
		raiz->dir = insere_AVL(raiz->dir, chave);
	} // A partir daqui, começo a sair de minha resursão, jogando meu problema para cima.

	/* Atualização de altura do nó atual e verificação da propriedade de AVL. */
	raiz->altura = 1 + num_maior(sub_altura(raiz->esq), sub_altura(raiz->dir));

	int equilibrio;
	equilibrio = verif_equilibrio(raiz);

	/* Casos distintos de balanceamento */
	if (equilibrio >= -1 && equilibrio <= 1) 
		return raiz; // Sub-Árvore não necessita de balanceamento.

	// São 2 casos de cada lado para resolver
	if (equilibrio > 1 && chave > raiz->esq->chave) { // Zig-Zag esq.
		raiz->esq = rotacao_esq(raiz->esq); // Transformo em Zig-Zig.
		return rotacao_dir(raiz); // Equilibro e repito o processo pros demais casos.
	}
	if (equilibrio < -1 && chave < raiz->dir->chave) { // Zig-Zag dir.
		raiz->dir = rotacao_dir(raiz);
		return rotacao_esq(raiz);
	}
	if (equilibrio > 1 && chave < raiz->esq->chave) // Zig-Zig esq.
		return rotacao_dir(raiz);

	return rotacao_esq(raiz); // (equilibrio < -1 && chave > raiz->dir->chave) // Zig-Zig dir.
}

/* Função que faz remoção na AVL */
struct noh* remove_AVL(struct noh* raiz, int chave) {
	/* Remoção por propriedade BST, pelo antecessor*/
	if (raiz == NULL) {
		return raiz; // Árvore vázia.
	}

	if (chave < raiz->chave) { // "Subo" no galho da esquerda.
		raiz->esq = remove_AVL(raiz->esq, chave);
	}
	else if (chave > raiz->chave) {
		raiz->dir = remove_AVL(raiz->dir, chave);
	}
	else { // chave == raiz->chave, encontrei quem quero excluir.
		if ( (raiz->esq == NULL) || (raiz->dir == NULL) ) { // Com apenas um ou nenhum filho.
			struct noh* aux; // Nó de auxilio para facilitar a exclusão.
			aux = (raiz->esq)? raiz->esq: raiz->dir; // Se o filho a esquerda não é nulo, aux = esquerda, caso contrario, aux = direita.
			if (aux == NULL) { // Neste caso, nó atual não possui filho algum, ou seja, ele é folha.
				aux = raiz;
				raiz = NULL; // Simplesmente "podo" ele da árvore
			}
			else{ // Aqui, ele possui um filho
				*raiz = *aux; // Subescreve o filho na posição do pai.
			} 
			free(aux); // libero memoria
		}
		else { // Nó com dois filhos. Devo buscar seu antecessor
			struct noh* antecessor;
			antecessor = busca_antecessor(raiz->esq);
			raiz->chave = antecessor->chave; // Coloco o antecessor em seu "posto" novo.
			raiz->esq = remove_AVL(raiz->esq, antecessor->chave); // Deleto o posto antigo do antecessor.
		}
	}

	if (raiz == NULL) { // Para evitar os SegFolds que estavam dando, aqui impeço de fazer os calculos com nó nulo.
		return raiz;
	}

	/* Atualização da altura do nó atual e verificação da propriedade AVL */
	raiz->altura = 1 + num_maior(sub_altura(raiz->esq), sub_altura(raiz->dir));

	int equilibrio;
	equilibrio = verif_equilibrio(raiz);

	/* Casos de balanceamento */
	if (equilibrio > 1 && verif_equilibrio(raiz->esq) < 0) { // Zig-Zag esq.
		raiz->esq = rotacao_esq(raiz->esq);
		return rotacao_dir(raiz);
	}
	if (equilibrio < -1 && verif_equilibrio(raiz->dir) > 0) { // Zig-Zag dir.
		raiz->dir = rotacao_dir(raiz->dir);
		return rotacao_esq(raiz);
	}
	if (equilibrio > 1 && verif_equilibrio(raiz->esq) >= 0) { // Zig-Zig esq.
		return rotacao_dir(raiz);
	}

	if (equilibrio < -1 && verif_equilibrio(raiz->dir) <= 0) { // Zig-Zig dir.
		return rotacao_esq(raiz);
	}

	return raiz;
}

/* -------- Fim das Funções Principais -------- */