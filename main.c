#include <stdio.h>
#include <stdlib.h>
#include "produto.h"

int main()
{
    int capacidade = 10;
    int quantidade_produtos = 0;
    int opcao;

    Produto *p = (Produto *)malloc(capacidade * sizeof(Produto));

    if (p == NULL)
    {
        printf("Erro: falha ao alocar memoria!\n");
        return 1;
    }

    quantidade_produtos = ler_produtos(p, &capacidade);

    if (quantidade_produtos > 0)
    {
        printf("Produtos carregados com sucesso! Total: %d\n", quantidade_produtos);
    }

    do
    {
        limpar_tela();

        printf("---------------------System products---------------------\n\n");
        printf("Escolha uma das opcoes abaixo:\n\n");
        printf("Opcao 1: Mostrar produtos cadastrados\n");
        printf("Opcao 2: Cadastrar um novo produto\n");
        printf("Opcao 3: Ver produto mais lucrativo\n");
        printf("Opcao 4: Ordenar por preco\n");
        printf("Opcao 5: Salvar\n");
        printf("Opcao 6: Remover produto do sistema\n");
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
            pausar_sistema();
            break;

        case 2:
            if (quantidade_produtos >= capacidade)
            {
                capacidade *= 2;
                Produto *temp = (Produto *)realloc(p, capacidade * sizeof(Produto));
                if (temp == NULL)
                {
                    printf("Erro: nao foi possivel realocar memoria!\n");
                    pausar_sistema();
                    break;
                }
                p = temp;
            }

            printf("\n ---------- Novo Produto ----------\n");
            ler_dados(&p[quantidade_produtos]);
            calcular_lucro(&p[quantidade_produtos]);
            quantidade_produtos++;
            printf("Produto cadastrado com sucesso!\n");
            pausar_sistema();
            break;

        case 3:
            if (quantidade_produtos > 0) {
                produto_mais_lucrativo(p, quantidade_produtos);
            }
            else {
                printf("Nenhum produto cadastrado.\n");
            }
            pausar_sistema();
            break;

        case 4:
            if (quantidade_produtos > 0) {
                ordenar_por_preco(p, quantidade_produtos);
            }
            else { 
                printf("Nenhum produto cadastrado.\n");
            }
            pausar_sistema();
            break;

        case 5:
            salvar_produtos(p, quantidade_produtos);
            printf("Produtos salvos com sucesso!\n");
            pausar_sistema();
            break;

        case 6:
            remover_produto(p, &quantidade_produtos);
            pausar_sistema();
            break;

        case 0:
            salvar_produtos(p, quantidade_produtos);
            free(p);
            break;
        default:
            printf("Opcao invalida, tente novamente!\n");
            pausar_sistema();
        }

    } while (opcao != 0);

    return 0;
}