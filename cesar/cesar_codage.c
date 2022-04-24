#include <stdlib.h>
#include <stdio.h>

void cesar(char*, int, char*);

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        fprintf(stderr, "format invalide vous devez suivre la forme suivante : ./exe entree decalage sortie \n");
        return EXIT_FAILURE;
    }
    cesar(argv[1],atoi(argv[2]),argv[3]);
    return EXIT_SUCCESS;
}

void cesar(char* entree , int decalage ,char* sortie)
{
    FILE *f;
    FILE *f2;
    f=fopen(entree,"rb");
    f2=fopen(sortie,"w+");
    char r;
    int e,i=0;

    if(f == NULL || f2 == NULL)
    {
        fprintf(stderr,"Erreur");
        exit(-1);    
        }

    
    while (e !=EOF)
    {
        e = fscanf(f, "%c", &r);
        
        if (r>='a' && r<='z')
        {
            fprintf(f2,"%c",(r - 'a' + decalage +26)% 26 + 'a');
        }else if (r>='A' && r<='Z')
        {
            fprintf(f2,"%c",(r - 'A' + decalage +26)% 26 + 'A');
        }else{
            fprintf(f2,"%c",r);
        }        
        i++;
    }
    fclose(f);
    fclose(f2);
}