#include "rbtree.h"

// Function to create a new node
RBTreeNode* tree_createNode(Data data) {
    RBTreeNode *newNode = (RBTreeNode*)malloc(sizeof(RBTreeNode));
    if (newNode == NULL) return NULL;

    newNode->key = data.student_number;
    newNode->data = data;
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

// Fix after insertion
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
void tree_insert(RBTreeNode **root, Data data) {
    int key = data.student_number;
    RBTreeNode *z = tree_createNode(data);
    RBTreeNode *y = NULL;
    RBTreeNode *x = *root;

    while (x != NULL) {
        y = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (key < y->key)
        y->left = z;
    else
        y->right = z;

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

// Fix after deletion
void fixDelete(RBTreeNode **root, RBTreeNode *x) {
    while (x != *root && (x == NULL || x->color == BLACK)) {
        if (x == NULL || x->parent == NULL) {
            break;
        }

        if (x == x->parent->left) {
            RBTreeNode *w = x->parent->right;

            // Case 1: Sibling is RED
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }

            // Case 2: Sibling and its children are BLACK
            if ((w == NULL || w->left == NULL || w->left->color == BLACK) &&
                (w == NULL || w->right == NULL || w->right->color == BLACK)) {
                if (w != NULL) w->color = RED;
                x = x->parent;
            } else {
                // Case 3: Sibling's right child is BLACK
                if (w != NULL && (w->right == NULL || w->right->color == BLACK)) {
                    if (w->left != NULL) w->left->color = BLACK;
                    if (w != NULL) w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }

                // Case 4: Sibling's right child is RED
                if (w != NULL) w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w != NULL && w->right != NULL) w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            // Symmetric cases
            RBTreeNode *w = x->parent->left;

            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }

            if ((w == NULL || w->right == NULL || w->right->color == BLACK) &&
                (w == NULL || w->left == NULL || w->left->color == BLACK)) {
                if (w != NULL) w->color = RED;
                x = x->parent;
            } else {
                if (w != NULL && (w->left == NULL || w->left->color == BLACK)) {
                    if (w->right != NULL) w->right->color = BLACK;
                    if (w != NULL) w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }

                if (w != NULL) w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w != NULL && w->left != NULL) w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }

    if (x != NULL) x->color = BLACK;
}


// Delete a node with the given key
void tree_delete(RBTreeNode **root, int key) {
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

// Function to print the tree (in-order traversal)
void tree_inorderPrint(RBTreeNode *root) {
    RBTreeNode* temp = root;
    if (temp != NULL) {
        tree_inorderPrint(temp->left);

        printf("Student Number: %d\n", temp->data.student_number);
        printf("General Course Name: %s, Instructor: %s, Score: %d\n",
               temp->data.general_course_name, temp->data.general_course_instructor, temp->data.general_course_score);
        printf("Core Course Name: %s, Instructor: %s, Score: %d\n",
               temp->data.core_course_name, temp->data.core_course_instructor, temp->data.core_course_score);
        printf("\n");

        tree_inorderPrint(temp->right);
    }
}

// Recursive function to free all nodes of the tree
void tree_free(RBTreeNode* root) {
    if (root == NULL) return;

    tree_free(root->left);
    tree_free(root->right);

    free(root);
}

// update a node
int tree_update(RBTreeNode** root, int key, Data new_data) {
    if (!root) return NOT_FOUND;

    RBTreeNode* p = *root;
    if (key < p->key) {
        return tree_update(&p->left, key, new_data);
    } else if (key > p->key) {
        return tree_update(&p->right, key, new_data);
    } else {
        tree_delete(root, key);
        tree_insert(root, new_data);
        return SUCCESS;
    }
}

// find a node
RBTreeNode* tree_find(RBTreeNode* root, int key) {
    if (!root) return NULL;


    if (key < root->key) {
        return tree_find(root->left, key);
    } else if (key > root->key) {
        return tree_find(root->right, key);
    } else {
        return root;
    }
}

