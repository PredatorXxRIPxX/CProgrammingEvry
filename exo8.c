#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define default_player 2
#define default_width 4
#define default_height 4

bool getvar(int argc,char*argv[],int *height,int *width,int *players){
    *height = default_height;
    *width = default_width;
    *players = default_player;
    if(argc>1){
        height = atoi(argv[1]);
    }else{
        char *height_tmp = getenv("P4HEIGHT");
    }
    if(argc>2){
        width = atoi(argv)
    }
}

int main(int argc , char*argv[]){
    int height,width,players;
    if(!getvar(argc,argv,&height,&width,&players)){
        fprintf(stderr,"invalide");
    }

}