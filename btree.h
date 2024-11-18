#ifndef BTREE_H
#define BTREE_H

#include "table.h"

typedef struct Node {
    Row data;
    struct Node* left;
    struct Node* right;
} Node;

void inser_good(Node** root, int value);

#endif
