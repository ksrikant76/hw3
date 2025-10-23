#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
  if (head == NULL) { //base case
    smaller = NULL;
    larger = NULL;
    return;
  }

  //consume head and pass recurse on the next node
  Node* node = head;
  Node* rest = head->next;
  node->next = NULL;
  head = rest;
  llpivot(head, smaller, larger, pivot);

  //put node into smaller/larger
  if (node->val > pivot) {
    node->next = larger;
    larger = node;
  }
  else {
    node->next = smaller;
    smaller = node;
  }
}
