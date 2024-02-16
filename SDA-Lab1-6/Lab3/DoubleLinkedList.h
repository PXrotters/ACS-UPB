#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
}List;
// -----------------------------------------------------------------------------

/**
 * Create a new node
 *  [input]: Item
 *  [output]: List*
 */
ListNode *createNode(Item elem) {
	ListNode *node = malloc (sizeof (struct ListNode));
	node -> elem = elem;
	node -> next = node -> prev = NULL;
	return node;
}

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createList(void) {
	List *list = malloc (sizeof (struct List));
	list -> first = list -> last = NULL;
	return list;
}
// -----------------------------------------------------------------------------


/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list){
	if (list -> first == NULL && list -> last == NULL) {
		return 1;
	}
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem){
	ListNode *iter;
	iter = list -> first;
	while (iter != NULL) {
		if (iter -> elem == elem) {
			return 1;
		}
		iter = iter -> next;
	}
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */
void insertAt(List* list, Item elem, int pos){
	ListNode *N = createNode (elem);
	if (list == NULL || pos < 0)
	return N;
	ListNode *newnode = list -> first;
	while (pos != 0 && newnode != NULL) {
		newnode = newnode -> next;
		pos--;
	}
	if (pos != 0) {
		return list;
	}
	if (list -> first == NULL) {
		list -> first = list -> last = N;
		return list;
	}
	if (newnode == NULL) {
		list -> last -> next = N;
		N -> prev = list -> last;
		list -> last = N;
		return list;
	}
	if (newnode == list -> first) {
		N -> next = list -> last;
		list -> first -> prev = N;
		list -> first = N;
		return list;
	}
	N -> next = newnode;
	N -> prev = newnode -> prev;
	newnode -> prev -> next = N;
	newnode -> prev = N;
	return list;
}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance form a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem){
	if(list -> first == NULL) {
		return ;
	}
	ListNode *iter = list -> first;
	while (iter != NULL && iter -> elem != elem) {
		iter = iter -> next;
	}
	if (iter == NULL)
	return ;
	if (iter == list -> first && iter == list -> last) {
		list -> first = NULL;
		list -> last = NULL;
	} else if (iter == list -> first) {
		list -> first = iter -> next;
		iter -> next -> prev = NULL;
	} else if (iter == list -> last) {
		list -> last = iter -> prev;
		iter -> prev -> next = NULL;
	} else {
		iter -> prev -> next = iter -> next;
		iter -> next -> prev = iter -> prev;
	}
	free (iter);
}
// -----------------------------------------------------------------------------


/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int length(List *list){
	int k = 0;
	ListNode *iter = list -> first;
	while (iter != NULL) {
		k++;
		iter = iter -> next;
	}
	return k;
}
// -----------------------------------------------------------------------------



/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
List* destroyList(List* list){
	if (list == NULL) {
		return list;
	}
	ListNode *iter, *temp;
	iter = list -> first;
	while (iter != NULL) {
		temp = iter;
		iter = iter -> next;
		free (temp);
	}
	free (list);
	return NULL;
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_
