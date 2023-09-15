#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    fp = fopen("Strings.txt", "a");

    if (fp != NULL)
    {
        fprintf(fp, "\nprimeira linha\n");

        char frase[] = "segunda linha\n";
        fputs(frase, fp);

        char caractere = '3';
        fputc(caractere, fp);
    }
}