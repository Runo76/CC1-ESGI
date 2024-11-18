#include <stdio.h>
#include "repl.h"
#include "btree.h"

int main(int argc, char* argv[], char* envp[]) {
    // Initialize the root of the binary tree
    Node* root = NULL;

    // Insert an example value into the tree
    inser_good(&root, 17);

    // Start the REPL loop
    repl();

    return 0;
}
