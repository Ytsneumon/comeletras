#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

ListNode *createNode(void *value) {
  ListNode *list = malloc(sizeof(ListNode));
  list->val = value;
  list->next = NULL;
  list->previous = NULL;

  return list;
}

ListNode *addElement(ListNode *list, void *value) {
  ListNode *newNode = createNode(value);
  if (list == NULL) {
    return newNode;
  } else {
    ListNode *iterator = list;
    while (iterator->next != NULL) {
      iterator = iterator->next;
    }
    iterator->next = newNode;
    newNode->previous = iterator;
    return list;
  }
}

ListNode *removeElementAt(ListNode *list, int index) {
  int i = 0;
  ListNode *iterator = list;
  while (i < index && iterator != NULL) {
    iterator = iterator->next;
    i++;
  }
  if (iterator != NULL) {
    if (iterator->previous == NULL) {
      list = iterator->next;
    } else {
      iterator->previous->next = iterator->next;
    }
    if (iterator->next != NULL) {
      iterator->next->previous = iterator->previous;
    }
    free(iterator);
  }
  return list;
}

void *getElementAt(ListNode *list, int index) {
  ListNode *iterator = list;
  int i = 0;
  while (i < index) {
    if (iterator != NULL) {
      iterator = iterator->next;
    }
    i++;
  }
  if (iterator != NULL) {
    return iterator->val;
  } else {
    return NULL;
  }
}