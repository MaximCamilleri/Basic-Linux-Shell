#include "linkedlist.c"
void initializeEnv(node **head, node **tail);
char* getCWD();
char* getUSER();
char* getPATH();
char* getPROMPT();
char* getHOME();
char* getSHELL();
void getTERMINAL();
int getEXITCODE();
bool printEnv(char* envName, char* filename, int redirect);
char* getENV(char *input);