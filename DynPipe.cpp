// file: DynPipe.cpp
// author: Veer Waje
// date: 04/11/2024
// purpose: CS3377
// description:
// this program allows for multiple commands to be piped into each other
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (argc < 3 || argc > 6) {
        printf("need to have args within the specified amount");
        exit(1);
    }

    int numPipes = argc - 2;
    //above line means that the pipes created is one less than args passed. 
    int pipes[2 * numPipes];
    for (int i = 0; i < numPipes; i++) {
        if (pipe(pipes + i*2) == -1) {
            perror("Failed to create pipe");
            exit(1);
        }
    }

    for (int i = 0; i < argc - 1; i++) {
        if (fork() == 0) {
            // Redirect stdin if not the first command
            if (i != 0) {
                dup2(pipes[(i - 1) * 2], 0);
            }
            // Redirect stdout if not the last command
            if (i != argc - 2) {
                dup2(pipes[i * 2 + 1], 1);
            }
            // Close all pipes
            for (int j = 0; j < 2 * numPipes; j++) {
                close(pipes[j]);
            }
            // Split the command into executable and arguments
            char *cmd = argv[i + 1];
            char *exec_args[64];
            char *token = strtok(cmd, " ");
            int k = 0;
            while (token != NULL) {
                exec_args[k++] = token;
                token = strtok(NULL, " ");
            }
            exec_args[k] = NULL;
            execvp(exec_args[0], exec_args);
            perror("execvp");
            exit(1);
        }
    }

    // Parent closes all pipes and waits for children
    for (int i = 0; i < 2 * numPipes; i++) {
        close(pipes[i]);
    }
    for (int i = 0; i < argc - 1; i++) {
        wait(NULL);
    }

    return 0;
}
