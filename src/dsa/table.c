//
// Created by Javad on 1/8/2025.
//

#include "table.h"

// private hashmap to store tables
static Table* table_hashmap[TABLE_HASH_SIZE];

// Hash function
unsigned int hashTableName(const char* table_name) {
    unsigned int hash = 0;
    while (*table_name) {
        hash = (hash << 5) + *table_name++;
    }
    return hash % TABLE_HASH_SIZE;
}

// private function to get a table by name
static Table* getTableByName(const char* table_name) {
    unsigned int index = hashTableName(table_name);
    Table* current = table_hashmap[index];
    while (current != NULL && strcmp(current->name, table_name) != 0) {
        current = current->next;
    }
    return current;
}

// Create a new table
int table_create(const char* table_name) {
    unsigned int index = hashTableName(table_name);
    Table* new_table = malloc(sizeof(Table));
    if (new_table == NULL) {
        return ERROR_MEMORY_ALLOCATION_FAILED;
    }
    strncpy(new_table->name, table_name, MAX_TABLE_NAME_LEN);
    new_table->records = NULL;
    new_table->next = table_hashmap[index];
    table_hashmap[index] = new_table;
    return SUCCESS;
}

// Create Index based on key
void createIndex(Table* table) {
    if (!table || table->isIndexed) return;

    RBTreeNode* new_tree = NULL;

    List_Node* current = table->records;
    while (current) {
        tree_insert(&new_tree, current->data);
        current = current->next;
    }

    table->index = new_tree;
    table->isIndexed = true;

    list_free(table->records);
    table->records = NULL;
}

// Create Index based on key
void table_createIndex(const char* table_name) {
    createIndex(getTableByName(table_name));
}

// Fill records from index
void fillListFromTree(RBTreeNode* node, List_Node** records) {
    if (!node) return;

    fillListFromTree(node->left, records);
    list_insertAtTail(records, node->data);
    fillListFromTree(node->right, records);
}

// Delete Index
void deleteIndex(Table* table) {
    if (!table || !table->index) return;

    fillListFromTree(table->index, &table->records);

    tree_free(table->index);
    table->index = NULL;
    table->isIndexed = false;
}

// Delete a table
int table_delete(const char* table_name) {
    unsigned int index = hashTableName(table_name);
    Table* current = table_hashmap[index];
    Table* prev = NULL;
    while (current != NULL && strcmp(current->name, table_name) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        return ERROR_TABLE_NOT_FOUND;
    }

    if (prev == NULL) {
        table_hashmap[index] = current->next;
    } else {
        prev->next = current->next;
    }

    if (current->isIndexed)
        tree_free(current->index);
    else
        list_free(current->records);

    free(current);
    return SUCCESS;
}

// Add a new record
int table_addRecord(const char* table_name, Data data) {
    Table* table = getTableByName(table_name);
    if (table == NULL) {
        return ERROR_TABLE_NOT_FOUND;
    }

    if (table->isIndexed) {
        tree_insert(&table->index, data);
        return SUCCESS;
    } else {
        return list_insertAtTail(&table->records, data);
    }
}

// Delete records
int table_deleteRecord(const char* table_name, const char* column_name, const char* value) {
    Table* table = getTableByName(table_name);
    if (table == NULL) return ERROR_TABLE_NOT_FOUND;

    if (table->isIndexed && strcmp("student_number", column_name) == 0) {
        tree_delete(&table->index, strtol(value, NULL, 10));
        return SUCCESS;
    } else if (table->isIndexed) {
        deleteIndex(table);
    }

    return list_delete(&(table->records), column_name, value);
}

// Update records
int table_updateRecord(const char* table_name, const char* column_name, const char* value, const char* new_value) {
    Table* table = getTableByName(table_name);
    if (table == NULL) return -1;

    if (table->isIndexed && strcmp("student_number", column_name) == 0) {
        int key = strtol(value, NULL, 10);
        int newKey = strtol(new_value, NULL, 10);

        RBTreeNode* node = tree_find(table->index, key);
        if (node == NULL) return ERROR_RECORD_NOT_FOUND;
        node->data.student_number = newKey;

        tree_update(&table->index, key, node->data);
        return SUCCESS;
    } else if (table->isIndexed) {
        deleteIndex(table);
    }

    List_Node* current = table->records;
    return list_update(current, column_name, value, new_value);
}

// Select records
List_Node* table_selectRecords(const char* table_name, const char* column_name, const char* value, bool sort_flag) {
    Table* table = getTableByName(table_name);
    if (table == NULL) {
        return NULL;
    }

    if (table->isIndexed && strcmp("student_number", column_name) == 0) {
        RBTreeNode* node = tree_find(table->index, strtol(value, NULL, 10));
        return list_createNode(node->data);
    } else if (table->isIndexed) {
        deleteIndex(table);
    }

    List_Node* head = table->records;
    return list_select(head, column_name, value, sort_flag);
}

int table_print(const char* table_name, bool sort_flag) {
    Table* table = getTableByName(table_name);
    if (table == NULL) {
        return ERROR_TABLE_NOT_FOUND;
    }

    if (table->isIndexed) {
        tree_inorderPrint(table->index);
    } else {
        if (sort_flag) list_sort(&table->records);
        list_print(table->records);
    }
    return SUCCESS;
}

