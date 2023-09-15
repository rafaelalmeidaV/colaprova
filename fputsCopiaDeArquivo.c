#include <stdio.h>
#include <stdlib.h>


int main(){
    void copiarConteudo(FILE *fp1, FILE *fp2);

    FILE *file1 = fopen("exercicio.txt", "r");
    if(file1 != NULL){
        FILE *file2 = fopen("exercicio2.txt", "w");
        copiarConteudo(file1, file2);
        fclose(file1);
        fclose(file2);
        return 0;
    } 
}

void copiarConteudo(FILE *file1, FILE *file2){

    char leitor[1000];

    while(fgets(leitor, 1000, file1) != NULL){ // fgets é uma função que lê uma string de um arquivo e armazena em uma variável string (char nome[50]) // 50 é o tamanho máximo da string // fp é o arquivo que será lido
        fputs(leitor, file2); // fputs escreve uma string em um arquivo
    }
}