#include <stdio.h>
#include <string.h>

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

void filtrar_por_preco(Produto p[], int quantidade_produtos, float preco_limite)
{
    for (int i = 0; i < quantidade_produtos; i++)
    {
        if (p[i].valores.venda <= preco_limite)
        {
            printf("O produto %s esta dentro do limite de preco\n\n", p[i].nome);
        }
    }
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

int ler_produtos(Produto p[])
{
    FILE *arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL)
    {
        return 0;
    }

    int i = 0;

    while (fscanf(arquivo, "%d %s %f %f", &p[i].codigo, p[i].nome, &p[i].valores.custo, &p[i].valores.venda) == 4 && i < MAX_PRODUTOS)
    {
        p[i].valores.margem = ((p[i].valores.venda - p[i].valores.custo) / p[i].valores.venda) * 100;
        i++;
    }

    fclose(arquivo);
    return i;
}

int main()
{
    int quantidade_produtos = 0;
    float preco_limite;
    int opcao;

    Produto p[MAX_PRODUTOS];

    quantidade_produtos = ler_produtos(p);

    if (quantidade_produtos > 0)
    {
        printf("Produtos carregados com sucesso! Total: %d\n", quantidade_produtos);
    }

    do
    {
        printf("---------------------System products---------------------\n\n");

        printf("Escolha uma das opcoes abaixo:\n\n");
        printf("Opcao 1: Mostrar produtos cadastrados\n");
        printf("Opcao 2: Cadastrar um novo produto\n");
        printf("Opcao 3: Ver produto mais lucrativo\n");
        printf("Opcao 4: Filtrar por preco\n");
        printf("Opcao 5: Ordenar por preco\n");
        printf("Opcao 6: Salvar\n");
        printf("Caso queira sair tecle 0\n");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (quantidade_produtos == 0)
            {
                printf("Nenhum produto cadastrado\n");
            }
            else
            {
                for (int i = 0; i < quantidade_produtos; i++)
                {
                    imprimir_dados(&p[i]);
                }
            }
            break;
        case 2:
            if (quantidade_produtos < MAX_PRODUTOS)
            {
                printf("\n ---------- Novo Produto ----------\n");
                ler_dados(&p[quantidade_produtos]);
                calcular_lucro(&p[quantidade_produtos]);
                quantidade_produtos++;
                printf("Produto cadastrado com sucesso!\n");
            }
            else
            {
                printf("Limite de produtos atingido!\n");
            }
            break;
        case 3:
            if (quantidade_produtos > 0)
                produto_mais_lucrativo(p, quantidade_produtos);
            else
                printf("Nenhum produto cadastrado.\n");
            break;

        case 4:
            if (quantidade_produtos > 0)
            {
                printf("Digite um limite de preco: ");
                scanf("%f", &preco_limite);
                filtrar_por_preco(p, quantidade_produtos, preco_limite);
            }
            else
            {
                printf("Nenhum produto cadastrado.\n");
            }
            break;

        case 5:
            if (quantidade_produtos > 0)
                ordenar_por_preco(p, quantidade_produtos);
            else
                printf("Nenhum produto cadastrado.\n");
            break;

        case 6:
            salvar_produtos(p, quantidade_produtos);
            break;

        case 0:
            salvar_produtos(p, quantidade_produtos);
            break;
        default:
            printf("Opcao invalida, tente novamente!\n");
            printf("Saindo do sistema...\n");
        }

    } while (opcao != 0);

    return 0;
}