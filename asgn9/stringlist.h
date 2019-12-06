#ifndef STRINGLIST_H
#define STRINGLIST_H

typedef struct node {
    char* data;
    struct node* next;
} node;

int addName(node**, char*);
int removeName(node**, char*);
void createNode(node**, char*);
void printList(node**);
void deleteList(node**);

#endif
