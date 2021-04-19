#include "linkedlist.h"

node *createNewNode(char *value, char *name){
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
        fflush(stdout);
        temporary = temporary->next;
    }
    printf("\n");
}

void destroy(node **head){
    node *temp = *head;
    node *next;

    while (temp != NULL)
    {
       next = temp->next;
       free(temp);
       temp = next;
    }
    *head = NULL;
}

node* searchByValue(node **head, char *value){
    node *temp = *head;

    while(temp != NULL){
        if(strcmp(temp->value, value)){
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}

node* searchByName(node **head, char *name){
    node *temp = *head;

    while(temp != NULL){
        if(strcmp(temp->name, name)){
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