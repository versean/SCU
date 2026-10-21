/*
Sean Cajigal
sorted.c
October 9, 2025
An implementation of the set.h interface that allows for creation and manipulation of sorted sets.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

typedef struct set {
    int count;
    int length;
    char **data;
} SET;

/*
Private function for binary element search.
O(logn) because it's a binary search
*/ 

static int search(SET *sp, char *elt, bool *found) {
    assert(sp!=NULL&&elt!=NULL&&found!=NULL);
    int low=0, high=sp->count-1;
    while (low<=high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(sp->data[mid],elt);
        if (cmp==0) {
            *found = true;
            return mid;
        } else if (cmp > 0) {
            high = mid-1;
        } else {
            low = mid+1;
        }
    }
    *found = false;
    return low;
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
O(n) <-- O(logn) from the binary search + O(n) from the shifting
*/ 

void addElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    if (sp->count > sp->length - 1)
        return;

    bool found;
    int index = search(sp, elt, &found);
    if (found == false) {
        for (int i = sp->count; i > index; i--) {
            sp->data[i] = sp->data[i-1];
        }
        char *dest = strdup(elt);
        assert(dest!=NULL);
        sp->data[index] = dest;
        
        sp->count++;
    }
};

/*
Removes an element from the set.
O(n) <-- O(logn) from the binary search + O(n) from the shifting
*/ 

void removeElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);

    bool found;
    int index = search(sp, elt, &found);
    if (found == true) {
        free(sp->data[index]);
        for (int i = index; i < sp->count; i++) {
            sp->data[i] = sp->data[i+1];
        }
        sp->count--;
        sp->data[sp->count] = NULL;
    }
};

/*
Searches for element, mainly using the private binary search function.
O(logn) <-- O(logn) from the binary search
*/ 

char *findElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int index = search(sp, elt, &found);
    return found ? sp->data[index] : NULL;
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