//
// Created by Javad on 1/8/2025.
//

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Error literals
#define SUCCESS 0
#define ERROR_MEMORY_ALLOCATION_FAILED -1
#define ERROR_NODE_NOT_FOUND -2
#define ERROR_LIST_EMPTY -3

// Define the structure for data that will be stored in each node
typedef struct Data {
    int student_number;
    char general_course_name[33];
    char general_course_instructor[33];
    int general_course_score;

    char core_course_name[33];
    char core_course_instructor[33];
    int core_course_score;
} Data;

// Define the structure for a doubly linked list node
typedef struct Node {
    Data data;
    struct Node *prev;
    struct Node *next;
} Node;

// Function declarations
Node* createNode(Data data);
int insertAtHead(Node **head, Data data);
int insertAtTail(Node **head, Data data);
int deleteNode(Node **head, Data data);
int printList(Node *head);
void freeList(Node *head);
void sortList(Node **head); // merge sort

#endif
