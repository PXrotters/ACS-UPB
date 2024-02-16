#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Maximum number of characters that can be read
 * in one go from the keyboard
 */
#define MAX_INPUT_LEN 255

/**
 *  Generic Item type definition
 */
typedef char Item;

/**
 * The Double linked list interface
 */
#include "DoubleLinkedList.h"

/**
 * Utility functions for character lists
 */
void printList(List *list){
	ListNode* iterator = list->first;
	printf("[");
	while(iterator != list->last){
		printf("%c, ", iterator->elem);
		iterator = iterator->next;
	}
	printf("%c]",list->last->elem);
}

void printListReverse(List* list){
	ListNode* iterator = list->last;
	printf("[");
	while(iterator != list->last){
		printf("%c ", iterator->elem);
		iterator = iterator->prev;
	}
	printf("%c]",list->last->elem);
}




/* Plaindrome computation function */
int isPalindrome(List* list){
	int k = 0;
	ListNode *head = list -> first;
	ListNode *tail = list -> last;
	while (head != NULL && tail != NULL) {
		if (head -> elem != tail -> elem) {
			k++;
		}
		head = head -> next;
		tail = tail -> prev;
	}
	if (k == 0) {
		return 1;
	} else {
		return 0;
	}
}

/* Main Program */
int main(void) {

	int len;
	int inputCount = 0;
	char inputCharacters[256];
	FILE* inputFile = fopen("input","r");



	while(fgets(inputCharacters, MAX_INPUT_LEN, inputFile) != NULL){
			// Remove trailing CR/LF (i.e. '\r', '\n')
			inputCharacters[strcspn(inputCharacters, "\r\n")] = 0;
			len = strlen(inputCharacters);
			if(len == 0) break;

			List *list = createList();
			for(int i = 0; i < len; i++) insertAt(list, inputCharacters[i],i);


			printf("Input%d: ", ++inputCount);
			printf("\"%s\" --- ", inputCharacters);
			printf("List: ");
			printList(list);

			if(isPalindrome(list)) printf(" is a palindrome.");
			else printf(" is NOT a palindorme.");
			printf("\n");

			list = destroyList(list);
	}

	fclose(inputFile);
	return 0;
}



