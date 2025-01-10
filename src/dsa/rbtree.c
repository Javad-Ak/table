#include "rbtree.h"

// Function to create a new node
RBTreeNode* tree_createNode(int key) {
    RBTreeNode *newNode = (RBTreeNode*)malloc(sizeof(RBTreeNode));
    newNode->key = key;
    newNode->color = RED;  // new nodes are always red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Right rotate the subtree rooted at node
void rightRotate(RBTreeNode **root, RBTreeNode *y) {
    RBTreeNode *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

// Left rotate the subtree rooted at node
void leftRotate(RBTreeNode **root, RBTreeNode *x) {
    RBTreeNode *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Fix violations after insertion
void fixInsert(RBTreeNode **root, RBTreeNode *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBTreeNode *y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                // Case 1: Uncle is red
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2: z is the right child
                    z = z->parent;
                    leftRotate(root, z);
                }
                // Case 3: z is the left child
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            RBTreeNode *y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                // Case 1: Uncle is red
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // Case 2: z is the left child
                    z = z->parent;
                    rightRotate(root, z);
                }
                // Case 3: z is the right child
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Insert a new node with the given key
void insert(RBTreeNode **root, int key) {
    RBTreeNode *z = tree_createNode(key);
    RBTreeNode *y = NULL;
    RBTreeNode *x = *root;

    // Perform a regular BST insert
    while (x != NULL) {
        y = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z;  // Tree was empty
    else if (key < y->key)
        y->left = z;
    else
        y->right = z;

    // Fix any violations
    fixInsert(root, z);
}

// Perform a BST transplant
void transplant(RBTreeNode **root, RBTreeNode *u, RBTreeNode *v) {
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

// Delete a node with the given key
void delete(RBTreeNode **root, int key) {
    RBTreeNode *z = *root;
    RBTreeNode *x, *y;

    // Find the node to delete
    while (z != NULL && z->key != key) {
        if (key < z->key)
            z = z->left;
        else
            z = z->right;
    }

    if (z == NULL) {
        printf("Node with key %d not found.\n", key);
        return;
    }

    y = z;
    Color originalColor = y->color;
    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = z->right;
        while (y->left != NULL)
            y = y->left;

        originalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (originalColor == BLACK)
        fixDelete(root, x);
}

// Fix violations after deletion
void fixDelete(RBTreeNode **root, RBTreeNode *x) {
    while (x != *root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            RBTreeNode *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL)
                        w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != NULL)
                    w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            RBTreeNode *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL)
                        w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != NULL)
                    w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    if (x != NULL)
        x->color = BLACK;
}

// Function to print the tree (in-order traversal)
void inorderTraversal(RBTreeNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d (%s)\n", root->key, root->color == RED ? "RED" : "BLACK");
        inorderTraversal(root->right);
    }
}
