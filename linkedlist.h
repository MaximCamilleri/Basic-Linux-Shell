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
void addLinkedList(char *value, char *name, node** head, node** tail);
void printNameValues(node *head, FILE *output);
void printNameValue(node *temp, FILE *output);
void deleteNode(node **head, char *value);
void insertNodeAtHead(node **head, node *newnode);
void printValue(node *head, FILE *output);
void deleteNodeByValue(node **head, char *value);
void freeNode(node* node);
void printValueInLine(node *head, FILE *output);
node* copyList(node* head);