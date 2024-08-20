#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _WIDTH 4
#define _HEIGHT 4
#define _PLAYERS 2

bool get_grid_parameters(int argc, char *argv[], int *width, int *height, int *players) {


    *width = _WIDTH;
    *height = _HEIGHT;
    *players = _PLAYERS;

    if (argc > 1) {
        *width = atoi(argv[1]);
    } else {
        char *width_env = getenv("P4WIDTH");
        if (width_env != NULL) {
            *width = atoi(width_env);
        }
    }

    if (argc > 2) {
        *height = atoi(argv[2]);
    } else {
        char *height_env = getenv("P4HEIGHT");
        if (height_env != NULL) {
            *height = atoi(height_env);
        }
    }

    if (argc > 3) {
        *players = atoi(argv[3]);
    } else {
        char *players_env = getenv("P4PLAYERS");
        if (players_env != NULL) {
            *players = atoi(players_env);
        }
    }

    if(*width>26||*width<4){
        *width = _WIDTH;
    }
    if(*height>26||*height<4){
        *height = _HEIGHT;
    }
    if(*players>26||*players<4){
        *players = _PLAYERS;
    }

    return true; 
}

int main(int argc, char *argv[]) {
    int width, height, players;

    if (!get_grid_parameters(argc, argv, &width, &height, &players)) {
        fprintf(stderr, ".\n");
        
    }


    return 0; 
}
