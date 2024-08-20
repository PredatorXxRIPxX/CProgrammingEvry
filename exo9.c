#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_size 100

typedef struct {
    char *pile;
    int taille;
} pile;

int getfirt(pile *user){
    int curr = 0;
    char * value = malloc(sizeof(char));
    while (user->pile[curr]!="+"||user->pile[curr]!="-"||user->pile[curr]!="/"||user->pile[curr]!="*")
    {

        curr++;
    }
    return atoi(value);
}

float traitment(pile *user_pile){
    float tmpResult= 0;
    char ope=NULL;
    for(int index = 0 ; index < user_pile->taille ; index++){
        if(user_pile->pile[index]=="+"){
            ope = user_pile->pile[index];
            
        }else if(user_pile->pile[index]=="-"){
            ope = user_pile->pile[index];

        }else if(user_pile->pile[index]=="/"){
            ope = user_pile->pile[index];

        }else if(user_pile->pile[index]=="*"){
            ope = user_pile->pile[index];
        }
    }
    int firstval = getfirst(&user_pile);
    return tmpResult;
}

int main(int argc, char *argv[]) {
    pile *mypile = malloc(sizeof(pile));
    mypile->taille = argc;
    mypile->pile = malloc(max_size * sizeof(char));

    for (int index = 0; index < argc; index++) {
        if (strlen(argv[index]) < max_size) {
            strcpy(mypile->pile, argv[index]);
        } else {
            fprintf(stderr, "Argument %d is too long\n", index);
            free(mypile->pile);
            free(mypile);
            return 1;
        }
    }
    
    if(mypile->pile!=NULL){
        float result = traitment(&mypile);
        printf("votre resultat %f",result);
    }else{
        exit(EXIT_FAILURE);
    }

    return 0;
}
