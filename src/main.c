//
// Created by Javad on 1/8/2025.
//

#include <stdio.h>
#include "dsa/list.h"
#include "dsa/tree.h"
#include "dsa/table.h"

void testList();
void testMap();
void testTree();
void testTable();

int main() {
  printf("AUT-CE DSA Project, Jan 2025, Mohammad Javad Akbari 40231005\n");

  printf("\n-------- running test cases...\n");
  testList();
  testTree();
  testTable();
  printf("\n-------- all tests done.\n");

  return 0;
}

void testList() {
  printf("\n---- Testing list...\n");

  Node* head = NULL;
  Data data1 = {1001, "Math101", "Dr. Smith", 18, "CS101", "Prof. John", 17};
  Data data2 = {1002, "English102", "Dr. White", 16, "CS102", "Prof. Mary", 19};
  Data data3 = {1003, "History103", "Dr. Green", 15, "CS103", "Prof. Peter", 14};
  Data data4 = {1004, "Biology104", "Dr. Blue", 20, "CS104", "Prof. Alice", 16};

  insertAtHead(&head, data1);
  insertAtHead(&head, data2);
  insertAtTail(&head, data3);
  insertAtTail(&head, data4);

  sortList(&head);
  printList(head);
  freeList(head);
}

void testTable() {
  printf("\n---- Testing Table...\n");

  createTable("t1");
  createTable("t2");

  Data data1 = {1001, "Math101", "Dr. Akbari", 18, "DS101", "Prof. Bagheri", 17};
  Data data2 = {1002, "English102", "Dr. Bayati", 16, "DS102", "Prof. Shahreza", 19};
  addRecord("t1", data1);
  addRecord("t1", data2);

  Data data3 = {2001, "Math101", "Dr. Smith", 18, "DS101", "Prof. John", 17};
  Data data4 = {2002, "English102", "Dr. White", 16, "DS102", "Prof. Mary", 19};
  addRecord("t2", data3);
  addRecord("t2", data4);

  updateRecord("t1", "student_number", "1002", "1010");
  deleteRecord("t1", "student_number", "1001");

  printTable("t1");
  printTable("t2");

  // Delete tables t1 and t2
  deleteTable("t2");
  deleteTable("t1");
}

void testTree() {
  printf("\n---- Testing Tree...\n");
  printf("test\n");
}

