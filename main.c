#include "main.h"

#define COMMANDSIZE 100
#define COMMANDNAME "tok"
#define STACKNAME "stack"
#define OUTPUT "out"


extern char **environ;  // stores the environment variables

node *shellVarHead = NULL;
node *shellVarTail = NULL;

node *stackHead = NULL;
node *buffer = NULL;

node *outputHead = NULL;

int main(int argc, char **argv[]){
    setvbuf(stdout, NULL, _IONBF, 0);
    initializeEnv(&shellVarHead, &shellVarTail);
    node* temp = searchByName(&shellVarHead, "CWD");
    pushDirToStack(temp->value);
    
    
    input();
    atexit(atExit);
    return EXIT_SUCCESS;
}

void atExit(){
    destroy(&shellVarHead);
    destroy(&stackHead);
    destroy(&headCommand);
    destroy(&outputHead);
}

void input(){
    char *line;
    printf("\033[32m");
    node *CWD = searchByName(&shellVarHead, "CWD");
    node *prompt = searchByName(&shellVarHead, "PROMPT");

    while((line = linenoise(prompt->value)) != NULL){  // linenoise stores the text entered in stdin, it also prints >>>
        printf("\033[00m");
        if(strcmp(line, "exit") == 0){  // if the user inputed exit then the code will terminate 
            exit(EXIT_SUCCESS);
        }

        tokenisation(line, &headCommand, &tailCommand);
        linenoiseFree(line); //deallocate the linenoise form the heap
        commands(headCommand);

        destroy(&headCommand); //deallocate the link list from the heap after it is done being used
        destroy(&outputHead);
        printf("\033[32m");

    }
}

void tokenisation(char *input, node **headTemp, node **tailTemp){
    int startPointer = 0; //index of the start of the current command 
    int length = 0; //lenght of the current ocmmand
    char command[COMMANDSIZE];
    bool inQuotes = false;


    for (int i = 0; input[i] > 1; i++){
        if(input[i] == 92){ // checks for escape character backslash
            deleteChar(input, i);
            if(input[i+1] < 1){
                endOFLine(i, startPointer,input, headTemp, tailTemp);
            }

        }else if(input[i] == 60){ // checks for <
            if(input[i-1] != 32 && input[i-1] != 9 && input[i-1] != 59 && input[i-1] != 60){
                startPointer = space(i, startPointer, input, headTemp, tailTemp);
            }else{
                startPointer++;
            }
            strcpy(command, "\"REDIRECTLEFT\"");
            addLinkedList(command, COMMANDNAME, headTemp, tailTemp);

        }else if(input[i] == 62){ // checks for >
            if(input[i-1] != 32 && input[i-1] != 9 && input[i-1] != 59 && input[i-1] != 62){
                startPointer = space(i, startPointer, input, headTemp, tailTemp);
            }else{
                startPointer++;
            }
            strcpy(command, "\"REDIRECTRIGHT\"");
            addLinkedList(command, COMMANDNAME, headTemp, tailTemp);

        }else if(input[i] == 124){ // checks for |
            if(input[i-1] != 32 && input[i-1] != 9 && input[i-1] != 59 && input[i-1] != 62){
                startPointer = space(i, startPointer, input, headTemp, tailTemp);
            }else{
                startPointer++;
            }
            strcpy(command, "\"PIPE\"");
            addLinkedList(command, COMMANDNAME, headTemp, tailTemp);

        }else if(input[i] == 34){ // checks for "
            if(input[i+1] > 1){
                i = quotationMarks(input, i, startPointer);
                inQuotes = true;
            }else{
                endOFLine(i, startPointer, input, headTemp, tailTemp);
            }
            

        }else if(input[i] == 32 || input[i] == 9 || input[i] == 59){ // checks for space

            if(inQuotes){
                length = i - startPointer;
                partition(startPointer, length, input, command);
                quoteCheck(command, headTemp, tailTemp);
                i++;
                startPointer = i;
                inQuotes = false;
            }else{
                if(input[startPointer] != 32 && input[startPointer] != 9 && input[startPointer] != 59){
                    startPointer = space(i, startPointer, input, headTemp, tailTemp);
                }else{
                    startPointer++;
                }
            }
            
            
            
        }else if(input[i] == 61){ // checks for =
            i = equalsEvaluation(i, startPointer, input);
            startPointer = i + 1;
        
        }else if(input[i] == 36){  //checks for $
            i = expandVariables(input,startPointer, headTemp, tailTemp);
            startPointer = i + 1;

        }else if(input[i+1] < 1){ // checks for EOF
            if(inQuotes){
                length = i - startPointer + 1;
                partition(startPointer, length, input, command);
                quoteCheck(command, headTemp, tailTemp);
                inQuotes = false;
            }else{
                endOFLine(i, startPointer, input, headTemp, tailTemp);
            }
            
        }
    }
    //printlist(*headTemp);
}

