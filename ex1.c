#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* proximo;
} Nodo;

void escreverListaEmArquivo(Nodo* inicio) {
    FILE* arquivo = fopen("C:\\Users\\rafap\\Desktop\\ex\\arquivo.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    Nodo* atual = inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%d\n", atual->data);
        atual = atual->proximo;
    }

    fclose(arquivo);
}



Nodo* lerListaDeArquivo() {
    FILE* arquivo = fopen("C:\\Users\\rafap\\Desktop\\ex\\arquivo.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    Nodo* inicio = NULL;
    Nodo* atual = NULL;
    int valor;

    while (fscanf(arquivo, "%d", &valor) != EOF) {
        Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
        novoNodo->data = valor;
        novoNodo->proximo = NULL;

        if (inicio == NULL) {
            inicio = novoNodo;
            atual = novoNodo;
        } else {
            atual->proximo = novoNodo;
            atual = novoNodo;
        }
    }

    fclose(arquivo);
    return inicio;
}

int main() {
    Nodo* inicio = lerListaDeArquivo();

    // Exemplo: Inserir um novo nó no início da lista
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    novoNodo->data = 42;
    novoNodo->proximo = inicio;
    inicio = novoNodo;
    escreverListaEmArquivo(inicio);

    // Exemplo: Encontrar o maior valor na lista e exibi-lo
    int maior = -1;
    Nodo* atual = inicio;
    while (atual != NULL) {
        if (atual->data > maior) {
            maior = atual->data;
        }
        atual = atual->proximo;
    }
    printf("O maior valor na lista é: %d\n", maior);

    // Exemplo: Inverter a ordem dos elementos na lista
    Nodo* anterior = NULL;
    atual = inicio;
    Nodo* proximo = NULL;
    while (atual != NULL) {
        proximo = atual->proximo;
        atual->proximo = anterior;
        anterior = atual;
        atual = proximo;
    }
    inicio = anterior;
    escreverListaEmArquivo(inicio);

    // Liberar a memória alocada
    while (inicio != NULL) {
        Nodo* temp = inicio;
        inicio = inicio->proximo;
        free(temp);
    }

    return 0;
}
