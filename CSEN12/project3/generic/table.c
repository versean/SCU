/*
Sean Cajigal
table.c
October 23, 2025
Implementing sets with hash tables.
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
    void **data;
    char *flags;
    int (*compare)();
    unsigned (*hash)();
} SET;

// Searches a hash table
// O(n) due to linear probing because of possible collisions
static int search(SET *sp, void *elt, bool *found) {
    assert(sp!=NULL&&elt!=NULL&&found!=NULL);

    unsigned hash = (sp->hash)(elt);
    int index = hash % sp->length;
    int firstFillable = -1;
    for (int probe = 0; probe < sp->length; probe++) {
        if (sp->flags[index] == 'E') break;
        index = (hash + probe) % sp->length;
        if (firstFillable == -1 && sp->flags[index] == 'D') {
            
            firstFillable = index;
        }
        
        if (sp->data[index] != NULL && (*sp->compare)(sp->data[index],elt) == 0) {
            *found = true;
            
            return index;
        }
    }
    if (firstFillable == -1) {
        firstFillable = index;
    }

    *found = false;
    return firstFillable;
};

// Creates a set
// O(n) due to filling the flags array with 'E'mpty flags
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    SET *sp;

    sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(void*)*maxElts);
    assert(sp->data!=NULL);
    sp->flags = malloc(sizeof(char)*maxElts);
    assert(sp->flags!=NULL);

    sp->compare = compare;
    sp->hash = hash;

    for (int i = 0; i < sp->length; i++) {
        sp->flags[i] = 'E';
    }

    return sp;
};

// Destroys a set
// O(1), data freeing is handled by user, so no looping (linear-time) through data 
void destroySet(SET *sp) {
    assert(sp!=NULL);

    free(sp->data);
    free(sp->flags);
    free(sp);
};

// Returns the number of elements in a set
// O(1), fetches the value of sp->count, no loops needed
int numElements(SET *sp) {
    assert(sp!=NULL);
    return sp->count;
};

// Adds an element to the set
// generally O(1) to add an element, but worst case, it's O(n) due to linear probing because of possible collisions
void addElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL && sp->count < sp->length);

    bool found;
    int locn;
    
    locn = search(sp, elt, &found);
    if (!found) {
        sp->data[locn] = elt;
        sp->flags[locn] = 'F';
        sp->count++;
    }
};

// Removes an element to the set
// generally O(1) to remove an element, but worst case, it's O(n) due to linear probing (searching subsequent elements until empty index)
void removeElement(SET *sp, void *elt) {
    assert(sp!=NULL && elt!=NULL);
    
    bool found;
    int locn;
    locn = search(sp, elt, &found);
    if (found) {
        sp->count--;
        sp->data[locn] = NULL;
        sp->flags[locn] = 'D';
    }
};

// Finds an element in the set
// generally O(1) to find an element, but worst case, it's O(n) due to linear probing (searching subsequent elements until empty index)
void *findElement(SET *sp, void *elt) {
    assert(sp!=NULL && elt!=NULL);

    bool found;
    int index = search(sp,elt,&found);
    if (found) {
        return sp->data[index];
    } else {
        return NULL;
    }
};

// Returns a hard copy of the set
// O(n) to linearly go through each filled (F flag) element in the set and add it to a new destination array
void *getElements(SET *sp) {
    assert(sp!=NULL);

    void **dest;
    dest = malloc(sizeof(void*) * sp->count);
    assert(dest!=NULL);
    int count = 0;
    for (int i = 0; i < sp->length; i++) {
        if (sp->flags[i] == 'F') {
            void *copy = malloc(sizeof(void));
            memcpy(copy, sp->data[i], sizeof(void));
            dest[count] = sp->data[i]; 
            count++;
        }
    }
    return dest;
};