//
//Tokenisation methods 
//

void endOFLine(int i, int startPointer, char *input, node **head, node **tail){
    char command[COMMANDSIZE];

    int length = (i - startPointer)+1;
    partition(startPointer, length, input, command);
    addLinkedList(command, COMMANDNAME, head, tail);
}

//if  "
int quotationMarks(char *input, int i, int start){
    int length = 0;
    char** var;
    char command[COMMANDSIZE];
    bool found = false;
    if(input[i-1] == 32 || input[i-1] == 61){
        start = i;
    }
    deleteChar(input, i);

    for(int j = i; input[j] > 1; j++){ //loops till EOF or a second " is found
        if(input[j] == 34){
            i = j; //skip over everything that was in the ""
            found = true;
            deleteChar(input, i);
                i = i-2; // decriment i to check the character that is directly after the closing " that was just deleted
            
            break;
        }
    }

    if(!found){
        i--;
    }

    return i;
}


//checking quotes for \ and $
void quoteCheck(char* input, node **head, node** tail){
    char* var;
    char beginning[100];
    char end[100];
    int counter = 0;
    int i = 0;
    bool brackets = false;
    for (int i = 0; i < 100; i++){
        beginning[i] = 0;
        end[i] = 0;
    }
    
    for (i = 0; input[i] > 1; i++){
        if(input[i] == 36){  //checks for $
            int varPointer;
            int positionCounter;
            if(input[i + 1] == 123){
                varPointer = i + 2;
                brackets = true;
                positionCounter = varPointer;
                while(input[positionCounter] != 125 && input[positionCounter] > 1){
                    positionCounter++;
                }
            }else{
                varPointer = i + 1;
                positionCounter = varPointer;
                while(input[positionCounter] != 124 && input[positionCounter] != 59 && input[positionCounter] != 60 && 
                input[positionCounter] != 62 && input[positionCounter] != 32 && input[positionCounter] != 9 && input[positionCounter] > 1){
                    positionCounter++;
                }
            }

            char var[50];
            int lenght = positionCounter - varPointer;
            partition(varPointer, lenght, input, var);
            node *varNode = searchByName(&shellVarHead, var);
            char *val = varNode->value;

            for (int j = 0; j < i; j++){
                beginning[j] = input[j];
            }

            if(brackets){
                positionCounter++;
            }
            
            for (int j = positionCounter; input[j] > 1; j++){
                end[counter] = input[j];
                counter++;
            }

            strcat(beginning, val);
            strcat(beginning, end);
            break;

        }else if(input[i] == 92){
            deleteChar(input, i);
        }
    }
    if(beginning[0] == 0){
        addLinkedList(input, COMMANDNAME, head, tail);
    }else{
        addLinkedList(beginning, COMMANDNAME, head, tail);
    }
    
}

int expandVariables(char* input, int startPointer, node **head, node** tail){
    int varPointer;
    int positionCounter;
    char final[200];
    int finalCounter = 0;

    for(int i = 0; i < 200; i++){
        final[i] = 0;
    }

    while(input[startPointer] != 36){
        final[finalCounter] = input[startPointer];
        startPointer++;
        finalCounter++;
    }

    if(input[startPointer + 1] == 123){
        varPointer = startPointer + 2;
        positionCounter = varPointer;
        while(input[positionCounter] != 125 && input[positionCounter] > 1){
            positionCounter++;
        }
    }else{
        varPointer = startPointer + 1;
        positionCounter = varPointer;
        while(input[positionCounter] != 124 && input[positionCounter] != 59 && input[positionCounter] != 60 && 
        input[positionCounter] != 62 && input[positionCounter] != 32 && input[positionCounter] != 9 && input[positionCounter] > 1){
            positionCounter++;
        }
    }
    char var[50];
    int lenght = positionCounter - varPointer;
    partition(varPointer, lenght, input, var);
    node *varNode = searchByName(&shellVarHead, var);
    char *val = varNode->value;
    int varCounter = 0;
    for(int i = 0; val[i] > 1; i++){
        final[finalCounter] = val[varCounter];
        finalCounter++;
        varCounter++;
    }

    if(input[positionCounter] == 125){
        positionCounter++;
        while(input[positionCounter] != 124 && input[positionCounter] != 59 && input[positionCounter] != 60 && 
        input[positionCounter] != 62 && input[positionCounter] != 32 && input[positionCounter] != 9 && input[positionCounter] > 1){
            final[finalCounter] = input[positionCounter];
            positionCounter++;
            finalCounter++;
        }
    }
    addLinkedList(final, COMMANDNAME, head, tail);
    return positionCounter;

}

