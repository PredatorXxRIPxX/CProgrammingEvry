#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <glob.h>

int main() {

    glob_t globebuffer;
    if(glob("*.c",0,NULL,&globebuffer)!=0){
        perror("globe failure");
        exit(EXIT_FAILURE);
    }

    int pipeid[2];
    pid_t ls_child, sed_child;

    if (pipe(pipeid) == -1) {
        perror("Erreur lors de la création du tube");
        exit(EXIT_FAILURE);
    }

    ls_child = fork();
    if (ls_child == -1) {
        perror("Erreur lors de la création du premier enfant");
        exit(EXIT_FAILURE);
    } else if (ls_child == 0) {
        close(pipeid[0]);
        dup2(pipeid[1], STDOUT_FILENO);
        execlp("ls", "ls", "-l", NULL);
        perror("execlep ls");
        exit(EXIT_FAILURE);
    }

    sed_child = fork();
    if (sed_child == -1) {
        perror("Erreur lors de la création du deuxième enfant");
        exit(EXIT_FAILURE);
    } else if (sed_child == 0) {
        close(pipeid[1]);
        dup2(pipeid[0], STDIN_FILENO);
        execlp("sed", "sed", "s/\\.c$/.COUCOU/", NULL);
        perror("execlp sed");
        exit(EXIT_FAILURE);
    }

    // Fermeture des extrémités du tube dans le processus parent
    close(pipeid[0]);
    close(pipeid[1]);

    // Attente de la terminaison des processus fils
    waitpid(ls_child, NULL, 0);
    waitpid(sed_child, NULL, 0);

    globfree(&globebuffer);

    return 0;
}
