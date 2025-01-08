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

    freeList(current->records);
    free(current);
    return SUCCESS;
}

// Add a new record
int addRecord(const char* table_name, Data data) {
    Table* table = getTableByName(table_name);
    if (table == NULL) {
        return ERROR_TABLE_NOT_FOUND;
    }
    return insertAtTail(&table->records, data);
}

// Delete a record
int deleteRecord(const char* table_name, const char* column_name, const char* value) {
    Table* table = getTableByName(table_name);
    if (table == NULL) return ERROR_TABLE_NOT_FOUND;

    Node* current = table->records;
    int deleted = 0;

    while (current != NULL) {
        int shouldDelete = 0;

        if (strcmp(column_name, "student_number") == 0) {
            if (current->data.student_number == strtol(value, NULL, 10)) {
                shouldDelete = 1;
            }
        } else if (strcmp(column_name, "general_course_name") == 0) {
            if (strcmp(current->data.general_course_name, value) == 0) {
                shouldDelete = 1;
            }
        } else if (strcmp(column_name, "general_course_instructor") == 0) {
            if (strcmp(current->data.general_course_instructor, value) == 0) {
                shouldDelete = 1;
            }
        } else if (strcmp(column_name, "general_course_score") == 0) {
            if (current->data.general_course_score == strtol(value, NULL, 10)) {
                shouldDelete = 1;
            }
        } else if (strcmp(column_name, "core_course_name") == 0) {
            if (strcmp(current->data.core_course_name, value) == 0) {
                shouldDelete = 1;
            }
        } else if (strcmp(column_name, "core_course_instructor") == 0) {
            if (strcmp(current->data.core_course_instructor, value) == 0) {
                shouldDelete = 1;
            }
        } else if (strcmp(column_name, "core_course_score") == 0) {
            if (current->data.core_course_score == strtol(value, NULL, 10)) {
                shouldDelete = 1;
            }
        }

        if (shouldDelete) {
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;

            if (current == table->records) {
                table->records = current->next;
            }

            Node* temp = current;
            current = current->next;
            free(temp);

            deleted = 1;
        } else {
            current = current->next;
        }
    }

    return deleted ? SUCCESS : ERROR_RECORD_NOT_FOUND;
}

// Update a record
int updateRecord(const char* table_name, const char* column_name, const char* value, const char* new_value) {
    Table* table = getTableByName(table_name);
    if (table == NULL) return -1;

    Node* current = table->records;
    int updated = 0;

    while (current != NULL) {
        int shouldUpdate = 0;

        if (strcmp(column_name, "student_number") == 0) {
            if (current->data.student_number == strtol(value, NULL, 10)) {
                shouldUpdate = 1;
            }
        } else if (strcmp(column_name, "general_course_name") == 0) {
            if (strcmp(current->data.general_course_name, value) == 0) {
                shouldUpdate = 1;
            }
        } else if (strcmp(column_name, "general_course_instructor") == 0) {
            if (strcmp(current->data.general_course_instructor, value) == 0) {
                shouldUpdate = 1;
            }
        } else if (strcmp(column_name, "general_course_score") == 0) {
            if (current->data.general_course_score == strtol(value, NULL, 10)) {
                shouldUpdate = 1;
            }
        } else if (strcmp(column_name, "core_course_name") == 0) {
            if (strcmp(current->data.core_course_name, value) == 0) {
                shouldUpdate = 1;
            }
        } else if (strcmp(column_name, "core_course_instructor") == 0) {
            if (strcmp(current->data.core_course_instructor, value) == 0) {
                shouldUpdate = 1;
            }
        } else if (strcmp(column_name, "core_course_score") == 0) {
            if (current->data.core_course_score == strtol(value, NULL, 10)) {
                shouldUpdate = 1;
            }
        }

        if (shouldUpdate) {
            if (strcmp(column_name, "student_number") == 0) {
                current->data.student_number = strtol(new_value, NULL, 10);
            } else if (strcmp(column_name, "general_course_name") == 0) {
                strncpy(current->data.general_course_name, new_value, sizeof(current->data.general_course_name) - 1);
                current->data.general_course_name[sizeof(current->data.general_course_name) - 1] = '\0';
            } else if (strcmp(column_name, "general_course_instructor") == 0) {
                strncpy(current->data.general_course_instructor, new_value, sizeof(current->data.general_course_instructor) - 1);
                current->data.general_course_instructor[sizeof(current->data.general_course_instructor) - 1] = '\0';
            } else if (strcmp(column_name, "general_course_score") == 0) {
                current->data.general_course_score = strtol(new_value, NULL, 10);
            } else if (strcmp(column_name, "core_course_name") == 0) {
                strncpy(current->data.core_course_name, new_value, sizeof(current->data.core_course_name) - 1);
                current->data.core_course_name[sizeof(current->data.core_course_name) - 1] = '\0';
            } else if (strcmp(column_name, "core_course_instructor") == 0) {
                strncpy(current->data.core_course_instructor, new_value, sizeof(current->data.core_course_instructor) - 1);
                current->data.core_course_instructor[sizeof(current->data.core_course_instructor) - 1] = '\0';
            } else if (strcmp(column_name, "core_course_score") == 0) {
                current->data.core_course_score = strtol(new_value, NULL, 10);
            }

            updated = 1;
        }

        current = current->next;
    }

    return updated ? SUCCESS : ERROR_RECORD_NOT_FOUND;
}

// Select records
Node* selectRecords(const char* table_name, const char* column_name, const char* value, bool sort_flag) {
    Table* table = getTableByName(table_name);
    if (table == NULL) {
        return NULL;
    }

    Node* head = table->records;

    if (sort_flag) {
        sortList(&head);  // Merge sort by student_number
    }

    return head;
}

int printTable(const char* table_name) {
    Table* table = getTableByName(table_name);
    if (table == NULL) {
        return ERROR_TABLE_NOT_FOUND;
    }
    printList(table->records);
    return SUCCESS;
}
