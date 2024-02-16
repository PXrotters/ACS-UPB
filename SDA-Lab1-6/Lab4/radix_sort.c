#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INPUT_LEN 256


typedef int Item;
#include "Queue.h"


void printArray(int *arr, int len){
  for(int i=0; i < len; i++)  
    printf("%d ", arr[i]);
}

int arrayMaximum(const int* arr, int len){
	int max = arr[0];
	for(int i = 1; i < len; i++){
		if(arr[i] > max) 
			max = arr[i];
	}
	return max;
}

int getNumberOfDigits(int num){
	int digits = 0;
	while(num){
		num = num/10;
		digits++;
	}
	return digits;
}

void init(Queue* q) {
    q -> front = NULL;
    q -> rear = NULL;
	q -> size = 0;
}

int get_digit(int num, int place) {
    int digit = 0;
    for (int i = 0; i <= place; i++) {
        digit = num % 10;
        num /= 10;
    }
    return digit;
}

void radixSort(int *arr, int len){
	Queue buckets[10];
	for (int i = 0; i < 10; i++) {
        init(&buckets[i]);
    }
	int max = arrayMaximum(arr, len);
	int max_digits = getNumberOfDigits(max);
	for (int i = 0; i < max_digits; i++) {
		for (int j = 0; j< len; j++) {
			int digit = get_digit(arr[j], i);
			enqueue(&buckets[digit], arr[j]);
		}
		int index = 0;
		for (int j = 0; j < 10; j++) {
			while (!isQueueEmpty(&buckets[j])) {
				dequeue(&buckets[j]);
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		while (!isQueueEmpty(&buckets[i])) {
			dequeue(&buckets[i]);
		}
	}
}

int main(void){
	

    int len;
    char fileBuffer[MAX_INPUT_LEN];
    FILE* inputFile = fopen("input-radix-sort.csv","r");
    if(inputFile == NULL) return 1;

    int capacity = MAX_INPUT_LEN;
    int *arr = (int*) malloc(capacity*sizeof(int));

    int count = 0;
    while(fgets(fileBuffer, MAX_INPUT_LEN, inputFile) != NULL){
      fileBuffer[strcspn(fileBuffer, "\r\n")] = 0;
      len = strlen(fileBuffer);
      if(len == 0) break;

      char *token = strtok(fileBuffer,",\n");
      if(token == NULL) return 1;
      len = 0;
	  arr[len++] = atoi(token);
      while(token != NULL){
      	if(len == capacity){
      		capacity <<= 1;
      		arr = realloc(arr, capacity*sizeof(int));
      	}
    	
      	token = strtok(NULL,",\r\n");
      	if(token != NULL)
      		arr[len++] = atoi(token);     	
      }

      count++;
      printf("Input array %d:\t", count);
      printArray(arr, len);
      printf("\n");
      radixSort(arr, len);
      printf("Sorted array %d:\t", count);
      printArray(arr, len);
      printf("\n");
      printf("\n");
  	}

	free(arr);
	fclose(inputFile);
	return 0;
}
