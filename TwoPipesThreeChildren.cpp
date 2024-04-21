// file: TwoPipesTwoChildren.cpp
// author: Veer Waje
// date: 04/11/2024
// purpose: CS3377
// description:
// this program executes "ls -ltr | grep 3376 | wc -l", using one parent and three children
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char **argv){
    int status;
    int childpid;
    int childpid2;
    int childpid3;
    char *cat_args[] = {"ls", "-ltr", NULL};
    char *grep_args[] = {"grep", "3376", NULL};
    char *wc_args[] = {"wc", "-l", NULL};
    // create one pipe to send the output of "ls" process to "grep" process
    int pipes[2];
    int pipes2[2];


    //stdin: 0
    //stdout: 1
    //stderr: 2

    pipe(pipes);
    pipe(pipes2);
    // fork the first child (to execute cat)



    if((childpid = fork()) == -1){
        perror("Error creating a child process");
        exit(1);
    }

    if (childpid == 0) {

        if((childpid2 = fork()) == -1){
            perror("Error creating a child process");
            exit(1);
        }

        if(childpid2 == 0) {

            if((childpid3 = fork()) == -1) {
                perror("Error creating a child process");
                exit(1);
            }

            if(childpid3 == 0) {
                // replace cat's stdout with write part of 1st pipe
                dup2(pipes[1], 1);
                // close all pipes (very important!); end we're using was safely copied
                close(pipes[0]);
                close(pipes[1]);
                execvp(*cat_args, cat_args); 
                exit(0);
            }

            else {
                // replace grep's stdin with read end of 1st pipe
                dup2(pipes[0], 0);
                //replace grep's stdout with write part of 2nd pipe
                dup2(pipes2[1], 1);
                // close all pipes (very important!); end we're using was safely copied
                close(pipes[0]);
                close(pipes[1]);
                close(pipes2[0]);
                close(pipes2[1]);
                execvp(*grep_args, grep_args); 
                exit(0);
            }

        }
        else {
            dup2(pipes2[0], 0);
            close(pipes[0]);
            close(pipes[1]);
            close(pipes2[0]);
            close(pipes2[1]);
            execvp(*wc_args, wc_args); 
        }
    }
    return(0);
}

//cat: writes to pipe

//grep: reads from pipe, writes to pipe2

//wc: reads from pipe2

//pipe2