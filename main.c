#include <stdio.h>

#define MAX_NOME 50
#define MAX_PRODUTOS 100

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

void produto_mais_lucrativo(Produto p[], int quantidade_produtos) {
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

void filtrar_por_preco(Produto p[], int quantidade_produtos, float preco_limite) {
    for (int i = 0; i < quantidade_produtos; i++)
    {
        if (p[i].valores.venda <= preco_limite)
        {
            printf("O produto %s esta dentro do limite de preco\n\n", p[i].nome);
        }
    }
}

int main()
{
    int quantidade_produtos;
    float preco_limite;

    printf("Quantos produtos tem cadastrado dentro do seu sistema?\n");
    scanf("%d", &quantidade_produtos);

    Produto p[MAX_PRODUTOS];

    for (int i = 0; i < quantidade_produtos; i++)
    {
        printf("\n ----------Produto %d ----------\n", i + 1);
        p[i].valores.margem = -1.0;
        ler_dados(&p[i]);
    }

    for (int i = 0; i < quantidade_produtos; i++)
    {
        calcular_lucro(&p[i]);
    }
    
    for (int i = 0; i < quantidade_produtos; i++)
    {
        imprimir_dados(&p[i]);
    }

    produto_mais_lucrativo(p, quantidade_produtos);

    printf("Digite um limite de preco, para filtrarmos quais produtos passam pelo filtro: ");
    scanf("%f", &preco_limite);

    filtrar_por_preco(p, quantidade_produtos, preco_limite);

    return 0;
}