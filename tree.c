#include "tree.h"
#include <stdlib.h>
#include <string.h>

// Insert a student into the tree
TreeNode* insert_tree(TreeNode* root, Student student) {
    if (root == NULL) {
        TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
        new_node->data = student;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }

    if (student.id < root->data.id) {
        root->left = insert_tree(root->left, student);
    } else if (student.id > root->data.id) {
        root->right = insert_tree(root->right, student);
    }

    return root;
}

// Search for a student by ID
TreeNode* search_tree(TreeNode* root, int id) {
    if (root == NULL || root->data.id == id) {
        return root;
    }

    if (id < root->data.id) {
        return search_tree(root->left, id);
    } else {
        return search_tree(root->right, id);
    }
}

// Find the minimum value in the tree
TreeNode* find_min(TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Delete a student by ID
TreeNode* delete_tree(TreeNode* root, int id) {
    if (root == NULL) {
        return NULL;
    }

    if (id < root->data.id) {
        root->left = delete_tree(root->left, id);
    } else if (id > root->data.id) {
        root->right = delete_tree(root->right, id);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        TreeNode* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_tree(root->right, temp->data.id);
    }

    return root;
}

// Inorder traversal (sorted)
void inorder_traversal(TreeNode* root) {
    if (root == NULL) return;

    inorder_traversal(root->left);
    printf("ID: %d, Name: %s, Grade: %.2f\n", root->data.id, root->data.name, root->data.grade);
    inorder_traversal(root->right);
}

// Save tree to file
void save_tree_to_file(TreeNode* root, FILE* file) {
    if (root == NULL) return;

    save_tree_to_file(root->left, file);
    fprintf(file, "%d,%s,%.2f\n", root->data.id, root->data.name, root->data.grade);
    save_tree_to_file(root->right, file);
}

// Load tree from file
void load_tree_from_file(TreeNode** root, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("No database file found. Starting with an empty database.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Student student;
        sscanf(line, "%d,%49[^,],%f", &student.id, student.name, &student.grade);
        *root = insert_tree(*root, student);
    }

    fclose(file);
}
