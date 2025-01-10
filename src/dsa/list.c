#include "list.h"

// Function to create a new node
Node* createNode(Data data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL; // Return NULL on memory allocation failure
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the head of the list
int list_insertAtHead(Node **head, Data data) {
    Node* newNode = createNode(data);
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

// Function to insert a node at the tail of the list
int list_insertAtTail(Node **head, Data data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        return ERROR_MEMORY_ALLOCATION_FAILED;
    }

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }

    return SUCCESS;
}

// Function to delete a node from the list
int list_deleteNode(Node **head, Data data) {
    if (*head == NULL) {
        return ERROR_LIST_EMPTY;
    }

    Node* temp = *head;
    while (temp != NULL && (
            temp->data.student_number != data.student_number ||
            strcmp(temp->data.general_course_name, data.general_course_name) != 0 ||
            strcmp(temp->data.general_course_instructor, data.general_course_instructor) != 0 ||
            temp->data.general_course_score != data.general_course_score ||
            strcmp(temp->data.core_course_name, data.core_course_name) != 0 ||
            strcmp(temp->data.core_course_instructor, data.core_course_instructor) != 0 ||
            temp->data.core_course_score != data.core_course_score)) {
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
int list_print(Node *head) {
    if (head == NULL) {
        return ERROR_LIST_EMPTY;
    }

    Node* temp = head;
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

// Function to free the entire list
void list_free(Node *head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

// Function to merge two sorted lists
Node* merge(Node* left, Node* right) {
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
Node* split(Node* head) {
    Node* fast = head;
    Node* slow = head;

    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* middle = slow->next;
    slow->next = NULL;

    return middle;
}

// Merge Sort the list based on student_number
void list_sort(Node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    Node* middle = split(*head);
    list_sort(head);
    list_sort(&middle);

    *head = merge(*head, middle);
}