//if space
int space(int i, int start, char *input, node **head, node **tail){
    char command[COMMANDSIZE];
    int length = i - start;
    partition(start, length, input, command);
    addLinkedList(command, COMMANDNAME, head, tail);
    start = i+1;
}

//if =
int equalsEvaluation(int i, int start, char *input){
    bool check = false;
    char var[COMMANDSIZE];
    int length = i - start;


    partition(start, length, input, var);
    check = varNameCheck(var);
    if(check == false){
        printError("The variable name contains unsuported characters,");
        printError("characters must be a-z, A-Z, 0-9 or _,");
        printError("The variable name also cant start with a number!");
        return i;
    }
    start = i+1;
    int k;
    for(k = i; input[k] > 1; k++){
        if(input[k] == 92){ // backslash
            deleteChar(input, k);
            if(input[k+1] < 1){
                addingVar(k, start, length, input, var);
            }
            
        }else if(input[k] == 34){
            k = quotationMarks(input, k, start);

        }else if(input[k] == 32 || input[k+1] < 1){
           addingVar(k, start, length, input, var);
           break;

        }
    }
    return k;
}

int addingVar(int i, int start, int length, char *input, char var[]){
    char val[COMMANDSIZE];
    node *tempReplace;

    if(input[i+1] < 1){
        length = (i - start)+1;
    }else{
        length = (i - start);
    }
    
    partition(start, length, input, val);
    start = i+1;
    tempReplace = searchByName(&shellVarHead, var);
    if(tempReplace == NULL){
        addLinkedList(val, var, &shellVarHead, &shellVarTail);
    }else{
        replaceValue(tempReplace, val);
        return i;
    }
}

bool varNameCheck(char *var){
    int i = 0;
    if((var[i] >= 65 && var[i] <= 90) || (var[i] >= 97 && var[i] <= 122) || var[i] == 95){
        i++;
    }else{
        return false;
    }
    
    while(var[i] > 1){
        if((var[i] >= 65 && var[i] <= 90) || (var[i] >= 97 && var[i] <= 122) || var[i] == 95 || (var[i] >= 48 && var[i] <= 57)){
            i++;
        }else{
            return false;
        }
    }
    return true;
}

//deleteing characters
void deleteChar(char *input, int index){
    int i;
    for(i = index; input[i] > 1; i++){ // replaces the entry to be deleted with the one after it. repeats this till the end of the list
        input[i] = input[i+1];
    }
    input[i] = 0; // sents the last element to null
}

//partitons of a token by storing it in a char []
void partition(int start, int lenght, char *input, char command[]){
    for(int i = 0; i < COMMANDSIZE; i++){
        command[i] = 0; // initilizes placeholder to null
    }

    command[0] = *(input+start);
    for(int i = 1; i < lenght; i++){ // stors token in placholder
        command[i] = *(input+start+i);
    }
}

//
//commands
//

void cd(char *command, bool popd){
    node *replaceTemp;
    char *cwd;
    char s[100];


    if(command == NULL){
        printError("No variable was specified");
    }else{
        chdir(command);
        replaceTemp = searchByName(&shellVarHead, "CWD");
        cwd =  getcwd(s, 100);

        if(popd == false){
            pushDirToStack(cwd);
        }

        replaceValue(replaceTemp, cwd);
        char *prompt = getPROMPT(cwd);
        replaceTemp = searchByName(&shellVarHead, "PROMPT");
        replaceValue(replaceTemp, prompt);
    }
}

//if echo
void echo(node *temp, char* filename, int redirect){
    char line[COMMANDSIZE];
    if(filename != NULL){
        FILE *fp;
        fp = openingFile(filename, redirect);
        if(fp != NULL && redirect == 0){
            tokenizationFromFile(fp, line);
            output(fileInputHead, stdout, oneLineValues);
        }
        else if(fp != NULL && redirect > 0){
            output(temp->next, fp, oneLineValues);
        }
    }else{
        output(temp->next, stdout, oneLineValues);
    }
}




