#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp;
    char nomes[100];
    char novoNome[100];

    fp = fopen("exercicio.txt","r");
    if(fp != NULL){
        while(fgets(nomes, 100, fp) != NULL){
            printf("%s", nomes);
        }
    
    fp = fopen("exercicio.txt", "a+");
        fprintf(fp, "\nantonio\n");
        printf("\ndigite um nome\n");
        gets(novoNome);

        // Voltar ao início do arquivo para verificar
        rewind(fp);

        // Verificar se o novo nome está no arquivo
        int encontrado = 0;
        while (fgets(nomes, 100, fp) != NULL) {
            nomes[strcspn(nomes, "\n")] = '\0'; // Remover o caractere de nova linha
            if (strcmp(novoNome, nomes) == 0) {
                encontrado = 1;
                break;
            }
        }

        if (encontrado) {
            printf("O nome está no arquivo.\n");
        } else {
            printf("O nome não está no arquivo.\n");
        } 
    }
    fclose(fp);

    

    
    }
