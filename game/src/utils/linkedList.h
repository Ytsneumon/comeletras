#ifndef UTILS_LINKED_LIST
#define UTILS_LINKED_LIST

typedef struct ListNode {
  void *val;
  struct ListNode *next;
  struct ListNode *previous;
} ListNode;

ListNode *createNode(void *value);

ListNode *addElement(ListNode *list, void *value);

ListNode *removeElementAt(ListNode *list, int index);

void *getElementAt(ListNode *list, int index);

#endif