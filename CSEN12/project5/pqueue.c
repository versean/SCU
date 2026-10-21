/*
Sean Cajigal
pqueue.c
November 22, 2025
Implementation of priority queues (min-heap).
*/

// For time complexity descriptions, n = number of elements in priority queue

#include <stdlib.h>
#include <assert.h>
# include <stdio.h>

typedef struct pqueue {
    int count;
    int length;
    void **data;
    int (*compare)();
} PQ;

/*
Creates a priority queue.
O(1), simple operations, malloc considered O(1) here.
*/

PQ *createQueue(int (*compare)()) {
    assert(compare!=NULL);

    PQ *pq;
    pq = malloc(sizeof(PQ));
    assert(pq!=NULL);
    pq->count = 0;
    pq->length = 10;
    pq->data = malloc(sizeof(void*)*pq->length);
    assert(pq->data!=NULL);
    pq->compare = compare;

    return pq;
};

/*
Destroys a priority queue.
O(1), simple operations, free considered O(1) here.
*/

void destroyQueue(PQ *pq) {
    assert(pq!=NULL);
    free(pq->data);
    free(pq);
};

/*
Returns the number of elements inside a priority queue.
O(1), simply returning a value, no complex operations.
*/

int numEntries(PQ *pq) {
    assert(pq!=NULL);
    return pq->count;
};

/*
Adds an element to a priority queue.
AVERAGE: adding an element to a min-heap is usually O(log n) to heap up
WORST: realloc is a O(n) process, doesn't have to reallocate every time though
*/

void addEntry(PQ *pq, void *entry) {
    assert(pq!=NULL&&entry!=NULL);
    if (pq->count >= pq->length) {
        pq->length*=2;
        pq->data = realloc(pq->data, sizeof(void*)*pq->length);
        assert(pq->data!=NULL);
    }
    
    int x = pq->count;
    while (x > 0 && (pq->compare)(entry,pq->data[(x-1)/2]) < 0) {
        pq->data[x] = pq->data[(x-1)/2]; 
        x = (x-1)/2;
    }
    pq->data[x] = entry;
    pq->count++;
};

/*
Removes the element next in line in a priority queue.
O(log n), removing an element from a min-heap does heap down which goes through log(n) elements. 
*/

void *removeEntry(PQ *pq) {
    assert(pq!=NULL && pq->count > 0);

    void *root = pq->data[0];
    
    pq->count--;

    int x = 0;
    while (x*2+1<pq->count) {
        int smallest;
        if (x*2+2<pq->count && (*pq->compare)(pq->data[x*2+2],pq->data[x*2+1]) < 0) {
            smallest = x*2+2;
        } else {
            smallest = x*2+1;
        }

        if ((*pq->compare)(pq->data[smallest],pq->data[pq->count]) < 0) {
            pq->data[x] = pq->data[smallest];
            x=smallest;
        } else {
            break;
        }
    }
    pq->data[x] = pq->data[pq->count];
    
    return root;
};