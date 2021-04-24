#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "linenoise/linenoise.c"
#include "variables.c"

void input();
void tokenisation(char *line);
void deleteChar(char *input, int index);
void tokenisation(char *input);
void partition(int start, int lenght, char *input, char command[]);
void atExit();
int expandVar(int startPointer, char* input, char stopCondition);
void commands(node *head);
void printError(char *error);