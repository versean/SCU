/*
Sean Cajigal
list.c
November 9, 2025
Impletmentation of a linked list.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

typedef struct list {
    int count;
    struct node *head;
    int (*compare)();
} LIST;

typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} NODE;

/*
O(1), simple operations, no loops involved.
This function creates a list filled with a dummy node by default, which doesn't count towards the total number of nodes.
*/

LIST *createList(int (*compare)())
{
    LIST *lp;
    lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->compare = compare;
    lp->head = malloc(sizeof(NODE));
    assert(lp->head != NULL);
    lp->head->data = NULL;
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    return lp;
};

/*
O(n), going through each node to individually free requires linear time complexity.
This function destroys a list by freeing each node then freeing the overall list.
*/

void destroyList(LIST *lp) {
    assert(lp!=NULL);

    NODE *current;
    NODE *next;
    current = lp->head->next;
    while (current != lp->head) { 
        next = current->next;
        free(current);
        current = next;
    }
    free(lp->head);
    free(lp);
};

/*
O(1), simple operations, no loops involved.
This function returns the number of elements in a linked list.
*/

int numItems(LIST *lp) {
    assert(lp!=NULL);
    return lp->count;
};

/*
O(1), simple operations, no loops involved.
This function adds a node to the front of a linked list.
*/

void addFirst(LIST *lp, void *item) {
    assert(lp!=NULL&&item!=NULL);
    NODE *new = malloc(sizeof(NODE));
    new->data = item;

    new->prev = lp->head;
    new->next = lp->head->next;

    new->prev->next = new;
    new->next->prev = new;

    lp->count++;
};

/*
O(1), simple operations, no loops involved.
This function adds a node to the back of a linked list.
*/

void addLast(LIST *lp, void *item) {
    assert(lp!=NULL&&item!=NULL);
    NODE *new = malloc(sizeof(NODE));
    new->data = item;

    new->prev = lp->head->prev;
    new->next = lp->head;

    new->prev->next = new;
    new->next->prev = new;

    lp->count++;
};

/*
O(1), simple operations, no loops involved.
This function removes the node at the front of a linked list.
*/

void *removeFirst(LIST *lp) {
    assert(lp!=NULL&&lp->count>0);

    NODE *del = lp->head->next;
    void *data = del->data;

    lp->head->next = del->next;
    del->next->prev = lp->head;
    free(del);

    lp->count--;
    return data;
};

/*
O(1), simple operations, no loops involved.
This function removes the node at the back of a linked list.
*/

void *removeLast(LIST *lp) {
    assert(lp!=NULL&&lp->count>0);

    NODE *del = lp->head->prev;
    void *data = del->data;

    lp->head->prev = del->prev;
    del->prev->next = lp->head;
    free(del);

    lp->count--;
    return data;
};

/*
O(1), simply returning data, no loops involved.
This function returns the dummy node's next's data.
*/

void *getFirst(LIST *lp) {
    assert(lp!=NULL&&lp->count>0);
    return lp->head->next->data;
};

/*
O(1), simply returning data, no loops involved.
This function returns the dummy node's previous' data.
*/

void *getLast(LIST *lp) {
    assert(lp!=NULL&&lp->count>0);
    return lp->head->prev->data;
};

/*
O(n), linearly searching through the linked list.
This function searches for an item in the linked list and deletes it.
*/

void removeItem(LIST *lp, void *item) {
    assert(lp!=NULL&&item!=NULL);

    NODE *current = lp->head->next;
    while (current!=lp->head) {
        if ((lp->compare)(current->data,item) == 0) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            lp->count--;
            break;
        }
        current=current->next;
    }
};

/*
O(n), linearly searching through linked list.
This function searches for an item in the linked list.
*/

void *findItem(LIST *lp, void *item) {
    assert(lp!=NULL&&item!=NULL);

    NODE *current = lp->head->next;
    while (current!=lp->head) {
        if ((lp->compare)(current->data,item) == 0) {
            return current->data;
        }
        current = current->next;
    }
    return NULL;
};

/*
O(n), linearly goes through linked list.
This function returns an array of elements in the linked list.
*/
void *getItems(LIST *lp) {
    assert(lp!=NULL);

    void **items = malloc(sizeof(void*)*lp->count);
    assert(items!=NULL);

    NODE *current = lp->head->next;
    int index = 0;
    while (current!=lp->head) {
        items[index]=current->data;
        current = current->next;
        index++;
    }
    return items;
};