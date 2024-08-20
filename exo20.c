#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <poll.h>

char hash[1 + 2 * MD5_DIGEST_LENGTH] = {0};

char* md5hash(const char *str) {
    unsigned char md5[MD5_DIGEST_LENGTH] = {0};
    MD5((const unsigned char *)str, strlen(str), md5);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(hash + 2 * i, "%02x", md5[i]);
    }
    return hash;
}

int zeros(const char *s, int n) {
    for (int i = 0; i < n; i++) {
        if (s[i] != '0') { 
            return 0;
        }
    }
    return 1;
}

void bruteforce(int first, int step, int zero, int pipe_write) {
    char str[128];
    int count = 0;
    while (true) {
        sprintf(str, "%d", first);
        md5hash(str);
        if (zeros(hash, zero)) {
            write(pipe_write, &first, sizeof(int));
            count++;
            if (count == 5) 
                break;
        }
        first += step;
    }
    close(pipe_write);
    exit(0);
}

int main(int argc, char **argv) {
    int child_pid[10];
    int status;

    int pipes[10][2]; 

    for (int i = 0; i < 10; i++) {
        if (pipe(pipes[i]) == -1) { 
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        child_pid[i] = fork();
        if (child_pid[i] < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid[i] == 0) {
            close(pipes[i][0]); 
            bruteforce(i, 10, 6, pipes[i][1]); 
        }
    }

    int found_nonces[5] = {0};
    int found_count = 0;

    struct pollfd pollfds[10]; // serveiller les evenments
    for (int i = 0; i < 10; i++) {
        pollfds[i].fd = pipes[i][0]; 
        pollfds[i].events = POLLIN; 
    }

    while (found_count < 5) {
        int ret = poll(pollfds, 10, -1);
        if (ret == -1) {
            perror("poll");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 10; i++) {
            if (pollfds[i].revents & POLLIN) {
                read(pollfds[i].fd, &found_nonces[found_count], sizeof(int));
                printf("Nonce found: %d\n", found_nonces[found_count]);
                found_count++;
            }
        }
    }

   
    for (int i = 0; i < 10; i++) {
        kill(child_pid[i], SIGTERM);
    }

    
    for (int i = 0; i < 10; i++) {
        waitpid(child_pid[i], &status, 0);
    }

    return 0;
    
}


