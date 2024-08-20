#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t ls_pid, sed_pid;

    // Création du pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Création du premier processus (ls)
    ls_pid = fork();
    if (ls_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (ls_pid == 0) { // Code exécuté par le processus fils (ls)
        close(pipefd[0]); // Ferme l'extrémité de lecture du pipe dans le processus fils
        dup2(pipefd[1], STDOUT_FILENO); // Redirige la sortie standard vers l'extrémité d'écriture du pipe
        execlp("ls", "ls", "-l", NULL); // Exécute la commande ls avec ses arguments
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    // Création du deuxième processus (sed)
    sed_pid = fork();
    if (sed_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (sed_pid == 0) { // Code exécuté par le processus fils (sed)
        close(pipefd[1]); // Ferme l'extrémité d'écriture du pipe dans le processus fils
        dup2(pipefd[0], STDIN_FILENO); // Redirige l'entrée standard vers l'extrémité de lecture du pipe
        execlp("sed", "sed", "s/\\.c$/.COUCOU/", NULL); // Exécute la commande sed avec son argument
        perror("execlp sed");
        exit(EXIT_FAILURE);
    }

    // Ferme les extrémités du pipe dans le processus parent
    close(pipefd[0]);
    close(pipefd[1]);

    // Attente de la terminaison des processus fils
    waitpid(ls_pid, NULL, 0);
    waitpid(sed_pid, NULL, 0);

    return 0; // Terminaison du programme principal avec un statut de sortie 0
}
