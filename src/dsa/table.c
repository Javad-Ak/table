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
int createTable(const char* table_name) {
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

// Delete a table
int deleteTable(const char* table_name) {
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

    list_free(current->records);
    free(current);
    return SUCCESS;
}

// Add a new record
int addRecord(const char* table_name, Data data) {
    Table* table = getTableByName(table_name);
    if (table == NULL) {
        return ERROR_TABLE_NOT_FOUND;
    }
    return list_insertAtTail(&table->records, data);
}

// Delete records
int deleteRecord(const char* table_name, const char* column_name, const char* value) {
    Table* table = getTableByName(table_name);
    if (table == NULL) return ERROR_TABLE_NOT_FOUND;
    return list_delete(&(table->records), column_name, value);
}

// Update records
int updateRecord(const char* table_name, const char* column_name, const char* value, const char* new_value) {
    Table* table = getTableByName(table_name);
    if (table == NULL) return -1;

    List_Node* current = table->records;
    return list_update(current, column_name, value, new_value);
}

// Select records
List_Node* selectRecords(const char* table_name, const char* column_name, const char* value, bool sort_flag) {
    Table* table = getTableByName(table_name);
    if (table == NULL) {
        return NULL;
    }

    List_Node* head = table->records;
    return list_select(head, column_name, value, sort_flag);
}

int printTable(const char* table_name) {
    Table* table = getTableByName(table_name);
    if (table == NULL) {
        return ERROR_TABLE_NOT_FOUND;
    }
    list_print(table->records);
    return SUCCESS;
}
