#ifndef PRODUTO_H
#define PRODUTO_H

#define MAX_NOME 50

typedef struct valores
{
    float custo;
    float venda;
    float margem;
} Valores;

typedef struct produto
{
    int codigo;
    char nome[MAX_NOME];
    Valores valores;
} Produto;

void ler_dados(Produto *p);
void calcular_lucro(Produto *p);
void imprimir_dados(Produto *p);
void produto_mais_lucrativo(Produto p[], int quantidade_produtos);
void ordenar_por_preco(Produto p[], int quantidade_produtos);
void salvar_produtos(Produto p[], int quantidade_produtos);
int ler_produtos(Produto *p, int *capacidade);

#endif