#ifndef RBTREE_H
#define RBTREE_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define SUCCESS 0
#define NOT_FOUND -1

// RBT colors
typedef enum { RED, BLACK } Color;

// RBT structure
typedef struct RBTreeNode {
    int key;
    Data data;
    Color color;
    struct RBTreeNode *left, *right, *parent;
} RBTreeNode;

// Function declarations
RBTreeNode* tree_createNode(Data data);
void tree_insert(RBTreeNode **root, Data data);
void tree_delete(RBTreeNode **root, int key);
void tree_inorderPrint(RBTreeNode *root);
void tree_free(RBTreeNode* root);

RBTreeNode* tree_find(RBTreeNode* root, int key);
int tree_update(RBTreeNode** root, int key, Data new_data);

#endif
