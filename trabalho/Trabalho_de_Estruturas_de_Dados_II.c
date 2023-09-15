/*  
    Nomes dos envolvidos:
    Rafael Almeida Vasconcelos
    Thiago Carretero Santos
    Guilherme Dias Gregorio
    Raphael Baruque Souza
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct Carrinho
{
    struct Produto *produtos;
    int quantidade;
};

struct Produto
{
    int codigo;
    char descricao[100];
    char categoria[100];
    int quantidadeEstoque;
    float precoUnitario;

    struct Produto *proximo;
};

FILE *pFile = NULL;
struct Produto *inicio = NULL;
struct Carrinho carrinhoCompra;

void imprimirProduto(struct Produto *produto)
{
    printf("\n");
    printf("\ncodigo %d", produto->codigo);
    printf("\ndescricao %s", produto->descricao);
    printf("\ncategoria %s", produto->categoria);
    printf("\nquantidade em estoque %d ", produto->quantidadeEstoque);
    printf("\npreco %0.2f ", produto->precoUnitario);
}

void printarCarrinho()
{
    struct Produto *produto = carrinhoCompra.produtos;

    printf("Produtos no carrinho:\n");
    while (produto != NULL)
    {
        imprimirProduto(produto);
        produto = produto->proximo;
    }

    printf("\nQuantidade total de produtos no carrinho: %d\n", carrinhoCompra.quantidade);
}

void listar_todos_produtos()
{
    struct Produto *aux = (struct Produto *)malloc(sizeof(struct Produto));
    int codigo;

    pFile = fopen("estoque2.txt", "r");

    if (pFile != NULL)
    {
        while (fscanf(pFile, "%d ", &codigo) != EOF)
        {
            aux->codigo = codigo;

            fscanf(pFile, "%s ", aux->descricao);
            fscanf(pFile, "%s ", aux->categoria);
            fscanf(pFile, "%d ", &aux->quantidadeEstoque);
            fscanf(pFile, "%f ", &aux->precoUnitario);

            aux->proximo = inicio;
            inicio = aux;

            if (inicio->quantidadeEstoque > 0)
            {
                imprimirProduto(inicio);
            }
        }
        fclose(pFile);
    }
    else
    {
        printf("Erro ao abrir o arquivo de estoque.\n");
    }
}

void listar_produtos_categoria(char categorias[100])
{
    struct Produto *novo = (struct Produto *)malloc(sizeof(struct Produto));
    int codigo;
    pFile = fopen("estoque2.txt", "r");

    if (pFile != NULL)
    {
        while (fscanf(pFile, "%d ", &codigo) != EOF)
        {
            novo->codigo = codigo;

            fscanf(pFile, "%s ", novo->descricao);
            fscanf(pFile, "%s ", novo->categoria);
            fscanf(pFile, "%d ", &novo->quantidadeEstoque);
            fscanf(pFile, "%f ", &novo->precoUnitario);

            novo->proximo = inicio;
            inicio = novo;

            if (strcmp(categorias, inicio->categoria) == 0)
            {
                imprimirProduto(inicio);
            }
        }
        fclose(pFile);
    }
    else
    {
        printf("Erro ao abrir o arquivo de estoque.\n");
    }
}

void adicionarProdutosEmCarrinhoDeCompra(int codigoC, int quantidadeC)
{
    struct Produto *novo = (struct Produto *)malloc(sizeof(struct Produto));
    int codigo;

    pFile = fopen("estoque2.txt", "r+");

    if (pFile != NULL)
    {
        while (fscanf(pFile, "%d ", &codigo) != EOF)
        {
            novo->codigo = codigo;

            fscanf(pFile, "%s ", novo->descricao);
            fscanf(pFile, "%s ", novo->categoria);
            fscanf(pFile, "%d ", &novo->quantidadeEstoque);
            fscanf(pFile, "%f ", &novo->precoUnitario);

            novo->proximo = inicio;
            inicio = novo;

            if (inicio->codigo == codigoC)
            {
                if (quantidadeC <= inicio->quantidadeEstoque)
                {

                    carrinhoCompra.quantidade += quantidadeC;

                    // Adicione o produto ao carrinho
                    struct Produto *produtoCarrinho = (struct Produto *)malloc(sizeof(struct Produto));
                    produtoCarrinho->codigo = inicio->codigo;
                    strcpy(produtoCarrinho->descricao, inicio->descricao);
                    strcpy(produtoCarrinho->categoria, inicio->categoria);
                    produtoCarrinho->quantidadeEstoque = quantidadeC;
                    produtoCarrinho->precoUnitario = inicio->precoUnitario;
                    produtoCarrinho->proximo = carrinhoCompra.produtos;
                    carrinhoCompra.produtos = produtoCarrinho;

                    printf("Produto adicionado ao carrinho.\n");
                }
                else
                {
                    printf("Quantidade indisponível.\n");
                }
            }
        }
        fclose(pFile);
    }
    else
    {
        printf("Erro ao abrir o arquivo de estoque.\n");
    }
}

void editarCarrinho()
{
    int codigoC;
    int novaQuantidade;

    printf("Digite o código do produto que deseja editar no carrinho: ");
    scanf("%d", &codigoC);

    struct Produto *produto = carrinhoCompra.produtos;

    while (produto != NULL)
    {
        if (produto->codigo == codigoC)
        {
            printf("Produto encontrado no carrinho.\n");
            printf("Quantidade atual: %d\n", produto->quantidadeEstoque);
            printf("Digite a nova quantidade desejada: ");
            scanf("%d", &novaQuantidade);

            // Verifique se a nova quantidade desejada é menor ou igual à disponível no estoque
            int quantidadeEstoque = 0;  // Variável para rastrear a quantidade em estoque

            pFile = fopen("estoque2.txt", "r");
            if (pFile != NULL)
            {
                int codigo;
                char descricao[100];
                char categoria[100];
                float precoUnitario;

                while (fscanf(pFile, "%d %s %s %d %f", &codigo, descricao, categoria, &quantidadeEstoque, &precoUnitario) != EOF)
                {
                    if (codigo == codigoC)
                    {
                        break;  // Encontrou o produto no estoque
                    }
                }
                fclose(pFile);

                if (novaQuantidade <= quantidadeEstoque)
                {
                    produto->quantidadeEstoque = novaQuantidade;
                    printf("Quantidade atualizada com sucesso.\n");
                }
                else
                {
                    printf("Quantidade indisponível no estoque.\n");
                }
            }
            else
            {
                printf("Erro ao abrir o arquivo de estoque.\n");
            }

            return;
        }
        produto = produto->proximo;
    }

    printf("Produto não encontrado no carrinho.\n");
}


void efetuarCompra()
{
    float totalCompra = 0.0;
    struct Produto *produto = carrinhoCompra.produtos;

    // Abra o arquivo de estoque para leitura
    pFile = fopen("estoque2.txt", "r");

    if (pFile != NULL)
    {
        // Crie um arquivo temporário para escrita
        FILE *tempFile = fopen("temp_estoque2.txt", "w");

        if (tempFile != NULL)
        {
            while (1)
            {
                // Variáveis para armazenar temporariamente os valores lidos
                int codigo;
                char descricao[100];
                char categoria[100];
                int quantidadeEstoque;
                float precoUnitario;

                // Percorra o arquivo e leia uma linha por vez
                if (fscanf(pFile, "%d %s %s %d %f", &codigo, descricao, categoria, &quantidadeEstoque, &precoUnitario) == EOF)
                {
                    break; // Saia do loop quando atingir o final do arquivo
                }

                struct Produto *produtoAtual = produto;

                while (produtoAtual != NULL)
                {
                    if (codigo == produtoAtual->codigo)
                    {
                        // Subtraia a quantidade vendida do estoque
                        quantidadeEstoque -= produtoAtual->quantidadeEstoque;

                        // Calcule o valor total da compra
                        totalCompra += (produtoAtual->quantidadeEstoque * produtoAtual->precoUnitario);

                        break;
                    }

                    produtoAtual = produtoAtual->proximo;
                }

                // Escreva a linha atualizada no arquivo temporário
                fprintf(tempFile, "%d %s %s %d %.2f\n", codigo, descricao, categoria, quantidadeEstoque, precoUnitario);
            }

            // Feche o arquivo temporário
            fclose(tempFile);

            // Feche o arquivo original
            fclose(pFile);

            // Substitua o arquivo original pelo arquivo temporário
            if (remove("estoque2.txt") != 0 || rename("temp_estoque2.txt", "estoque2.txt") != 0)
            {
                printf("Erro ao atualizar o arquivo de estoque.\n");
            }
            else
            {
                // Limpe o carrinho de compra
                carrinhoCompra.quantidade = 0;
                carrinhoCompra.produtos = NULL;

                printf("Compra efetuada com sucesso!\n");
                printf("Valor total da compra: R$%.2f\n", totalCompra);
            }
        }
        else
        {
            printf("Erro ao criar o arquivo temporário.\n");
            fclose(pFile);
        }
    }
    else
    {
        printf("Erro ao abrir o arquivo de estoque.\n");
    }
}




int main()
{
    int opcao;
    char categorias[100];
    int codigoC;
    int quantidadeC;

    do
    {
        printf("\n\n1 - Listar todos os produtos.\n");
        printf("2 - Buscar produto de acordo com categoria.\n");
        printf("3 - Adicionar produtos em carrinho de compra.\n");
        printf("4 - Visualizar carrinho de compra.\n");
        printf("5 - Editar carrinho de compra.\n");
        printf("6 - Efetuar compra.\n");
        printf("0 - Sair do programa.\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            listar_todos_produtos();
            break;
        case 2:
            printf("Digite a categoria desejada: ");
            scanf("%s", categorias);
            listar_produtos_categoria(categorias);
            break;
        case 3:
            printf("Digite o código do produto: ");
            scanf("%d", &codigoC);
            printf("Digite a quantidade desejada: ");
            scanf("%d", &quantidadeC);
            adicionarProdutosEmCarrinhoDeCompra(codigoC, quantidadeC);
            break;
        case 4:
            printarCarrinho();
            break;
        case 5:
            editarCarrinho();
            break;
        case 6:
            efetuarCompra();
            break;
        case 0:
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}
