#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp;
    fp = fopen("exercicio.txt", "w");
    fprintf(fp, "Rafael\n");
    fclose(fp);

    char nome[50];
    fp = fopen("exercicio.txt", "r");
    fscanf(fp, "%s", nome);
    printf("%s", nome);
    fclose(fp);
    
    
}