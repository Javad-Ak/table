#include "list.h"

// Function to create a new node
List_Node* list_createNode(Data data) {
    List_Node* newNode = (List_Node*)malloc(sizeof(List_Node));
    if (newNode == NULL) return NULL;

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to check duplicate primary key
bool list_studentNumberExists(List_Node *head, int student_number) {
    List_Node *current = head;
    while (current != NULL) {
        if (current->data.student_number == student_number) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Function to insert a node at the head of the list without duplicates
int list_insertAtHead(List_Node **head, Data data) {
    if (list_studentNumberExists(*head, data.student_number)) {
        return ERROR_DUPLICATE_STUDENT_NUMBER;
    }

    List_Node *newNode = list_createNode(data);
    if (newNode == NULL) {
        return ERROR_MEMORY_ALLOCATION_FAILED;
    }

    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;

    return SUCCESS;
}

// Function to insert a node at the tail of the list without duplicates
int list_insertAtTail(List_Node **head, Data data) {
    if (list_studentNumberExists(*head, data.student_number)) {
        return ERROR_DUPLICATE_STUDENT_NUMBER;
    }

    List_Node* newNode = list_createNode(data);
    if (newNode == NULL) {
        return ERROR_MEMORY_ALLOCATION_FAILED;
    }

    if (*head == NULL) {
        *head = newNode;
    } else {
        List_Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }

    return SUCCESS;
}

// Function to delete a node from the list
int list_deleteNode(List_Node **head, int key) {
    if (*head == NULL) {
        return ERROR_LIST_EMPTY;
    }

    List_Node* temp = *head;
    while (temp != NULL && temp->data.student_number != key) {
        temp = temp->next;
    }

    if (temp == NULL) {
        return ERROR_NODE_NOT_FOUND;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
    return SUCCESS;
}

// Function to print the list from head to tail
int list_print(List_Node *head) {
    if (head == NULL) {
        return ERROR_LIST_EMPTY;
    }

    List_Node* temp = head;
    while (temp != NULL) {
        printf("Student Number: %d\n", temp->data.student_number);
        printf("General Course Name: %s, Instructor: %s, Score: %d\n",
               temp->data.general_course_name, temp->data.general_course_instructor, temp->data.general_course_score);
        printf("Core Course Name: %s, Instructor: %s, Score: %d\n",
               temp->data.core_course_name, temp->data.core_course_instructor, temp->data.core_course_score);
        printf("\n");
        temp = temp->next;
    }
    return SUCCESS;
}

// Function to merge two sorted lists
List_Node* merge(List_Node* left, List_Node* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    if (left->data.student_number <= right->data.student_number) {
        left->next = merge(left->next, right);
        if (left->next != NULL) {
            left->next->prev = left;
        }
        left->prev = NULL;
        return left;
    } else {
        right->next = merge(left, right->next);
        if (right->next != NULL) {
            right->next->prev = right;
        }
        right->prev = NULL;
        return right;
    }
}

// Function to split the list into two halves
List_Node* split(List_Node* head) {
    List_Node* fast = head;
    List_Node* slow = head;

    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    List_Node* middle = slow->next;
    slow->next = NULL;

    return middle;
}

// Merge Sort the list based on student_number
void list_sort(List_Node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    List_Node* middle = split(*head);
    list_sort(head);
    list_sort(&middle);

    *head = merge(*head, middle);
}

// Delete nodes
int list_delete(List_Node** head, const char* column_name, const char* value) {
    List_Node* current = *head;
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

            if (current == (*head)) {
                (*head) = current->next;
            }

            List_Node* temp = current;
            current = current->next;
            free(temp);

            deleted = 1;
        } else {
            current = current->next;
        }
    }

    return deleted ? SUCCESS : ERROR_NODE_NOT_FOUND;
}

// Update nodes
int list_update(List_Node* head, const char* column_name, const char* value, const char* new_value) {
    List_Node* current = head;
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

    return updated ? SUCCESS : ERROR_NODE_NOT_FOUND;
}

// Select nodes
List_Node* list_select(List_Node* head, const char* column_name, const char* value, bool sort_flag) {
    List_Node* current = head;
    List_Node* newHead = NULL;
    while (current != NULL) {
        if (strcmp(column_name, "student_number") == 0) {
            if (current->data.student_number == strtol(value, NULL, 10)) {
                list_insertAtTail(&newHead, current->data);
            }
        } else if (strcmp(column_name, "general_course_name") == 0) {
            if (strcmp(current->data.general_course_name, value) == 0) {
                list_insertAtTail(&newHead, current->data);
            }
        } else if (strcmp(column_name, "general_course_instructor") == 0) {
            if (strcmp(current->data.general_course_instructor, value) == 0) {
                list_insertAtTail(&newHead, current->data);
            }
        } else if (strcmp(column_name, "general_course_score") == 0) {
            if (current->data.general_course_score == strtol(value, NULL, 10)) {
                list_insertAtTail(&newHead, current->data);
            }
        } else if (strcmp(column_name, "core_course_name") == 0) {
            if (strcmp(current->data.core_course_name, value) == 0) {
                list_insertAtTail(&newHead, current->data);
            }
        } else if (strcmp(column_name, "core_course_instructor") == 0) {
            if (strcmp(current->data.core_course_instructor, value) == 0) {
                list_insertAtTail(&newHead, current->data);
            }
        } else if (strcmp(column_name, "core_course_score") == 0) {
            if (current->data.core_course_score == strtol(value, NULL, 10)) {
                list_insertAtTail(&newHead, current->data);
            }
        }

        current = current->next;
    }

    if (sort_flag) list_sort(&newHead);
    return newHead;
}

// Function to free the entire list
void list_free(List_Node *head) {
    while (head != NULL) {
        List_Node* temp = head;
        head = head->next;
        free(temp);
    }
}