#include "variables.c"


void insertNodeAtHead(node **head, node *newnode){
    node *temp = *head;
    *head = newnode;
    (*head)->next = temp;
}






