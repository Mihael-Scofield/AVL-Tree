/* Mihael Scofield de Azevedo - GRR 20182621 */
/* Aqui estão as estruturas utilizadas no meu programa. */

struct noh {
	struct noh *esq;
	struct noh *dir;
	int chave;
	int altura;
};