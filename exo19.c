#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

volatile int counter = 0;

void traitment(int num){
    if(num==SIGINT){
        counter++;
        if(counter==1){
            printf("click CTRL + C  avant 2 second pour exit");
            alarm(2);
        }else if(counter==2){
            printf("GOODBYE \n");
            exit(EXIT_SUCCESS);
        }
    }
}

int main(){
    signal(SIGINT,traitment);
    while(1){
        printf("working...\n");
        sleep(1);
    }
    return 0;
}