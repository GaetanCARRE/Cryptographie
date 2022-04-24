#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char prochaineLettre(FILE *);
char lettreLaPlusFrequente(FILE *);
void decodageCesar(FILE *, FILE *);
void cesar(char *entree, int decalage, char *sortie);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "format invalide vous devez suivre la forme suivante : ./exe entree sortie \n");
        return EXIT_FAILURE;
    }
    FILE *f = fopen(argv[1], "rb");
    FILE *f2 = fopen(argv[2], "w+");
    if (f == NULL || f2 == NULL)
    {
        printf("erreur à l'ouverture des fichiers");
        return EXIT_FAILURE;
    }
    decodageCesar(f, f2);
    fclose(f);
    fclose(f2);
    return EXIT_SUCCESS;
}

char prochaineLettre(FILE *in)
{
    char r;
    int e;
    e = fscanf(in, "%c", &r);
    while ((r < 'a' || r > 'z') && (r < 'A' || r > 'Z'))
    {
        if (e == EOF)
        {
            return '\0';
        }
        e = fscanf(in, "%c", &r);
    }
    return r;
}

char lettreLaPlusFrequente(FILE *in)
{
    char c;
    int max = 0;
    char idx = '\0';
    int tab[26] = {'\0'};

    c = tolower(prochaineLettre(in));

    while (c != '\0')
    {
        tab[(int)c - (int)'a'] += 1;
        if (tab[(int)c - (int)'a'] > max)
        {
            max = tab[(int)c - (int)'a'];
            idx = c;
        }
        c = prochaineLettre(in);
    }
    return (char)idx;
}

void decodageCesar(FILE *in, FILE *out)
{

    char c;
    int decalage;
    int e = 0;
    char r;
    c = lettreLaPlusFrequente(in);
    rewind(in);
    decalage = -(c - 'e');
    e = fscanf(in, "%c", &r);
    while (e != EOF)
    {
        

        if (r >= 'a' && r <= 'z')
        {
            fprintf(out, "%c", (r - 'a' + decalage + 26) % 26 + 'a');
        }
        else if (r >= 'A' && r <= 'Z')
        {
            fprintf(out, "%c", (r - 'A' + decalage + 26) % 26 + 'A');
        }
        else
        {
            fprintf(out, "%c", r);
        }
        e = fscanf(in, "%c", &r);
    }
    
}
