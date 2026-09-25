#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "produto.h"

void ler_dados(Produto *p)
{
    printf("Digite o codigo do produto: ");
    scanf("%d", &(p->codigo));

    printf("Digite o nome do produto: ");
    scanf("%s", p->nome);

    printf("Qual o preco de custo do produto %s: ", p->nome);
    scanf("%f", &(p->valores.custo));

    printf("Digite o preco de venda do produto %s: ", p->nome);
    scanf("%f", &(p->valores.venda));
}

void calcular_lucro(Produto *p)
{
    p->valores.margem = ((p->valores.venda - p->valores.custo) / p->valores.venda) * 100;
}

void imprimir_dados(Produto *p)
{
    printf("O produto %s com o codigo %d tem o custo de compra de RS: %.2f e seu preco de venda e de RS: %.2f\n", p->nome, p->codigo, p->valores.custo, p->valores.venda);

    if (p->valores.margem < 0)
    {
        printf("A margem de lucro ainda nao foi calculada\n\n");
    }
    else
    {
        printf("A Margem de lucro desse produto e de %.0f%%\n\n", p->valores.margem);
    }
}

void produto_mais_lucrativo(Produto p[], int quantidade_produtos)
{
    int indice_mais_lucrativo = 0;

    for (int i = 1; i < quantidade_produtos; i++)
    {
        if (p[i].valores.margem > p[indice_mais_lucrativo].valores.margem)
        {
            indice_mais_lucrativo = i;
        }
    }
    printf("O produto mais lucrativo e o %s com uma margem de %.0f%%\n", p[indice_mais_lucrativo].nome, p[indice_mais_lucrativo].valores.margem);
}

void ordenar_por_preco(Produto p[], int quantidade_produtos)
{
    Produto temp;
    int ok = 0;

    for (int i = 0; i < quantidade_produtos - 1 && !ok; i++)
    {
        ok = 1;

        for (int j = 0; j < quantidade_produtos - i - 1; j++)
        {
            if (p[j].valores.venda > p[j + 1].valores.venda)
            {
                ok = 0;
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    printf("\n------Produtos ordenados por preco de venda------\n");

    for (int i = 0; i < quantidade_produtos; i++)
    {
        printf("-> [%d] %s - RS %.2f\n", p[i].codigo, p[i].nome, p[i].valores.venda);
    }
}

void salvar_produtos(Produto p[], int quantidade_produtos)
{
    FILE *arquivo = fopen("produtos.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    for (int i = 0; i < quantidade_produtos; i++)
    {
        fprintf(arquivo, "%d %s %f %f\n", p[i].codigo, p[i].nome, p[i].valores.custo, p[i].valores.venda);
    }

    fclose(arquivo);
    printf("Produtos salvos com sucesso\n");
}

int ler_produtos(Produto *p, int *capacidade)
{
    FILE *arquivo = fopen("produtos.txt", "rt");
    if (arquivo == NULL)
    {
        return 0; 
    }

    int i = 0;
    int leu_com_sucesso = (fscanf(arquivo, "%d %s %f %f", &p[i].codigo, p[i].nome, &p[i].valores.custo, &p[i].valores.venda) == 4);

    while (leu_com_sucesso)
    {
        p[i].valores.margem = ((p[i].valores.venda - p[i].valores.custo) / p[i].valores.venda) * 100;
        i++;

        if (i >= *capacidade)
        {
            (*capacidade) *= 2; 
            Produto *temp = (Produto *) realloc(p, (*capacidade) * sizeof(Produto));
            if (temp == NULL)
            {
                printf("Erro ao realocar memória!\n");
                break;
            }
            p = temp;
        }

        leu_com_sucesso = (fscanf(arquivo, "%d %s %f %f", &p[i].codigo, p[i].nome, &p[i].valores.custo, &p[i].valores.venda) == 4);
    }

    fclose(arquivo);
    return i;
}