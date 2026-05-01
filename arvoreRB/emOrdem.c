#include <stdio.h>
#include <stdlib.h>

#define VERMELHO 0
#define PRETO 1

typedef struct NoDeArvore {
    int valor;
    int cor; 
    struct NoDeArvore *filhoEsquerda;
    struct NoDeArvore *filhoDireita;
    struct NoDeArvore *pai;
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
        novo->cor = VERMELHO; 
        novo->filhoEsquerda = NULL;
        novo->filhoDireita = NULL;
        novo->pai = NULL;
        
        return novo;
    }

    if (valor < raiz->valor)
    { raiz->filhoEsquerda = inserir(raiz->filhoEsquerda, valor); }
    else
    { raiz->filhoDireita = inserir(raiz->filhoDireita, valor); }
    
    return raiz;
}

void emOrdem(TipoNoDeArvore *raiz) {

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

int main()
{
    TipoNoDeArvore *raiz = NULL;

    raiz = inserir(raiz, 10);
    inserir(raiz, 5);
    inserir(raiz, 15);
    inserir(raiz, 3);
    inserir(raiz, 7);
    inserir(raiz, 12);
    inserir(raiz, 18);

    printf("Árvore em ordem: ");
    emOrdem(raiz);
    printf("\n");

    liberarArvore(raiz);

    return 0;
}