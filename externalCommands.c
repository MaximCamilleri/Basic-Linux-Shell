// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>
// #include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// #include <signal.h>
#include "externalCommands.h"

#define MAXARGS 20



// Exit code to use when execvp fails
#define CUSTOM_EXIT_CODE 4

bool fork_and_exec(node *args){
    // Basic error checking
    if (args == NULL){
        return false;
    }
    char *argsArray[MAXARGS];
    for(int i = 0; i < MAXARGS; i++){
        argsArray[i] = 0;
    }
    copyArgs(args, argsArray);

    // Fork and exec
    pid_t pid_result = fork();
    if (pid_result == -1) {
        perror("fork failed");
        return false;
    }


    if (pid_result == 0) {
        
        // This is child - call execvp
        if (execvp(argsArray[0], argsArray) == -1){
            perror("The command was not found");
            exit(CUSTOM_EXIT_CODE);
        }
    } else {
        // This is parent
        int status;
        if (waitpid(pid_result, &status, 0) == -1){
            perror("waitpid failed");
            return false;
        }

        // execvp failed (using custom error code 4)
        if (WIFEXITED(status) && WEXITSTATUS(status) == CUSTOM_EXIT_CODE) {
            return false;
        }
    }

    return true;
}

  // Parse and copy tokens
        

void copyArgs(node *head, char *args[]){
    node *temp = head;
    int i = 0;
        while(temp != NULL && i < (MAXARGS - 1)){
            args[i] = temp->value;
            temp = temp->next;
            i++;
        }
}

int piping(node *head){

    int saved_stdout;


    /* Save current stdout for use later */
    saved_stdout = dup(1);
    

    node *temp = head;
    int processCounter = 0;
    while(temp != NULL){
        if(strcmp(temp->value, "\"PIPE\"") == 0){
            processCounter++;
        }
        temp = temp->next;
    }

    temp = head;
    char *args[processCounter + 1][MAXARGS];
    int argsCounter = 0;
    int commandCounter = 0;

    processCounter++;

    while(temp != NULL){
        if(strcmp(temp->value, "\"PIPE\"") != 0){
            args[commandCounter][argsCounter] = temp->value;
            argsCounter++;
        }else{
            args[commandCounter][argsCounter] = NULL;
            commandCounter++;
            argsCounter = 0;
        }
        temp = temp->next;
    }
    args[commandCounter][argsCounter] = NULL;
    
    setvbuf(stdout, NULL, _IONBF, 0);
    int pids[processCounter];
    int pipes[processCounter + 1][2];
    int i;
    
    for (i = 0; i < processCounter + 1; i++) {
        if (pipe(pipes[i]) == -1) {
            printf("Error with creating pipe\n");
            return 1;
        }
    }

    for (i = 0; i < processCounter; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            printf("Error with creating process\n");
            return 2;
        }
        if (pids[i] == 0) {
            // Child process
            dup2(pipes[i][0], STDIN_FILENO);
            if(i != processCounter -1){
                dup2(pipes[i + 1][1], STDOUT_FILENO);
            }

            for(int k = 0; k < processCounter + 1; k++){
                close(pipes[k][0]);
                close(pipes[k][1]);
            }
            
            execvp(args[i][0], args[i]);
            return 0;
        }
    }

    // Main process

    for(int k = 0; k < processCounter + 1; k++){
        close(pipes[k][0]);
        close(pipes[k][1]);
    }

    for (i = 0; i < processCounter; i++) {
        wait(NULL);
    }
    printf("\n");
    return 0; 
}