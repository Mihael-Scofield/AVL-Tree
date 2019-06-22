/* Mihael Scofield de Azevedo - GRR 20182621 */
/* Cabeçalho das funções usadas para manipular minha árvore. */
/* Este cabeçalho é dividido em funções utilitárias (com várias repetições ao longo do código)
   e em funções principais (com apenas uma repetição aqui, mas várias lá fora) */

/* ------------ Funções Utilitárias ------------ */

/* Responsável pela criação de nós */
struct noh* cria_no(int valor);

/* Função que pega a altura da sub-árvore, afim de evitar Seg. Fold com altura de NULL */
int sub_altura(struct noh* sub_raiz);

/* Pequena função para retornar a maior altura entre duas sub-árvores. */
int num_maior(int a, int b);

/* Função que rotaciona a direita de um nó */
struct noh* rotacao_dir(struct noh* y);

/* Função que rotaciona a esquerda de um nó */
struct noh* rotacao_esq(struct noh* x);

/* Função que imprime a árvore em ordem */
void em_ordem(struct noh* raiz, int profundidade);

/* Função que ira buscar nó mais a direita, da sub-árvore da esquerda do nó atual */
struct noh* busca_antecessor(struct noh* no);

/* Retorna o fator de balanceamento do nó atal */
int verif_equilibrio(struct noh* no);

/* -------- Fim das Funções Utilitárias -------- */


/* ------------ Funções Principais ------------ */

/* Função que faz inserção na AVL */
struct noh* insere_AVL(struct noh* raiz, int chave);

/* Função que faz remoção na AVL */
struct noh* remove_AVL(struct noh* raiz, int chave);

/* -------- Fim das Funções Principais -------- */