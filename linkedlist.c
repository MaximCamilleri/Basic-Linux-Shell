#include "linkedlist.h"

node* createNewNode(char *value, char *name){
    node *result = malloc(sizeof(node));
    result->value = malloc(strlen(value) + 1);
    result->name = malloc(strlen(name) + 1);
    strcpy(result->value, value);
    strcpy(result->name, name);
    result->next = NULL;
    return result;
}

void insertNode(node *tail, node *newnode){
    tail->next = newnode;
}

void printlist(node *head){
    node *temporary = head;

    while(temporary != NULL){
        printf("%s - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

void printNameValues(node *head, FILE *output){
    node *temp = head;
    while(temp != NULL){
        printNameValue(temp, output);
        temp = temp->next;
    }
}

void printValue(node *head, FILE *output){
    node *temp = head;
    while(temp != NULL){
        fprintf(output, "%s\n", temp->value);
        temp = temp->next;
    }
}

void printValueInLine(node *head, FILE *output){
    node *temp = head;
    while(temp != NULL){
        fprintf(output, "%s ", temp->value);
        temp = temp->next;
    }
}

void printNameValue(node *temp, FILE *output){
    fprintf(output, "%s = %s\n", temp->name, temp->value);
}

void destroy(node **head){
    node *temp = *head;
    node *next;

    while (temp != NULL)
    {
       next = temp->next;
       freeNode(temp);
       temp = next;
    }
    *head = NULL;
}

node* searchByValue(node **head, char *value){
    node *temp = *head;

    while(temp != NULL){
        if(strcmp(temp->value, value) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}

node* searchByName(node **head, char *name){
    node *temp = *head;

    while(temp != NULL){
        if(strcmp(temp->name, name) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}

void replaceValue(node *node, char *value){
    free(node->value);
    node->value = malloc(strlen(value)+1);
    strcpy(node->value, value);
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
    //freeNode(temp);
}

void deleteNode(node **head, char *value){
    node *temp = *head;
    node *prev = NULL;
    while(temp != NULL){
        if(strcmp(temp->name, value) == 0){
            if(temp == *head){
                if(temp->next == NULL){
                    *head = NULL;
                }else{
                    *head = temp->next;
                }
            }else{
                prev->next = temp->next;
            }
        }
        prev = temp;
        temp = temp->next;
    }
}

void deleteNodeByValue(node **head, char *value){
    node *temp = *head;
    node *prev = NULL;
    while(temp != NULL){
        if(strcmp(temp->value, value) == 0){
            if(temp == *head){
                if(temp->next == NULL){
                    *head = NULL;
                    break;
                }else{
                    *head = (*head)->next;
                    break;
                }
            }else{
                prev->next = temp->next;
                break;
            }
        }
        prev = temp;
        temp = temp->next;
    }
}

void freeNode(node* node){
    free(node->name);
    free(node->value);
    free(node);
}

node* copyList(node* head)
{
    if (head == NULL) {
        return NULL;
    }
    else {
  
        // Allocate the memory for new Node
        // in the heap and set its data
        node* newNode = malloc(sizeof(node));
  
        newNode->value = head->value;
        newNode->name = head->name;
  
        // Recursively set the next pointer of
        // the new Node by recurring for the
        // remaining nodes
        newNode->next = copyList(head->next);
  
        return newNode;
    }
}

