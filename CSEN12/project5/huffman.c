/*
Sean Cajigal
huffman.c
November 22, 2025
Implementation of huffman trees.
*/

#include "pack.h"
#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"
#include <ctype.h>
#include <assert.h>

/*
Special private function used to make a new node with parent and count attributes.
*/

static struct node *mknode(int count, struct node *left_node, struct node *right_node) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->count = count;
    new_node->parent =  NULL;
    if (left_node!=NULL) left_node->parent=new_node;
    if (right_node!=NULL) right_node->parent=new_node;
    return new_node;
}

/*
Private function used to calculate the depth of a specified node.
*/

static int depth(struct node *n) {
    assert(n!=NULL);
    struct node *node = n;
    int count = 0;
    while (node->parent!=NULL) {
        node = node->parent;
        count++;
    }
    return count;
}

/*
Comparison function used by the priority queue.
*/

static int cmp(struct node *t1, struct node *t2) {
    return (t1->count < t2->count) ? -1 : (t1->count > t2->count);
}

int main (int argc, char *argv[]) {
    // argument handling
    if (argc!=3) {
        printf("Wrong number of arguments! Correct syntax: ./huffman <input_file_name> <output_file_name>\n");
        return 0;
    }
    char *input_file_name = argv[1];
    char *output_file_name = argv[2];

    // creating arrays
    int counts[257] = {0};
    struct node **nodes = malloc(sizeof(struct node*)*257);
    assert(nodes!=NULL);

    // file opening and counting character frequency
    FILE* fp = fopen(argv[1], "r");
    assert(fp!=NULL);
    char ch;
    while ((ch = getc(fp)) != EOF) {
        counts[(int)ch]++;
    }

    // setting-up arrays
    PQ *pq = createQueue(cmp);
    assert(pq!=NULL);
    for (int i = 0; i < 256; i++) {
        if (counts[i] > 0) {
            nodes[i] = mknode(counts[i], NULL, NULL);
            addEntry(pq, nodes[i]);
        }
    }
    nodes[256] = mknode(0, NULL, NULL); // EOL
    addEntry(pq, nodes[256]);
    
    // building up the huffman tree by combining two nodes repeatedly
    while (numEntries(pq) > 1) {
        struct node *node2 = removeEntry(pq);
        struct node *node1 = removeEntry(pq);
        struct node *new_node = mknode(node1->count + node2->count, node1, node2);
        addEntry(pq, new_node);
    }

    // printing how many occurances and bits for each used character
    for (int c = 0; c < 257; c++) {
        if (counts[c] > 0 || c == 256) {
            if (!isprint(c)) {
                printf("%03o: ",c);
            } else {
                printf("'%c': ",(char)c);
            }
            printf("%d x %d bits = %d bits\n", counts[c], depth(nodes[c]), counts[c] * depth(nodes[c]));
        }
        
    }

    // generates the compressed file, also prints # of required bits.
    pack(input_file_name, output_file_name, nodes);

    // don't want memory leaks! freeing up malloc'ed stuff here
    for (int i = 0; i < 257; i++) {
        free(nodes[i]);
    }
    free(nodes);
    destroyQueue(pq);
    fclose(fp);
    
    return 0;
}