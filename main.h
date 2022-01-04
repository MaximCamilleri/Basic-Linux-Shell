#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "linenoise/linenoise.c"
#include "stack.c"
#include "readingFromFIle.c"
#include "externalCommands.c"
#include <dirent.h>
#include <errno.h>

typedef enum output{
    oneLineValues = 0,
    lineValueName = 1,
    lineValue = 2

}outputType;


void input();
void deleteChar(char *input, int index);
void partition(int start, int lenght, char *input, char command[]);
void atExit();
int expandVar(int startPointer, char* input, char stopCondition, char **ret);
void commands(node *head);
void CWDPrompt(node * cwd);

int quotationMarks(char *input, int i, int start);
int space(int i, int start, char *input, node **head, node **tail);
int equalsEvaluation(int i, int start, char *input);
int dollarSign(int start, int i, char *input, char **ret);

bool source(node *temp, char *filename, int redirect);
int addingVar(int i, int start, int length, char *input, char var[]);
void pushDirToStack(char *wpd);
void export(node *temp, char *filename, int redirect);
void deleteVar(node *temp);
bool showLinkedList(node *temp, node *outputHead, char* filename, int redirect);
void echo(node *temp, char* filename, int redirect);
void cd(char *cwd, bool popd);
void pushd(node *temp, char *filename, int redirect);
void endOFLine(int i, int startPointer, char *input, node **head, node **tail);
void popd(node **head, char *filename, int redirect);
void output(node *temp, FILE *outputLocation, outputType convertionType);
char *checkForRedirect(node *head, int *redirectType);
int variableExpansion(int i, int start, char* input, node **headTemp, node **tailTemp);
void dirs(char* filename, int redirect);
void unset(node *temp, char* filename, int redirect); 
void updateExitcode();

bool varNameCheck(char *var);
void findNextCommand(node **head);
void quoteCheck(char* input, node **head, node** tail);
int expandVariables(char* input, int startPointer, node **head, node** tail);