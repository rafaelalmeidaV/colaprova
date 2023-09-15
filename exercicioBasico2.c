#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp;
    fp = fopen("Strings.txt", "r");

    if (fp != NULL)
    {
        char frase[100];

        while(fgets(frase, 100, fp) != NULL){
            printf("%s", frase);
        }
    }
}