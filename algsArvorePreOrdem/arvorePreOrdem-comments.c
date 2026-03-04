#include <stdio.h>
#include <stdlib.h>

// O typedef funciona como um "apelido". Em vez de chamarmos de "struct NoDeArvore"
// em todo o código, chamamos apenas de "TipoNoDeArvore", deixando a infraestrutura limpa.
typedef struct NoDeArvore
{
    int valor; // O dado real que o nó vai guardar na memória
    struct NoDeArvore *filhoEsquerda; // Ponteiro que levará aos valores MENORES
    struct NoDeArvore *filhoDireita;  // Ponteiro que levará aos valores MAIORES
} TipoNoDeArvore;

// Função responsável por alocar novos dados na memória respeitando a regra da Árvore Binária.
TipoNoDeArvore *inserir(TipoNoDeArvore *raiz, int valor)
{
    // Caso base: Se a raiz é nula, achamos um "terreno vazio" para construir nosso novo nó.
    if (raiz == NULL)
    {
        // Pede ao sistema operacional um bloco de memória do tamanho exato da nossa struct.
        TipoNoDeArvore *novo = (TipoNoDeArvore *) malloc(sizeof(TipoNoDeArvore));
        
        // Verificação de segurança visionária: garante que a memória RAM não esgotou.
        if (novo == NULL)
        {
            printf("Erro crítico: Falta de memória RAM!\n");
            exit(1); // Aborta a operação de forma segura se der pane na memória.
        }
        
        // Inicializa o novo nó como uma "folha" (sem filhos ainda).
        novo->valor = valor;
        novo->filhoEsquerda = NULL;
        novo->filhoDireita = NULL;
        
        return novo; // Retorna a referência desse novo bloco de memória alocado.
    }

    // Navegação recursiva: O motor de busca da árvore.
    // Se o valor for menor, delega a tarefa de inserir para a subárvore da esquerda.
    if (valor < raiz->valor)
    { raiz->filhoEsquerda = inserir(raiz->filhoEsquerda, valor); }
    // Caso contrário (maior ou igual), delega para a subárvore da direita.
    else
    { raiz->filhoDireita = inserir(raiz->filhoDireita, valor); }
    
    // Retorna a própria raiz para manter a integridade das conexões da árvore intacta.
    return raiz; 
}

// Algoritmo de travessia em Pré-Ordem: Processa a Raiz -> Esquerda -> Direita.
// Ideal para clonar ou serializar a estrutura, pois lê os "pais" antes dos "filhos".
void preOrdem(TipoNoDeArvore *raiz)
{
    if (raiz != NULL) // A condição de parada: só executa se o nó realmente existir.
    {
        printf("%d ", raiz->valor);    // 1. Processa a raiz atual.
        preOrdem(raiz->filhoEsquerda); // 2. Mergulha recursivamente em toda a lateral esquerda.
        preOrdem(raiz->filhoDireita);  // 3. Mergulha recursivamente em toda a lateral direita.
    }
}

// Algoritmo de travessia em Pós-Ordem: Processa Esquerda -> Direita -> Raiz.
// Essencial para faxina de memória, pois destrói os filhos antes de destruir o pai.
void liberarArvore(TipoNoDeArvore *raiz)
{
    if (raiz != NULL)
    {
        liberarArvore(raiz->filhoEsquerda); // 1. Vai até a última folha da esquerda.
        liberarArvore(raiz->filhoDireita);  // 2. Vai até a última folha da direita.
        free(raiz); // 3. Sem filhos pendentes, machado na raiz! Libera a RAM pro sistema.
    }
}

// O motor principal do nosso programa em C.
int main()
{
    // A árvore nasce como um ponteiro nulo (totalmente vazia na memória).
    TipoNoDeArvore *minhaArvore = NULL;

    printf("\nIniciando a infraestrutura da Árvore...\n");

    // Construindo a hierarquia. O primeiro a entrar (500) torna-se a raiz absoluta.
    minhaArvore = inserir(minhaArvore, 500); 
    minhaArvore = inserir(minhaArvore, 250); // Menor que 500, vai pra esquerda.
    minhaArvore = inserir(minhaArvore, 750); // Maior que 500, vai pra direita.
    minhaArvore = inserir(minhaArvore, 100); // Menor que 250, fica bem à esquerda.
    minhaArvore = inserir(minhaArvore, 300); // Maior que 250, à direita do 250.

    // Extraindo e validando os dados.
    printf("\nLendo os dados em Pré-Ordem:\n");
    printf("Resultado esperado: 500 250 100 300 750\n");
    printf("Resultado obtido:   ");
    preOrdem(minhaArvore); // Chama a função recursiva de impressão no terminal.
    printf("\n\n");

    // Encerrando a aplicação com responsabilidade, evitando vazamento de memória.
    printf("Iniciando protocolo de limpeza de memória (Pós-Ordem)...\n");
    liberarArvore(minhaArvore); // Corta a árvore inteira de baixo para cima.
    printf("Memória RAM liberada com sucesso. Zero memory leaks!\n\n");

    return 0; // Código zero indica ao SO que tudo ocorreu perfeitamente.
}