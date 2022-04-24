#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void normaliserFichier(FILE *in, FILE *out);
void decouperFichier(FILE *in, FILE *out, long longueur, int debut);
char *trouver_mdp(FILE *in, long longueur, int debut);
char lettreLaPlusFrequente(FILE *in);
char prochaineLettre(FILE *in);
void decodage(FILE *in, FILE *out, char *mdp, int longueur);
double IndiceCoincidence(FILE *in);
int longueurMotPasseVigenere(FILE *in);
int *frequenceLettre(FILE *in);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "format invalide vous devez suivre la forme suivante : ./exe entree sortie \n");
        return EXIT_FAILURE;
    }
    int longueur = 0;
    int debut = 0;
    FILE *f = fopen(argv[1], "r+");
    FILE *f2 = fopen("f2", "w+");
    FILE *f3 = fopen(argv[2], "w+");

    if (f == NULL || f2 == NULL || f3 == NULL)
    {
        printf("erreur à l'ouverture des fichiers");
        return EXIT_FAILURE;
    }
    normaliserFichier(f, f2);
    rewind(f2);

    longueur = longueurMotPasseVigenere(f2);
    rewind(f2);
    decodage(f,f3,trouver_mdp(f2,longueur,debut), longueur);

    return EXIT_SUCCESS;
}

void normaliserFichier(FILE *in, FILE *out)
{
    int e = 0;
    char r;
    e = fscanf(in, "%c", &r);
    while (e != EOF)
    {

        if (r >= 'a' && r <= 'z')
        {
            fprintf(out, "%c", r);
        }
        else if (r >= 'A' && r <= 'Z')
        {
            fprintf(out, "%c", tolower(r));
        }
        e = fscanf(in, "%c", &r);
    }
}

void decouperFichier(FILE *in, FILE *out, long longueur, int debut)
{
    int e = 0;
    char r;
    rewind(in);
    fseek(in, debut, SEEK_CUR);
    e = fscanf(in, "%c", &r);
    while (e != EOF)
    {
        fprintf(out, "%c", r);
        fseek(in, longueur - 1, SEEK_CUR);

        e = fscanf(in, "%c", &r);
    }
    fprintf(out, "%c", '\0');
}

char *trouver_mdp(FILE *in, long longueur, int debut)
{
    char *mot_de_passe = malloc(sizeof(char) * longueur);
    if(!mot_de_passe)
        return NULL;
    for (int i = 0; i < longueur; i++)
    {
        FILE *f4 = fopen("f4.txt", "w+");

        if (f4 == NULL)
        {
            printf("erreur à l'ouverture des fichiers");
            exit(-1);
        }
        decouperFichier(in, f4, longueur, debut + i);
        rewind(f4);

        mot_de_passe[i] = lettreLaPlusFrequente(f4);
        mot_de_passe[i] = mot_de_passe[i] - 'e' + 'a';
        fclose(f4);
    }
    return mot_de_passe;
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

char prochaineLettre(FILE *in)
{
    char r;
    int e = 0;
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

void decodage(FILE *in, FILE *out, char *mdp, int longueur)
{

    int decalage;
    int e = 0;
    char r;
    int i = 0;
    rewind(in);
    e = fscanf(in, "%c", &r);
    while (e != EOF)
    {

        decalage = -(mdp[(i % longueur)] - 'a');
        if (r >= 'a' && r <= 'z')
        {
            fprintf(out, "%c", (r - 'a' + decalage + 26) % 26 + 'a');
            i++;
        }
        else if (r >= 'A' && r <= 'Z')
        {
            fprintf(out, "%c", (r - 'A' + decalage + 26) % 26 + 'A');
            i++;
        }
        else
        {
            fprintf(out, "%c", r);
        }
        e = fscanf(in, "%c", &r);
    }
}

double IndiceCoincidence(FILE *in)
{
    double idx = 0;
    double N = 0;
    int *tablo;

    tablo = frequenceLettre(in);
    double add = 0;
    for (int i = 0; i < 26; i++)
    {
        add += tablo[i] * (tablo[i] - 1);
        N += tablo[i];
    }
    idx = add / (N * (N - 1));
    return idx;
}

int *frequenceLettre(FILE *in)
{
    char c;

    int *tab = malloc(sizeof(int) * 26);
    c = tolower(prochaineLettre(in));
    while (c != '\0')
    {
        tab[(int)c - (int)'a'] += 1;
        c = prochaineLettre(in);
    }
    return tab;
}

int longueurMotPasseVigenere(FILE *in)
{
    double idx = 0;
    int i_max = 0;
    double max = 0;
    for (int i = 1; i <= 30; i++)
    {
        FILE *f5;
        f5 = fopen("f5.txt", "w+");
        decouperFichier(in, f5, i, 0);
        rewind(f5);
        idx = IndiceCoincidence(f5);
        if (idx > max)
        {
            max = idx;
            i_max = i;
        }
        fclose(f5);
    }
    return i_max;
}