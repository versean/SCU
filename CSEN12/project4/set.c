/*
Sean Cajigal
set.c
November 9, 2025
Implementation of set of linked lists (used in conjunction w/ list.c).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"
#include "list.h"

typedef struct set {
    int count;
    int length;
    LIST **data;
    int (*compare)();
    unsigned (*hash)();
} SET;

/*
O(n/20) = O(n), creation of linked lists loop.
This function creates a set of linked lists.
*/

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    SET *sp;

    sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count = 0;
    sp->length = maxElts/20;
    sp->data = malloc(sizeof(LIST*)*sp->length);
    assert(sp->data!=NULL);

    sp->compare = compare;
    sp->hash = hash;

    for (int i = 0; i < sp->length; i++) {
        sp->data[i] = createList(sp->compare);
    }

    return sp;
};

/*
O(n/20) = O(n), deletion loop.
This function frees the set and all of the lists in it.
*/

void destroySet(SET *sp) {
    assert(sp!=NULL);

    for (int i = 0; i < sp->length; i++) {
        destroyList(sp->data[i]);
    }
    free(sp->data);
    free(sp);
};

/*
O(1), returns sp->count, which is a constant time operation.
This function returns the total number of elements.
*/

int numElements(SET *sp) {
    assert(sp!=NULL);
    return sp->count;
};

/*
O(n), findItem is linear time complexity.
This function adds an element to one of the linked lists in the set (based on hash value).
*/

void addElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL && sp->count < sp->length*20);

    int locn = (sp->hash)(elt) % sp->length;
    
    if (findItem(sp->data[locn],elt)==NULL) {
        addFirst(sp->data[locn],elt);
        sp->count++;
    }
};

/*
O(n), findItem is linear time complexity.
This function finds and removes an element from a specific linked list (based on hash value).
*/

void removeElement(SET *sp, void *elt) {
    assert(sp!=NULL && elt!=NULL);
    
    int locn = (sp->hash)(elt) % sp->length;
    
    if (findItem(sp->data[locn],elt)!=NULL) {
        removeItem(sp->data[locn],elt);
        sp->count--;
    }
};

/*
O(n), findItem is linearly searching the designated linked list.
This function finds an element from a specific linked list (based on hash value).
*/

void *findElement(SET *sp, void *elt) {
    assert(sp!=NULL && elt!=NULL);
    
    int locn = (sp->hash)(elt) % sp->length;
    void *data = findItem(sp->data[locn],elt);

    return data;
};

/*
O(n/20) loop * O(20) memcpy = O(n)
This function returns an array of memcopied elements in the set of linked lists.
*/

void *getElements(SET *sp) {
    assert(sp!=NULL);
    
    void **dest = malloc(sizeof(void*)*sp->count);
    assert(dest!=NULL);
    
    int index = 0;
    for (int i = 0; i < sp->length; i++) {
        int num = numItems(sp->data[i]); 
        void **items = getItems(sp->data[i]);
        
        memcpy(dest+index,items,sizeof(void*)*num);
        index+=num;
        free(items);
    }
    return dest;
};
