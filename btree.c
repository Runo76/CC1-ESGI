#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

void inser_good(Node** root, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data.id = value;
    new_node->left = NULL;
    new_node->right = NULL;

    if (*root == NULL) {
        *root = new_node;
        return;
    }

    Node* current = *root;
    while (1) {
        if (value < current->data.id) {
            if (current->left == NULL) {
                current->left = new_node;
                return;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = new_node;
                return;
            }
            current = current->right;
        }
    }
}
