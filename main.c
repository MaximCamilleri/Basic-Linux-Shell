#include "main.h"

#define COMMANDSIZE 100
#define COMMANDNAME "tok"

extern char **environ;  // stores the environment variables
node *headVar = NULL;
node *tailVar = NULL;

node *environHead = NULL;

node *headCommand = NULL; // start of the linked list
node *tailCommand = NULL; // end of the linked list

int main(int argc, char **argv[]){
    setvbuf(stdout, NULL, _IONBF, 0);

    initializeEnv(&environHead);
    
    input();
    atexit(atExit);
    return EXIT_SUCCESS;
}

void atExit(){
    destroy(&headVar);
    destroy(&environHead);
}

void input(){
    char *line;
    printf("\033[32m");
    fflush(stdout);
    node *prompt = searchByName(&environHead, "PROMPT");
    while((line = linenoise(prompt->value)) != NULL){  // linenoise stores the text entered in stdin, it also prints >>>
        printf("\033[00m");
        fflush(stdout);
        if(strcmp(line, "exit") == 0){  // if the user inputed exit then the code will terminate 
            exit(EXIT_SUCCESS);
        }

        tokenisation(line);
        commands(headCommand);

        destroy(&headCommand); //deallocate the link list from the heap after it is done being used
        linenoiseFree(line); //deallocate the linenoise form the heap
        printf("\033[32m");
        fflush(stdout);
    }
}

void tokenisation(char *input){
    int startPointer = 0; //index of the start of the current command 
    int length = 0; //lenght of the current ocmmand
    char command[COMMANDSIZE];
    char var[COMMANDSIZE];
    char val[COMMANDSIZE];

    for (int i = 0; input[i] > 1; i++){
        if(input[i] == 92){ // checks for escape character backslash
            deleteChar(input, i);

        }else if(input[i] == 34){ // checks for "
            if(input[i-1] == 32){
                startPointer = i;
            }
            deleteChar(input, i);

            for(int j = i; input[i] > 1; j++){ //loops till EOF or a second " is found
                if(input[j] == 34){
                    i = j; //skip over everything that was in the ""
                    length = (i - startPointer);
                    deleteChar(input, i);
                    if(input[i+1] < 1){
                        length = (i - startPointer);
                        partition(startPointer, length, input, command);
                        addLinkedList(command, COMMANDNAME, &headCommand, &tailCommand);
                    }
                    break;
                }
            }
            i--; // decriment i to check the character that is directly after the closing " that was just deleted
            
        }else if(input[i] == 32){ // checks for space
            length = i - startPointer;
            partition(startPointer, length, input, command);
            addLinkedList(command, COMMANDNAME, &headCommand, &tailCommand);
            startPointer = i+1;

        }else if(input[i] == 36){ // checks for $
            startPointer = i+1;
            if(input[startPointer] == 123){
                startPointer++;
                i = expandVar(startPointer, input, 125);

            }else{
                i = expandVar(startPointer, input, 32);
            }
            
            
        }else if(input[i] == 61){ // checks for =
            node *tempReplace;

            length = i - startPointer;
            partition(startPointer, length, input, var);
            startPointer = i+1;

            for(int k = i; input[k] > 1; k++){
                if(input[k] == 32 || input[k+1] < 1){
                    i = k;
                    if(input[k+1] < 1){
                        length = (i - startPointer)+1;
                    }else{
                        length = (i - startPointer);
                    }
                    partition(startPointer, length, input, val);
                    startPointer = i+1;
                    tempReplace = searchByName(&environHead, var);
                    if(tempReplace == NULL){
                        tempReplace = searchByName(&headVar, var);
                        if(tempReplace == NULL){
                            addLinkedList(val, var, &headVar, &tailVar);
                        }
                    }else{
                        replaceValue(tempReplace, val);
                        break;
                    }
                    
                }
            }

        }else if(input[i+1] < 1){ // checks for EOF
            length = (i - startPointer)+1;
            partition(startPointer, length, input, command);
            addLinkedList(command, COMMANDNAME, &headCommand, &tailCommand);
        }
    }
    printlist(headCommand);
}

