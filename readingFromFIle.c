#include "readingFromFile.h"

#define FILECONTENT 100

node *fileInputHead = NULL;
node *fileInputTail = NULL;

// execute a list of commands found in a file
bool fileExecution(const char *filename){
    FILE *fp;
    char line[FILECONTENT];
    fp = openingFile(filename, 0); // open a file to be read 
    initialize(line, FILECONTENT);
    
    if (fp == NULL) // checks if the file exists
    {
        return false; // file execution failed
    } 
    else{
        char ch;
        char counter = 0;
        while(ch != EOF){
            while((ch=fgetc(fp))!=EOF && ch != 10){ // loops through the file till it finds the end of file or a new line
                if(ch != 13){ // ignores the \r
                    line[counter] = ch;
                    counter++;
                }
            }
            if(ch == EOF){
            break;
            }
            commandExecution(line); // executes the command read from the file
            initialize(line, FILECONTENT);
            counter = 0;
        }
    }
    return true; // file executed sussesfully
}

void tokenizationFromFile(FILE *fp, char line[]){
    destroy(&fileInputHead);
    char ch;
    char counter = 0;
    while((ch=fgetc(fp))!=EOF){
        if(ch != 13 && ch != 10){
            line[counter] = ch;
            counter++;
        }
    }
    
    tokenisation(line, &fileInputHead, &fileInputTail);
}

//sets an array to \0
void initialize(char line[], size_t size){
    for (int i = 0; i < size; i++)
    {
        line[i] = 0;
    }
}
//writes the contents of line to a file
bool writingToFile(const char *filename, char *line){
    FILE *fp;
    fp = openingFile(filename, 1); //opens file to write

    if (fp == NULL)
    {
        return false; // file does not exist
    } 
    else{
        fprintf(fp,"%s", line);
        return true; //file exists and line has been writen
    }
}
//read 0 = read
//read 1 = write
//read 2 = append
FILE *openingFile(const char *filename, int read){
    FILE *fp;
    if(read == 0){
        if((fp = fopen(filename, "r")) == NULL){ // opens in read
            printError("The file was not found");
            return NULL;
        }
    }else if(read == 1){
        if((fp = fopen(filename, "w")) == NULL){ // opens in write 
            printError("The file was not found");
            return NULL;
        }
        
    }else if(read == 2){
        if((fp = fopen(filename, "a")) == NULL){ // opens in append
            printError("The file was not found");
            return NULL;
        }
    }
    return fp;
}

FILE *initializeFile(char* filename, int redirect){
    FILE *fp;
    fp = openingFile(filename, redirect);
    return fp;
}

