#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef struct node {
    int data;
    node* next;
}node, * linklist;
linklist headinsert(linklist& L) {
    node * s;
    int x;
    L = (linklist)malloc(sizeof(node));
    L->next = NULL;
    scanf("%d", &x);
    while (x != 99999) {
        s = (node*)malloc(sizeof(node));
        s->data = x;
        s->next = L->next;
        L->next = s;
        scanf("%d", &x);
    }
    return L;
}


       