void deleteChar(char *input, int index){
    int i;
    for(i = index; input[i] > 1; i++){ // replaces the entry to be deleted with the one after it. repeats this till the end of the list
        input[i] = input[i+1];
    }
    input[i] = 0; // sents the last element to null
}

void partition(int start, int lenght, char *input, char command[]){
    for(int i = 0; i < COMMANDSIZE; i++){
        command[i] = 0; // initilizes placeholder to null
    }

    command[0] = *(input+start);
    for(int i = 1; i < lenght; i++){ // stors token in placholder
        command[i] = *(input+start+i);
    }
}

int expandVar(int startPointer, char* input, char stopCondition){
    int i;
    int length;
    node *tempPrint;
    char var[COMMANDSIZE];
    char val[COMMANDSIZE];

    for(int k = startPointer; input[k] > 1; k++){
        if(input[k] == stopCondition || input[k+1] < 1){
            i = k;
            
            if(input[k+1] < 1){
                length = (i - startPointer)+1;
            }else{
                length = (i - startPointer);
            }
            if(input[k] == 125){
                length--;
            }
            partition(startPointer, length, input, var);
            tempPrint = searchByName(&environHead, var);
            if(tempPrint == NULL){
                tempPrint = searchByName(&headVar, var);
                if(tempPrint != NULL){
                    addLinkedList(tempPrint->value, var, &headCommand, &tailCommand);  
                }else{
                    printf("\033[31m");
                    fflush(stdout);
                    printf("Variable [%s] was not found", var);
                    printf("\033[00m");
                    fflush(stdout);
                }
            }else{
                addLinkedList(tempPrint->value, var, &headCommand, &tailCommand);  
            }
        }
    }
    return i;
}

void commands(node *head){
    node *temp = head;
    node *temp2 = NULL;
    node *replaceTemp;
    int success;
    while(temp != NULL){
        if(strcmp(temp->value, "cd") == 0)
        {
            chdir("..");
            replaceTemp = searchByName(&environHead, "CWD");
            replaceValue(replaceTemp, getCWD());
        }else if(strcmp(temp->value, "echo") == 0){
            while(temp->next != NULL){
                temp = temp->next;
                fprintf(stdout, "%s ", temp->value); 
            }
            printf("\n");

        }else if(strcmp(temp->value, "showvar") == 0){
            if(temp->next != NULL){
                temp2 = searchByName(&headVar, temp->next->value);
                if(temp2 == NULL){
                        printf("\033[31m");
                        printf("Variable [%s] was not found\n", temp->next->value);
                        printf("\033[00m");
                }else{
                    printNameValue(temp2);
                }
            }else{
                
                printNameValues(headVar);
            }
        }else if(strcmp(temp->value, "showenv") == 0){
            if(temp->next != NULL){
                temp2 = searchByName(&environHead, temp->next->value);
                if(temp2 == NULL){
                    printf("\033[31m");
                    printf("Variable [%s] was not found\n", temp->next->value);
                    printf("\033[00m");
                }else{
                    printNameValue(temp2);
                }
            }else{
                printNameValues(environHead);
            }


        }else if(strcmp(temp->value, "export") == 0){
            if(temp->next != NULL){
                temp2 = searchByName(&environHead, temp->next->value);
                if (temp2 == NULL){
                    temp2 = searchByName(&headVar, temp->next->value);
                    if(temp2 == NULL){
                        printError("The variable does not exist");
                    }else{
                        setenv(temp2->name, temp2->value, 1);
                    }
                    
                }else{
                    printError("The variable is already in the environment");
                }
                
            }else{
                printError("No variable was specified");
            }
        }else if(strcmp(temp->value, "unset") == 0){
            if(temp->next != NULL){
                unsetenv(temp->next->value);
                deleteNode(&headVar, temp->next->value);
            }else{
                printError("No variable was specified");
            }
        }
        temp = temp->next;
    }
}

void printError(char *error){
    printf("\033[31m");
    printf("%s\n", error);
    printf("\033[00m");
}
