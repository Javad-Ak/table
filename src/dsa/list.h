//
// Created by Javad on 1/8/2025.
//

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
typedef struct List_Node {
    Data data;
    struct List_Node *prev;
    struct List_Node *next;
} List_Node;

// Function declarations
List_Node* list_createNode(Data data);
int list_insertAtHead(List_Node **head, Data data);
int list_insertAtTail(List_Node **head, Data data);
int list_deleteNode(List_Node **head, int key);
int list_print(List_Node *head);
void list_free(List_Node *head);
void list_sort(List_Node **head);

List_Node* list_select(List_Node* head, const char* column_name, const char* value, bool sort_flag);
int list_update(List_Node* head, const char* column_name, const char* value, const char* new_value);
int list_delete(List_Node** head, const char* column_name, const char* value);

#endif
