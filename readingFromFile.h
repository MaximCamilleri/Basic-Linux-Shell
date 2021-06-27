bool fileExecution(const char *filename);
FILE *openingFile(const char *filename, int read);

node *headCommand = NULL; // start of the linked list
node *tailCommand = NULL; // end of the linked list
void commandExecution(char command[]);
void initialize(char line[], size_t size);
FILE *initializeFile(char* filename, int redirect);
void printError(char *error);
void tokenisation(char *input, node **headTemp, node **tailTemp);
void tokenizationFromFile(FILE *fp, char line[]);