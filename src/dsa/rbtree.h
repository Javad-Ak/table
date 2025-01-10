#ifndef RBTREE_H
#define RBTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct RBTreeNode {
    int key;
    Color color;  // RED or BLACK
    struct RBTreeNode *left, *right, *parent;
} RBTreeNode;

// Function declarations
RBTreeNode* tree_createNode(int key);
void rightRotate(RBTreeNode **root, RBTreeNode *y);
void leftRotate(RBTreeNode **root, RBTreeNode *x);
void fixInsert(RBTreeNode **root, RBTreeNode *z);
void insert(RBTreeNode **root, int key);
void transplant(RBTreeNode **root, RBTreeNode *u, RBTreeNode *v);
void delete(RBTreeNode **root, int key);
void fixDelete(RBTreeNode **root, RBTreeNode *x);
void inorderTraversal(RBTreeNode *root);

#endif
