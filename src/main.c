//
// Created by Javad on 1/8/2025.
//

#include <stdio.h>
#include "dsa/list.h"
#include "dsa/rbtree.h"
#include "dsa/table.h"

void testList();
void testMap();
void testTree();
void testTable();
void testIndex();

int main() {
  printf("AUT-CE DSA Project, Jan 2025, Mohammad Javad Akbari 40231005\n");

  printf("\n-------- running test cases...\n");
  // testList();
  // testTree();
  testTable();
  testIndex();
  printf("\n-------- all tests done.\n");

  return 0;
}

void testList() {
  printf("\n---- Testing list...\n");

  List_Node* head = NULL;
  Data data1 = {4000, "Math101", "Dr. Smith", 18, "CS101", "Prof. John", 17};
  Data data2 = {3000, "English102", "Dr. White", 16, "CS102", "Prof. Mary", 19};
  Data data3 = {2000, "History103", "Dr. Green", 15, "CS103", "Prof. Peter", 14};
  Data data4 = {1000, "Biology104", "Dr. Blue", 20, "CS104", "Prof. Alice", 16};

  list_insertAtHead(&head, data1);
  list_insertAtHead(&head, data2);
  list_insertAtTail(&head, data3);
  list_insertAtTail(&head, data4);

  list_sort(&head);
  list_print(head);
  list_free(head);
}

void testTable() {
  printf("---- Testing Table...\n");

  table_create("t1");

  Data data1 = {1001, "Math101", "Dr. Akbari", 18, "DS101", "Prof. Bagheri", 17};
  Data data2 = {1002, "English102", "Dr. Bayati", 16, "DS102", "Prof. Shahreza", 19};
  Data data3 = {2001, "Math101", "Dr. Smith", 18, "DS101", "Prof. John", 17};
  Data data4 = {2002, "English102", "Dr. White", 16, "DS102", "Prof. Mary", 19};

  table_addRecord("t1", data1);
  table_addRecord("t1", data2);
  table_addRecord("t1", data3);
  table_addRecord("t1", data4);

  table_deleteRecord("t1", "student_number", "1001");
  table_updateRecord("t1", "student_number", "1002", "5000");
  List_Node* sel = table_selectRecords("t1","student_number","2001", true);

  table_print("t1", true);
  printf("###\n\n");
  list_print(sel);

  table_delete("t1");
}

void testTree() {
  printf("---- Testing Tree...\n");

  Data data1 = {4000, "Math101", "Dr. Akbari", 18, "DS101", "Prof. Bagheri", 17};
  Data data2 = {3000, "English102", "Dr. Bayati", 16, "DS102", "Prof. Shahreza", 19};
  Data data3 = {2000, "Math101", "Dr. Smith", 18, "DS101", "Prof. John", 17};
  Data data4 = {1000, "English102", "Dr. White", 16, "DS102", "Prof. Mary", 19};

  RBTreeNode *root = NULL;

  tree_insert(&root, data1);
  tree_insert(&root, data2);
  tree_insert(&root, data3);
  tree_insert(&root, data4);
  tree_delete(&root, 4000);

  tree_inorderPrint(root);
}

void testIndex() {
  printf("\n---- Testing Table Index...\n");

  table_create("t1");

  Data data1 = {1001, "Math101", "Dr. Akbari", 18, "DS101", "Prof. Bagheri", 17};
  Data data2 = {1002, "English102", "Dr. Bayati", 16, "DS102", "Prof. Shahreza", 19};
  Data data3 = {2001, "Math101", "Dr. Smith", 18, "DS101", "Prof. John", 17};
  Data data4 = {2002, "English102", "Dr. White", 16, "DS102", "Prof. Mary", 19};

  table_addRecord("t1", data1);
  table_addRecord("t1", data2);
  table_addRecord("t1", data3);
  table_addRecord("t1", data4);

  table_createIndex("t1");

  table_deleteRecord("t1", "student_number", "1001");
  table_updateRecord("t1", "student_number", "1002", "5000");
  List_Node* sel = table_selectRecords("t1","student_number","2001", true);

  table_print("t1", true);
  printf("###\n\n");
  list_print(sel);

  table_delete("t1");
}
