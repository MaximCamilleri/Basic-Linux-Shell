#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "variables.h"

extern char **environ;

void initializeEnv(node **head, node **tail){
    node *temp;
    char *cwd;
    addLinkedList(cwd = getENV("PWD"), "CWD", head, tail);
    addLinkedList(getENV("USER"), "USER", head, tail);
    addLinkedList(getENV("PATH"), "PATH", head, tail);
    addLinkedList(getPROMPT(cwd), "PROMPT", head, tail);
    addLinkedList(getENV("HOME"), "HOME", head, tail);
    addLinkedList(getENV("SHELL"), "SHELL", head, tail);
    addLinkedList(ttyname(STDIN_FILENO), "TERMINAL", head, tail);
}

char* getENV(char *input){
    char *ret;
    if(ret = getenv(input)){
        return ret;
    }else{
        return NULL;
    }
}

char* getPROMPT(char *cwd){
    char s[100];
    char *prompt = strcat(cwd, " >");
    return prompt;
}

int getEXITCODE(){
    int error = errno;
    return error;
}


