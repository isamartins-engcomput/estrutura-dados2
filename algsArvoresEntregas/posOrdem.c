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

void posOrdem(TipoNoDeArvore *raiz)
{
    if (raiz != NULL)
    {
        posOrdem(raiz->filhoEsquerda);
        posOrdem(raiz->filhoDireita);
        printf("%d ", raiz->valor);
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

int main()
{
    TipoNoDeArvore *minhaArvore = NULL;

    printf("\nIniciando a infraestrutura da Árvore...\n\n");

    minhaArvore = inserir(minhaArvore, 500); 
    minhaArvore = inserir(minhaArvore, 250);
    minhaArvore = inserir(minhaArvore, 750);
    minhaArvore = inserir(minhaArvore, 100);
    minhaArvore = inserir(minhaArvore, 300);

    printf("Árvore bruta após as inserções (Pré-Ordem): "); // Raiz → Esquerda → Direita
    preOrdem(minhaArvore);
    printf("\n\n");

    printf("Lendo os dados em Pós-Ordem...\n\n");
    printf("Resultado esperado: 100 300 250 750 500\n");
    printf("Resultado obtido:   ");
    posOrdem(minhaArvore);
    printf("\n\n");

    printf("Iniciando protocolo de limpeza de memória...\n");
    liberarArvore(minhaArvore);
    printf("Memória RAM liberada com sucesso. Zero memory leaks!\n\n");

    return 0;
}