/*
Sean Cajigal
unsorted.c
October 9, 2025
An implementation of the set.h interface that allows for creation and manipulation of unsorted sets.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "set.h"

typedef struct set {
    int count;
    int length;
    char **data;
} SET;

/*
Private function for sequential/linear element search.
O(n)
*/

static int search(SET *sp, int n, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    for (int i = 0; i < n; i++) {
        if (strcmp(elt, sp->data[i]) == 0) {
            return i;
        }
    }
    return -1;
};

/*
Creates a set of size maxElts to contain an array of strings.
O(1)
*/ 

SET *createSet(int maxElts) {
    SET *sp;

    sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data!=NULL);
    
    return sp;
};

/*
Destroys the set and frees up the space in memory.
O(n)
*/ 

void destroySet(SET *sp) {
    assert(sp!=NULL);
    for (int i = 0; i < sp->count; i++) {
        free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
};

/*
Returns the number of elements inside set.
O(1)
*/ 

int numElements(SET *sp) {
    assert(sp!=NULL);
    return sp->count;
};

/*
Adds a unique element to the set.
O(n)
*/ 

void addElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    if (sp->count > sp->length - 1)
        return;
    if (search(sp,sp->count,elt) == -1) {
        char *dest = strdup(elt);
        assert(dest!=NULL);
        sp->data[sp->count] = dest;
        sp->count++;
    }
};

/*
Removes an element from the set.
O(n) <-- O(n) from the search
*/ 

void removeElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    int index = search(sp, sp->count, elt);
    if (index != -1) {
        free(sp->data[index]);
        sp->count--;
        sp->data[index] = sp->data[sp->count];
    }
};

/*
Searches for element, mainly using the private search function.
O(n) <-- O(n) from the search
*/ 

char *findElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    int index = search(sp,sp->count,elt);
    if (index==-1) {
        return NULL;
    } else {
        return sp->data[index];
    }
};

/* 
Returns a pointer to a duplicated array of strings.
O(n) <-- O(n) from memcpy
*/ 

char **getElements(SET *sp) {
    assert(sp!=NULL);
    char **dest;
    dest = malloc(sizeof(char*) * sp->count);
    assert(dest!=NULL);
    memcpy(dest, sp->data, sizeof(char*) * sp->count);
    return dest;
};