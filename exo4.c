#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char base;
    unsigned int len;
    unsigned char *digits;
}number;

const *chiffre = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";


number from_string(char *str , unsigned char base){
    int bases = atoi(base);
    unsigned char * tmp = malloc(strlen(str)*sizeof(char));
    int counter = 0;
    for(int index = strlen(chiffre)-1;index>=0;index--){
        const char *ptr = strchr(chiffre,str[index]);
        if(ptr!=NULL){
            tmp[counter] = ptr - chiffre ;
        }
        counter++;
    }
    number s = {.base = base,.len=strlen(tmp),.digits = tmp};
    return s;
}

number to_base(number nbr,unsigned char base){
    int nbr = to_uint(nbr);
    int bases = atoi(base);
    if(bases>=64||bases<2){
        return;
    }
    number tmp = {.base=base,.len = 0,.digits=NULL};
    int counter = 0;
    number * digits = malloc(8*sizeof(unsigned char));
    do
    {
        digits[counter] = (char)(nbr.digits[nbr.len-counter]%bases);
        counter++;
    } while (nbr.digits[0]!=0);
    tmp.len=counter;
    tmp.digits=digits;
    return tmp;
}

number add_number(number a , number b){
    number  tmp1 = to_base(a,"2");
    number tmp2 = to_base(b,"2");


}


void main(void){};