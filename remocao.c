#include <stdio.h>
#include <stdlib.h>

typedef struct NoDeArvore
{
    int valor;
    struct NoDeArvore *filhoEsquerda;
    struct NoDeArvore *filhoDireita;
} TipoNoDeArvore;

TipoNoDeArvore *inserir(TipoNoDeArvore *raiz, int valor)
{
    if (raiz == NULL)
    {
        TipoNoDeArvore *novo = (TipoNoDeArvore *) malloc(sizeof(TipoNoDeArvore));
        
        if (novo == NULL)
        {
            printf("Erro crítico: Falta de memória RAM!\n");
            exit(1);
        }
        
        novo->valor = valor;
        novo->filhoEsquerda = NULL;
        novo->filhoDireita = NULL;
        
        return novo;
    }

    if (valor < raiz->valor)
    { raiz->filhoEsquerda = inserir(raiz->filhoEsquerda, valor); }
    else
    { raiz->filhoDireita = inserir(raiz->filhoDireita, valor); }
    
    return raiz; 
}

void preOrdem(TipoNoDeArvore *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->valor);
        preOrdem(raiz->filhoEsquerda);
        preOrdem(raiz->filhoDireita);
    }
}

void emOrdem(TipoNoDeArvore *raiz)
{
    if (raiz != NULL)
    {
        emOrdem(raiz->filhoEsquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->filhoDireita);
    }
}

void liberarArvore(TipoNoDeArvore *raiz)
{
    if (raiz != NULL)
    {
        liberarArvore(raiz->filhoEsquerda);
        liberarArvore(raiz->filhoDireita);
        free(raiz); 
    }
}

TipoNoDeArvore *encontrarMaximo(TipoNoDeArvore *raiz)
{
    while (raiz->filhoDireita != NULL)
    {
        raiz = raiz->filhoDireita;
    }
    return raiz;
}

TipoNoDeArvore *remover(TipoNoDeArvore *raiz, int valor)
{
    if (raiz == NULL) return raiz;

    if (valor < raiz->valor)
    {
        raiz->filhoEsquerda = remover(raiz->filhoEsquerda, valor);
    }
    else if (valor > raiz->valor)
    {
        raiz->filhoDireita = remover(raiz->filhoDireita, valor);
    }
    else
    {
        if (raiz->filhoEsquerda == NULL)
        {
            TipoNoDeArvore *temp = raiz->filhoDireita;
            free(raiz);
            return temp;
        }
        else if (raiz->filhoDireita == NULL)
        {
            TipoNoDeArvore *temp = raiz->filhoEsquerda;
            free(raiz);
            return temp;
        }

        TipoNoDeArvore *temp = encontrarMaximo(raiz->filhoEsquerda);
        raiz->valor = temp->valor;
        raiz->filhoEsquerda = remover(raiz->filhoEsquerda, temp->valor);
    }
    return raiz;
}

int main()
{
    TipoNoDeArvore *minhaArvore = NULL;

    printf("\nIniciando a infraestrutura da Árvore...\n\n");

    minhaArvore = inserir(minhaArvore, 500); 
    minhaArvore = inserir(minhaArvore, 250);
    minhaArvore = inserir(minhaArvore, 750);
    minhaArvore = inserir(minhaArvore, 100);
    minhaArvore = inserir(minhaArvore, 300);

    printf("Árvore bruta após as inserções (Pré-Ordem): "); 
    preOrdem(minhaArvore);
    printf("\n\n");

    printf("Lendo os dados Em-Ordem...\n");
    printf("Resultado esperado: 100 250 300 500 750\n");
    printf("Resultado obtido:   ");
    emOrdem(minhaArvore);
    printf("\n\n");

    printf("Executando exclusão do nó 250...\n");
    minhaArvore = remover(minhaArvore, 250);
    
    printf("Lendo os dados Em-Ordem após exclusão...\n");
    printf("Resultado esperado: 100 300 500 750\n");
    printf("Resultado obtido:   ");
    emOrdem(minhaArvore);
    printf("\n\n");

    printf("Iniciando protocolo de limpeza de memória...\n");
    liberarArvore(minhaArvore);
    printf("Memória RAM liberada com sucesso. Zero memory leaks!\n\n");

    return 0;
}