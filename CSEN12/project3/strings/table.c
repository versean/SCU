/*
Sean Cajigal
table.c
October 16, 2025
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
    char **data;
    char *flags;
} SET;

// O(n), the number of operations varies directly with the length of the string.
// Converts the string (key) into an index
unsigned strhash(char *s)
{
    unsigned hash = 0;
    while (*s != '\0')
        hash = 31 * hash + *s ++;
    return hash;
}

// Searches a hash table
// O(n) due to linear probing because of possible collisions
static int search(SET *sp, char *elt, bool *found) {
    assert(sp!=NULL&&elt!=NULL&&found!=NULL);

    unsigned hash = strhash(elt);
    int index = hash % sp->length;
    int firstFillable = -1;
    for (int probe = 0; probe < sp->length; probe++) {
        if (sp->flags[index] == 'E') break;
        index = (hash + probe) % sp->length;
        if (firstFillable == -1 && sp->flags[index] == 'D') {
            
            firstFillable = index;
        }
        
        if (sp->data[index] != NULL && strcmp(sp->data[index],elt) == 0) {
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
SET *createSet(int maxElts) {
    SET *sp;

    sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data!=NULL);
    sp->flags = malloc(sizeof(char)*maxElts);
    assert(sp->flags!=NULL);

    for (int i = 0; i < sp->length; i++) {
        sp->flags[i] = 'E';
    }

    return sp;
};

// Destroys a set
// O(n) due to the for loop freeing each element inside sp->data
void destroySet(SET *sp) {
    assert(sp!=NULL);

    for (int i = 0; i < sp->count; i++) {
        free(sp->data[i]);
    }
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
void addElement(SET *sp, char *elt) {
    assert(sp != NULL && elt != NULL && sp->count < sp->length);

    bool found;
    int locn;
    char *copy;
    locn = search(sp, elt, &found);
    if (!found) {
        
        copy = strdup(elt);
        assert(copy != NULL);
        sp->data[locn] = copy;
        sp->flags[locn] = 'F';
        sp->count++;
    }
};

// Removes an element to the set
// generally O(1) to remove an element, but worst case, it's O(n) due to linear probing (searching subsequent elements until empty index)
void removeElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    
    bool found;
    int locn;
    locn = search(sp, elt, &found);
    if (found) {
        free(sp->data[locn]);
        sp->count--;
        sp->data[locn] = NULL;
        sp->flags[locn] = 'D';
    }
};

// Finds an element in the set
// generally O(1) to find an element, but worst case, it's O(n) due to linear probing (searching subsequent elements until empty index)
char *findElement(SET *sp, char *elt) {
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
char **getElements(SET *sp) {
    assert(sp!=NULL);

    char **dest;
    dest = malloc(sizeof(char*) * sp->count);
    assert(dest!=NULL);
    int count = 0;
    for (int i = 0; i < sp->length; i++) {
        if (sp->flags[i] == 'F') {
            char *copy = strdup(sp->data[i]);
            assert(copy!=NULL);
            dest[count] = copy; 
            count++;
        }
    }
    return dest;
};
