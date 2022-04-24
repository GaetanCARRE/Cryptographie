#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenere(FILE *in, char *mdp, FILE *out);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "format invalide vous devez suivre la forme suivante : ./exe entree mot_de_passe sortie \n");
        return EXIT_FAILURE;
    }
    FILE *f = fopen(argv[1], "r+");
    FILE *f2 = fopen(argv[3], "w+");
    if (f == NULL || f2 == NULL)
    {
        printf("emotdepasserreur à l'ouverture des fichiers");
        return EXIT_FAILURE;
    }
    vigenere(f, argv[2], f2);
}

void vigenere(FILE *in, char *mdp, FILE *out)
{
    int taille_mdp = strlen(mdp);
    int i = 0, e = 0;
    char r;
    char* codage = malloc(sizeof(int) * taille_mdp);

    for (int i = 0; i < taille_mdp; i++)
    {
        codage[i] = (int)tolower(mdp[i]) - 'a' ;
        printf("%d\n", codage[i]);
    }

    e = fscanf(in, "%c", &r);
    while (e != EOF)
    {

        if (r >= 'a' && r <= 'z')
        {
            fprintf(out, "%c", (r - 'a' + codage[i % taille_mdp] + 26) % 26 + 'a');
            i++;
        }
        else if (r >= 'A' && r <= 'Z')
        {
            fprintf(out, "%c", (r - 'A' + codage[i % taille_mdp] + 26) % 26 + 'A');
            i++;
        }
        else
        {
            fprintf(out, "%c", r);
        }
        e = fscanf(in, "%c", &r);
        
    }
}