//if showvar or showenv
bool showLinkedList(node *temp, node *head, char* filename, int redirect){
    node *temp2;
    FILE *fp;
    if(filename != NULL){
        fp = openingFile(filename, redirect);
    }
    
    if(temp->next != NULL){
        temp2 = searchByName(&head, temp->next->value);
        if(temp2 == NULL){
                return false;
        }else if(temp2 != NULL){
            if(filename != NULL){
                if(fp != NULL){
                    output(temp2, fp, oneLineValues);
                }
            }else{
                printNameValue(temp2, stdout);
            }
        }
    }else{
        if(filename != NULL){
            if(fp != NULL){
                output(head, fp, lineValueName);
            }
        }else{
            printNameValues(head, stdout);
        }
    }
    return true;
}



void deleteVar(node *temp){
    if(temp != NULL){
        unsetenv(temp->value);
        deleteNode(&shellVarHead, temp->value);
    }else{
        printError("No variable was specified");
    }
}

//if export
void export(node *temp, char* filename, int redirect){
    node *temp2;
    if(filename != NULL){
        FILE *fp = openingFile(filename, redirect);
        if(redirect > 0){
            printError("This function does not give an output");
            return;
        }else{
            char line[COMMANDSIZE];
            tokenizationFromFile(fp, line);
            temp = fileInputHead;
        }
    }else{
        temp = temp->next;
    }

    if(temp != NULL){
        temp2 = searchByName(&shellVarHead, temp->value);
        if (temp2 != NULL){
            setenv(temp2->name, temp2->value, 1);
            
        }else{
            printError("The variable was not found");
        }
        
    }else{
        printError("No variable was specified");
    }
}

//if pushd
void pushd(node *temp, char *filename, int redirect){
    if(filename != NULL){
        if(redirect == 0){
            FILE *fp = openingFile(filename, redirect);
            char line[COMMANDSIZE];
            tokenizationFromFile(fp, line);
            temp = fileInputHead;
        }else{
            printError("This function dose not take give an output");
            return;
        }
    }else{
        temp = temp->next;
    }
    
    if(temp == NULL){
        printError("No Directory was specified");
    }else{
        pushDirToStack(temp->value);
    }
}


// pushing to the stack
void pushDirToStack(char *wd){
    DIR* dir = opendir(wd);
    if (dir) {
        node *newnode;

        newnode = createNewNode(wd, STACKNAME); // creats a new node with the value of wd
        insertNodeAtHead(&stackHead, newnode);
        cd(wd ,true);
        
        closedir(dir);
    } else if (ENOENT == errno) {
        printError("The Directory does not exist");
    } else {
        printError("The Directory failed to open");
    }
}

// poping from the stack
void popd(node **head, char *filename, int redirect){
    if(filename != NULL){
        if(redirect > 0){
            printError("This function dose give an output");
        }else{
            printError("This function dose not take an input");
        }
    }
    if((*head)->next != NULL){
        deleteNodeByValue(head, (*head)->value);
        cd((*head)->value, true);  // ..................
    }
}

//if source
bool source(node *temp, char *filename, int redirect){

    if(filename != NULL){
        if(redirect > 0){
            printError("This function dose give an output");
            return false;
        }else if(redirect == 0){
            FILE *fp = openingFile(filename, redirect);
            if(fp == NULL){
                return false;
            }
            char line[COMMANDSIZE];
            tokenizationFromFile(fp, line);
            temp = fileInputHead;
        }
    }else{
        temp = temp->next;
    }

    if(temp == NULL){
        printError("No file has been specified");
    }else {
        fileExecution(temp->value);
        
        return true;
    }
    return false;
}

//unset

void unset(node *temp, char* filename, int redirect){
    if(filename == NULL){
        if(temp == NULL){
            printError("No file name specified");
        }else{
            deleteVar(temp->next); 
        }
    }else{
        FILE *fp;
        fp = openingFile(filename, redirect);
        if(redirect > 0){
            printError("This command does not have an output");
        }else{
            char line[COMMANDSIZE];
            tokenizationFromFile(fp, line);
            deleteVar(fileInputHead);
        }
    }
    
}

void commandExecution(char command[]){
    destroy(&headCommand);
    tokenisation(command, &headCommand, &tailCommand);
    commands(headCommand);
}


