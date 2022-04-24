#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct
{
    double qt[26][26][26][26];
} quadgr;

void affectation(FILE *, quadgr *);
double valeur_quadgram(quadgr *, char, char, char, char);
void permute(char *);
void decrypt(char *, char *, char *);
void last(char *input, quadgr *quad, char *);
double compute_score(char *input, quadgr *quad);
void ecrire_fichier(char* result, char *);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "veuillez executer avec la forme ./exe quadgram_txt entree_txt sortie_txt \n");
        return EXIT_FAILURE;
    }
    srand(time(NULL));
    FILE *f;
    f = fopen(argv[1], "r");
    FILE *f2;
    f2 = fopen(argv[2], "r");
    if (f == NULL || f2 == NULL)
    {
        fprintf(stderr, "erreur à l'ouverture du fichier \n");
        return EXIT_FAILURE;
    }
    quadgr quad;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            for (int k = 0; k < 26; k++)
            {
                for (int l = 0; l < 26; l++)
                {
                    quad.qt[i][j][k][l] = 0;
                }
            }
        }
    }
    fseek(f2, 0, SEEK_END);
    long a = ftell(f2);
    rewind(f2);
    char *test = malloc(sizeof(char) * a);
    fgets(test, sizeof(char) * a, f2);
    affectation(f, &quad);
    last(test, &quad, argv[3]);
}

void affectation(FILE *in, quadgr *quad)
{

    int e, idx = 0;
    float S = 0.0;
    char r;
    int i = 0, j = 0, k = 0, l = 0;
    e = fscanf(in, "%c", &r);

    while (e != EOF)
    {
        if (r == ' ')
        {
            idx = 0;
        }

        if (r >= 'a' && r <= 'z')
        {
            S = 0;
            if (idx == 0)
            {
                i = r - 'a';
            }
            else if (idx == 1)
            {
                j = r - 'a';
            }
            else if (idx == 2)
            {
                k = r - 'a';
            }
            else if (idx == 3)
            {
                l = r - 'a';
            }
            idx++;
        }
        if (r >= '0' && r <= '9')
        {
            if (quad->qt[i][j][k][l] != 0) // Si il existe plusieurs quadgrams
                S = quad->qt[i][j][k][l];
            S = S * 10 + r - '0';
            quad->qt[i][j][k][l] = S;
        }
        e = fscanf(in, "%c", &r);
    }
}

double valeur_quadgram(quadgr *quad, char c1, char c2, char c3, char c4)
{
    if (quad->qt[c1 - 'a'][c2 - 'a'][c3 - 'a'][c4 - 'a'] != 0)
        return quad->qt[c1 - 'a'][c2 - 'a'][c3 - 'a'][c4 - 'a'];
    else
        return 1;
}

double compute_score(char *input, quadgr *quad)
{
    double S = 0;
    int i;
    for (i = 0; i <= strlen(input) - 4; i++)
    {
        S += log(valeur_quadgram(quad, input[i], input[i + 1], input[i + 2], input[i + 3]));
    }
    return S;
}

void permute(char *mdp)
{
    int a, b, tmp;
    do
    {
        a = rand() % 26;
        b = rand() % 26;
    } while (a == b);
    tmp = mdp[a];
    mdp[a] = mdp[b];
    mdp[b] = tmp;
}

void decrypt(char *input, char *output, char *password)
{
    int i;
    for (i = 0; i < strlen(input); i++)
    {
        output[i] = password[input[i] - 'a'];
    }
    output[i] = '\0';
}

void last(char *input, quadgr *quad, char* output)
{
    char M[27] = "abcdefghijklmnopqrstuvwxyz";
    char M2[27];
    int i = 0;
    char *sortie = malloc(strlen(input) + 1);
    double S = 0;
    double S2 = 0;
    while (i < 1000)
    {
        strcpy(M2, M);
        permute(M2);

        decrypt(input, sortie, M);
        S = compute_score(sortie, quad);
        decrypt(input, sortie, M2);
        S2 = compute_score(sortie, quad);
        if (S2 > S)
        {
            strcpy(M, M2); //M = M2
            i = 0;
        }
        else
        {
            i++;
        }
    }
    decrypt(input, sortie, M);
    printf("last : %s\n", sortie);
    ecrire_fichier(sortie, output);
    
}

void ecrire_fichier(char* sortie, char * output)
{
    FILE *f;
    f = fopen(output, "w+");
    fprintf(f,"%s", sortie);
}