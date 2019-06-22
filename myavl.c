/* Mihael Scofield de Azevedo - GRR 20182621 */
/* Main onde leio arquivo de entrada, manipulo minha 
árvore e crio o arquivo de saída */

#include "includes.h"

int main(void) {
	/* "Cultivação" da Árvore */
	char operacao;
	int chave;
	struct noh *raiz;

	raiz = NULL; // "Prepara o solo" para minha árvore.
	operacao = getchar(); // Vê operação inicial.
	while (operacao != EOF) {
		switch (operacao) {
		case 'i': 
			scanf("%d", &chave); // Le chave para atualizar minha árvore.
			raiz = insere_AVL(raiz, chave);
			break;

		case 'r':
			scanf("%d", &chave);
			raiz = remove_AVL(raiz, chave); 			
			break;

		default: // Ignora outros comandos.
			break;
		}
		operacao = getchar(); // Atualiza operação.
	}

	/* Impressão da árvore */
	em_ordem(raiz, 0);

	/* Finalização */
	printf("\n");
	return 0;
}