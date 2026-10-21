/*
 * File:        list.c
 *
 * Copyright:	December 5 2025, Sean C. Cajigal
 *
 * Description: Implementation of a linked list of nodes, which each have
 *              an array to store data, dubbed the "Loony List." (apparently)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

typedef struct list {
    int count;          // total amount of elements across all nodes' arrays
    struct node *head;  // head node (a dummy node)
} LIST;

typedef struct node {
    int count;          // number of elements in node's array
    int size;           // size of node's array (# of elements it can hold, not in bytes, arbitrary)
    int first;          // index of first element node's array (array is treated like a circular queue)
    void **data;        // the node's array itself
    struct node *next;  // proceeding node 
    struct node *prev;  // preceding node
} NODE;


/*
 * Function:    createList
 *
 * Complexity:  O(1)
 *
 * Description: Return a pointer to a new list and also creates
 *              a default array for the default node.
 */

LIST *createList() {
    LIST *lp;
    lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->head = malloc(sizeof(NODE));
    assert(lp->head != NULL);
    
    lp->head->count = 0;
    lp->head->size = 0;
    lp->head->first = 0;
    lp->head->data = NULL;

    NODE *node = malloc(sizeof(NODE));
    assert(node != NULL);

    lp->head->prev = node;
    lp->head->next = node;

    node->prev = lp->head;
    node->next = lp->head;

    node->data = malloc(sizeof(void*)*16);
    assert(node->data != NULL);
    node->size = 16;
    //printf("Default node size %d\n",node->size); for demo
    node->count = 0;
    node->first = 0;
    
    return lp;
}


/*
 * Function:    destroyList
 *
 * Complexity:  O(k), where k is the number of nodes
 *
 * Description: Deallocates each node, then deallocates
 *              the linked list itself. Deallocation of
 *              the data is handled by the user.
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
}


/*
 * Function:    numItems
 *
 * Complexity:  O(1)
 *
 * Description: Returns the number of total amount
 *              of elts (not nodes, but data),
 *              since lp->count keeps track of #
 *              of elts across nodes.
 */

int numItems(LIST *lp) {
    assert(lp!=NULL);
    return lp->count;
}


/*
 * Function:    addLast
 *
 * Complexity:  O(1), average case, O(n) worst case
 *
 * Description: Adds an element to the end of the last node's array.
 *              Worst case, it has to create a new node with double
 *              the last array size.
 */

void addLast(LIST *lp, void *item) {
    assert(lp!=NULL&&item!=NULL);

    NODE *node = lp->head->prev;
    if (node->count >= node->size) {
        NODE *new = malloc(sizeof(NODE));
        new->data = malloc(sizeof(void*)*node->size*2);
        assert(new!=NULL&&new->data!=NULL);
        new->size = node->size*2;
        //printf("New node size %d\n", new->size); for demo
        new->count = 0;
        new->first = 0;

        new->prev = node;
        new->next = lp->head;

        node->next = new;
        lp->head->prev = new;

        new->data[0] = item;
        new->count++;
    } else {
        node->data[(node->first+node->count)%node->size] = item;
        node->count++;
    }

    lp->count++;
}


/*
 * Function:    removeFirst
 *
 * Complexity:  O(1)
 *
 * Description: Removes the element at the front of the
 *              first node's circular queue. If the first
 *              node is empty, it deallocates that first,
 *              then sets the next node as the new first
 *              node. Returns removed data.
 */

void *removeFirst(LIST *lp) {
    assert(lp!=NULL&&lp->count>0);

    NODE *node = lp->head->next;
    assert(lp->head!=lp->head->next);

    if (node->count<=0 && node->next!=lp->head) {
        lp->head->next = node->next;
        node->next->prev = lp->head;

        free(node->data);
        free(node);

        node = lp->head->next;
    }
    void *data = node->data[node->first];
    node->data[node->first] = NULL;
    node->first = (node->first+1)%node->size;
    node->count--;
    lp->count--;

    return data;
}


/*
 * Function:    addFirst
 *
 * Complexity:  O(1), average case, O(n) worst case
 *
 * Description: Adds an element to the front of the first node's array.
 *              Worst case, it has to create a new node with double
 *              the last array size.
 */

void addFirst(LIST *lp, void *item) {
    assert(lp!=NULL&&item!=NULL);

    NODE *node = lp->head->next;
    if (node->count >= node->size) {
        NODE *new = malloc(sizeof(NODE));
        new->data = malloc(sizeof(void*)*node->size*2);
        assert(new!=NULL&&new->data!=NULL);
        new->size = node->size*2;
        //printf("New node size %d\n", new->size); for demo
        new->count = 0;
        new->first = 0;

        new->prev = lp->head;
        new->next = node;

        lp->head->next = new;
        node->prev = new;

        new->data[0] = item;
        new->count++;
    } else {
        node->first--;
        if (node->first < 0) node->first = node->size-1; 
        
        node->data[node->first] = item;
        node->count++;
    }

    lp->count++;
}


/*
 * Function:    removeLast
 *
 * Complexity:  O(1)
 *
 * Description: Removes the element at the end of the
 *              last node's circular queue. If the last
 *              node is empty, it deallocates that first,
 *              then sets the prev node as the new last
 *              node. Returns removed data.
 */

void *removeLast(LIST *lp) {
    assert(lp!=NULL&&lp->count>0);

    NODE *node = lp->head->prev;
    assert(lp->head!=lp->head->next);

    if (node->count<=0) {
        lp->head->prev = node->prev;
        node->prev->next = lp->head;
        
        free(node->data);
        free(node);

        node = lp->head->prev;
    }

    int last = (node->first+node->count-1)%node->size;
    void *data = node->data[last];
    node->data[last] = NULL;
    node->count--;
    lp->count--;
    return data;
}


/*
 * Function:    getFirst
 *
 * Complexity:  O(1)
 *
 * Description: Returns the data that's at the front of
 *              the first node's array (not including
 *              dummy node).
 */

void *getFirst(LIST *lp) {
    assert(lp!=NULL&&lp->count>0);
    NODE *node = lp->head->next;
    return node->data[node->first];
}


/*
 * Function:    getLast
 *
 * Complexity:  O(1)
 *
 * Description: Returns the data that's at the end of
 *              the last node's array (not including
 *              dummy node).
 */

void *getLast(LIST *lp) {
    assert(lp!=NULL&&lp->count>0);
    NODE *node = lp->head->prev;
    return node->data[(node->first+node->count-1)%node->size];
}


/*
 * Function:    getItem
 *
 * Complexity:  O(log n)
 *
 * Description: Returns the element at that index. Index is treated
 *              as if all of the nodes' arrays were combined into
 *              one large array.
 */

void *getItem(LIST *lp, int index) {
    assert(lp!=NULL&&index<lp->count);

    NODE *node = lp->head->next;
    int total = index;
    while (node->count - 1 < total) {
        total-=node->count;
        node=node->next;
        
    }
    return node->data[total];
}


/*
 * Function:    setItem
 *
 * Complexity:  O(log n)
 *
 * Description: Finds the place in one of the nodes' arrays for
 *              the given index and sets it to an input item.
 *              Index is treated as if all of the nodes' arrays
 *              were combined into one large array.
 */

void setItem(LIST *lp, int index, void *item) {
    assert(lp!=NULL&&item!=NULL&&index<lp->count);

    NODE *node = lp->head->next;
    int total = index;
    while (node->count - 1 < total) {
        total-=node->count;
        node=node->next;
        
    }

    node->data[total] = item;
}