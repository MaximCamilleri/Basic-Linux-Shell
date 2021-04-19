#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "variables.h"

void initializeEnv(node **head){
    node *temp;
    node *tail;

    addLinkedList(getCWD(), "CWD", head, &tail);
    addLinkedList(getUSER(), "USER", head, &tail);
    addLinkedList(getPATH(), "PATH", head, &tail);
    addLinkedList(getPROMPT(), "PROMPT", head, &tail);
    addLinkedList(getHOME(), "HOME", head, &tail);
    // temp = createNewNode(getSHELL(), "SHELL"); 
    // insertNode(tail, temp);
    // tail = temp;
    //temp = createNewNode(getTERMINAL(), "TERMINAL"); 
    //insertNode(tail, temp);
    //tail = temp;
    // temp = createNewNode(getEXITCODE(), "EXITCODE"); 
    // insertNode(tail, temp);
    // tail = temp;
}

char* getCWD(){
    char *cwd;
    if(cwd = getenv("PWD")){
        return cwd;
    }
    else{
        return NULL;
    }
}

char* getUSER(){
    char *user;
    if(user = getenv("USER")){
        return user;
    }
    else{
        return NULL;
    }
}

char* getPATH(){
    char *path;
    if(path = getenv("PATH")){
        return path;
    }
    else{
        return NULL;
    }
}

char* getPROMPT(){
    return ">>>";
}

char* getHOME(){
    char *home;
    if(home = getenv("HOME")){
        return home;
    }
    else{
        return NULL;
    }
}

char* getSHELL(){ // no idea how to do this
    char *home;
    if(home = getenv("HOME")){
        printf("%s\n", home);
    }
    else{
        return NULL;
    }
}

void getTERMINAL(){
    if(fork() == 0){
        char exec_msg[64];
        if(execlp("tty", "tty", NULL) == -1){
            snprintf(exec_msg, sizeof(exec_msg), "Failed to run [%d]", errno);
            perror("Failed to exec");
            exit(EXIT_FAILURE);
        }
    }
}

int getEXITCODE(){
    int error = errno;
    return error;
}

