//
// Created by Javad on 1/8/2025.
//

#ifndef TABLE_H
#define TABLE_H

#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "rbtree.h"

#define MAX_TABLE_NAME_LEN 64
#define TABLE_HASH_SIZE 100

// Error codes
#define SUCCESS 0
#define ERROR_MEMORY_ALLOCATION_FAILED -1
#define ERROR_TABLE_NOT_FOUND -2
#define ERROR_RECORD_NOT_FOUND -3
#define ERROR_INVALID_COLUMN -4

// Table structure
typedef struct Table {
    char name[MAX_TABLE_NAME_LEN];
    bool isIndexed;

    List_Node* records;
    RBTreeNode* index;

    struct Table* next;
} Table;

// Function declarations
int table_create(const char* table_name);
int table_delete(const char* table_name);
int table_addRecord(const char* table_name, Data data);
int table_deleteRecord(const char* table_name, const char* column_name, const char* value);
int table_updateRecord(const char* table_name, const char* column_name, const char* value, const char* new_value);
int table_print(const char* table_name, bool sort_flag);
void table_createIndex(const char* table_name);
List_Node* table_selectRecords(const char* table_name, const char* column_name, const char* value, bool sort_flag);

#endif