void commands(node *head){
    node *temp = head;
    bool success;
    int redirectType = 0;
    int *redirectTypeP = &redirectType;
    char *file = checkForRedirect(temp, redirectTypeP);
    if(head != NULL){
        if(strcmp(temp->value, "cd") == 0){
        cd(temp->next->value, false);
            
        }
        else if(strcmp(temp->value, "echo") == 0){
            echo(temp, file, redirectType);
            
        }
        else if(strcmp(temp->value, "showvar") == 0){
            if(temp->next != NULL){
                success = showLinkedList(temp, shellVarHead, file, redirectType);
                if(!success){
                    printf("\033[31m");
                    printf("Variable [%s] was not found\n", temp->next->value);
                    printf("\033[00m");
                }
            }else{
                showLinkedList(temp, shellVarHead, file, redirectType);
            }
        }
        else if(strcmp(temp->value, "showenv") == 0){
            if(temp->next == NULL){
                printEnv(NULL, file, redirectType); //redirect input
            }else{
                success =printEnv(temp->next->value, file, redirectType);
                if(success == false){
                    printError("Variable not found");
                }
            }
        }
        else if(strcmp(temp->value, "export") == 0){
            export(temp, file, redirectType); 
            

        }
        else if(strcmp(temp->value, "unset") == 0){
            unset(temp, file, redirectType);

        }
        else if(strcmp(temp->value, "pushd") == 0){
            pushd(temp, file, redirectType); //redirect not working

        }
        else if(strcmp(temp->value, "popd") == 0){
            popd(&stackHead, file, redirectType);

        }
        else if(strcmp(temp->value, "source") == 0){
            success = source(temp, file, redirectType); // redirect output for terminals

        }
        else if(strcmp(temp->value, "dirs") == 0){
            dirs(file, redirectType);

        }
        else{
            if(redirectType == 3){
                piping(head);
            }else{
                fork_and_exec(temp);
            }
            
        }
    }
    
}

void dirs(char* filename, int redirect){
    if(filename != NULL){
        FILE *fp;
        fp = openingFile(filename, redirect);
        if(fp != NULL && redirect == 0){
            printError("This function does not take an input");
        }
        else if(fp != NULL && redirect > 0){
            output(stackHead, fp, lineValue);
        }
    }else{
        output(stackHead, stdout, lineValue);
    }
}


void printError(char *error){
    printf("\033[31m");
    printf("%s\n", error);
    printf("\033[00m");
}

void CWDPrompt(node * cwd){
    printf("\033[33m");
    printf("%s ", cwd->value);
    printf("\033[32m");

}

void output(node *temp, FILE *outputLocation, outputType convertionType){
    destroy(&outputHead);
    node *tail = NULL;

    while(temp != NULL){
        addLinkedList(temp->value, temp->name, &outputHead, &tail);
        temp = temp->next;
    }

    
    if(convertionType == 0){
        printValueInLine(outputHead, outputLocation);   
    }else if(convertionType == 1){
        printNameValues(outputHead, outputLocation);
    }else if(convertionType == 2){
        printValue(outputHead, outputLocation);
    }
    fprintf(outputLocation, "\n");
    if(outputLocation != stdout){
        fclose(outputLocation);
    }
        
    
}



char *checkForRedirect(node *head, int *redirectType){
    node *temp = head;
    char *ret;
    while(temp != NULL){
        if(strcmp(temp->value,"\"REDIRECTRIGHT\"") == 0){
            temp = temp->next;
            deleteNodeByValue(&head, "\"REDIRECTRIGHT\"");
            if(strcmp(temp->value,"\"REDIRECTRIGHT\"") == 0){
                *redirectType = 2;
                deleteNodeByValue(&head, "\"REDIRECTRIGHT\"");
                ret = temp->next->value;
                deleteNodeByValue(&head, ret);
                return ret;
            }
            *redirectType = 1;
            ret = temp->value;
            deleteNodeByValue(&head, ret);
            return ret;
        }else if(strcmp(temp->value,"\"REDIRECTLEFT\"") == 0){
            *redirectType = 0;
            temp = temp->next;
            ret = temp->value;
            // deleteNodeByValue(&head, "\"REDIRECTLEFT\"");
            // deleteNodeByValue(&head, ret);
            return ret;
        }else if(strcmp(temp->value,"\"PIPE\"") == 0){
            *redirectType = 3;
            temp = temp->next;
            ret = temp->value;
            return ret;
        }
        temp = temp->next;

    }
    return NULL;
}

bool printEnv(char* envName, char* filename, int redirect){
    FILE *fp;
    if(filename != NULL){
        fp = openingFile(filename, redirect);
        if(redirect = 0){
            
        }else{
            
        }
    }else{
        fp = stdout;
    }
    
    if(envName == NULL){
        for(char **env = environ; *env != NULL; env++){
            fprintf(fp, "%s\n", *env);
        }
    }else{
        char* val = getENV(envName);
        if(val == NULL){
            return false;
        }else{
            printf("%s = %s\n", envName, val);
        }
    }
    return true;
    
}





