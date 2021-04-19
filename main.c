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
    
    environHead = initializeEnv(environHead);
    
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
    //node *prompt = searchByName(&environHead, "PROMPT");
    while((line = linenoise(">>>")) != NULL){  // linenoise stores the text entered in stdin, it also prints >>>
        if(strcmp(line, "exit") == 0){  // if the user inputed exit then the code will terminate 
            exit(EXIT_SUCCESS);
        }
        tokenisation(line);

        destroy(&headCommand); //deallocate the link list from the heap after it is done being used
        linenoiseFree(line); //deallocate the linenoise form the heap
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
            i--; // dicriment i to check the character that is directly after the closing " that was just deleted
            
        }else if(input[i] == 32){ // checks for space
            length = i - startPointer;
            partition(startPointer, length, input, command);
            addLinkedList(command, COMMANDNAME, &headCommand, &tailCommand);
            startPointer = i+1;

        }else if(input[i] == 36){
            startPointer = i+1;
            node *tempPrint;

            for(int k = startPointer; input[k] > 1; k++){
                if(input[k] == 32 || input[k+1] < 1){
                    i = k;
                    if(input[k+1] < 1){
                        length = (i - startPointer)+1;
                    }else{
                        length = (i - startPointer);
                    }
                    partition(startPointer, length, input, var);
                    tempPrint = searchByName(&environHead, var);
                    addLinkedList(command, COMMANDNAME, &headCommand, &tailCommand);
                }
            }
            
        }else if(input[i] == 61){
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


void addLinkedList(char *value, char *name, node** head, node** tail){
    node *temp;

    temp = createNewNode(value, name); // creats a new node with the value of placholder
    if(*head == NULL)
    {
        *head = temp;
        *tail = temp;
    }
    else{
        insertNode(*tail, temp); //adds the node to the linked list 
        *tail = temp;
    }
}

