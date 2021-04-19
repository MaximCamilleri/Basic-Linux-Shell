#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node{
    char *value;
    char *name;
    struct node* next;
}node;

node *createNewNode(char *value, char *name);
void insertNode(node *tail, node *newnode);
void printlist(node *head);
void destroy(node **head);
node *searchByValue(node **head, char *value);
node *searchByName(node **head, char *value);
void replaceValue(node *node, char *value);