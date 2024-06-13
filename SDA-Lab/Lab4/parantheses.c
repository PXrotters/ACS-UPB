#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 256

typedef char Item;
#include "Stack.h"

int isBalanced(const char *str, int length){
  Stack *stack = createStack();
  for (int i = 0; i < length ; i++) {
    if (str[i] == '(') {
      push (stack, str[i]);
    } else if (str[i] == '[') {
      push (stack, str[i]);
    } else if (str[i] == '{') {
      push (stack, str[i]);
    }
    if (str[i] == ')') {
      if (stack -> head != NULL) {
        if (stack -> head -> elem == '(') {
        pop(stack);
        } else {
          return 0;
        }
      } else {
        return 0;
      }
      } else if (str[i] == ']') {
         if (stack -> head != NULL) {
        if (stack -> head -> elem == '[') {
        pop(stack);
        } else {
          return 0;
        }
         }
      } else if (str[i] == '}') {
         if (stack -> head != NULL) {
        if (stack -> head -> elem == '{') {
        pop(stack); 
        } else {
          return 0;
        }
         }
      }
  }
  if (isStackEmpty(stack) != 0) {
        return 1;
  } 
  return 0;
}
  

int main(){
    int len;
    char buffer[MAX_INPUT_LEN];
    FILE* inputFile = fopen("input-parantheses.txt","r");
    if(inputFile == NULL) return 1;


    while(fgets(buffer, MAX_INPUT_LEN, inputFile) != NULL){
      buffer[strcspn(buffer, "\r\n")] = 0;
      len = strlen(buffer);
      if(len == 0) break;

      if(isBalanced(buffer, len))
        printf("%s ---> is balanced.\n", buffer);
      else
        printf("%s ---> not balanced.\n", buffer);
    }

    fclose(inputFile);

    return 0;
}
