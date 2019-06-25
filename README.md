# Árvore AVL

Implementado por Mihael Scofield de Azevedo,
Aplicado como trabalho de Algoritmos e Estruturas de Dados 2 (UFPR) por Eduardo Cunha Almeida em 2019-1

## Resumo
O projeto foi dividido em 5 arquivos, sendo 3 cabeçalhos (.h) e 2 arquivos de implementação (.c). A ideia é que a main trate da leitura e escrita dos arquivos passados enquanto chama o arquivo responsável pela manipulação da AVL.

## Arquivos
  - 1 - Includes.h:
  
  Um arquivo simples, responsável por fazer a inclusão das bibliotecas e dos demais arquivos cabeçalhos (.h) utilizados no projeto.
  
  - 2 - Structs.h:
  
  Também um arquivo simples, contendo a estrutura “noh”, utilizada para representar os nós da AVL.
  
  - 3 - Manipulacao_avl (.c e .h):
  
  Sendo o “.h” o cabeçalho e “.c” a implementação das funções. Este arquivo contém 10 funções, sendo elas divididas em 2 classes, as “Funções Utilitárias” (8 delas) que fazem pequenos trabalhos, porém repetitivos, e as “Funções Principais” (2 delas) que fazem grande parte do trabalho e chamam as funções utilitárias para auxilio. O Foco desse arquivo é fazer o tratamento da AVL como inclusão de elementos, remoção de elementos, balanceamento, rotação, etc...
  
    - 3.1 - Funções Utilitárias
      - 3.1.1 - struct noh* cria_no(int valor)
      
      Responsável pela criação de nós novos para inserção, colocando o valor passando no nó.
      
      - 3.1.2 - int sub_altura(struct noh* sub_raiz)
      
      Retorna a altura da raiz da sub-árvore atual, afim de evitar segmentation fold quando chegar nas folhas (NULL);
      
      - 3.1.3 - int num_maior(int a, int b)
      
      Retorna a maior altura (“a” e “b”) entre duas sub-arvores;
      
      - 3.1.4 - struct noh* rotacao_dir(struct noh* y)
      
      Função que rotaciona a direita de um nó passado;
      
      - 3.1.5 - struct noh* rotacao_esq(struct noh* x)
      
      Função que rotaciona a esquerda de um nó passado;
      
      - 3.1.6 - void em_ordem(struct noh* raiz, int profundidade)
      
      Função responsável pela impressão da árvore em ordem, imprimindo também em qual nível (profundidade) cada nó se encontra;
      
      - 3.1.7 - struct noh* busca_antecessor(struct noh* no);
      
      Retorna o nó mais a direita, da sub-árvore à esquerda do nó passado.
      
      -3.1.8 - int verif_equilibrio(struct noh* no);
      
      Retorna o fator de balanceamento do nó passado.
    - 3.2 - Funções Principais
      - 3.2.1 - struct noh* insere_AVL(struct noh* raiz, int chave)
      
      A função foi dividida em 3 partes:
      
      1 - Inserção por BST (feita de maneira recursiva) da chave passada;
      
      2 - A recursão começa a “retornar” até a primeira chamada, no caminho ela faz a atualização da altura e a verificação do fator de balanceamento da árvore;
      
      3 - Dependendo do balanceamento, ela analisa em qual caso a sub-árvore atual se encontra, para então fazer a chamada das rotações.
      
      - 3.2.2 - struct noh* remove_AVL(struct noh* raiz, int chave)
      Feita de maneira semelhante a insere_AVL (3.2.1), muda apenas pelo fato de que ela faz uma busca BST ao invés de uma inserção. Através da recursão, ela procura a chave a ser excluída, quando a encontra, ela descobre qual o caso atual (0, 1 ou 2 filhos). Faz a remoção de acordo com cada caso e então balanceia a árvore como em insere_AVL (3.2.1).
      
  - 4 – Myavl.c
  
  Está é a main, onde é feita a leitura do arquivo de entrada, analisando qual operação deve ser feita. Após isso, ela chama a manipulação_avl (3) para cada caso específico. No final, ela faz a impressão no arquivo de saída e encerra o programa.
