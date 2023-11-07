/* Lemnaru Mihai-Daniel - 312CD */
#define lung 20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {   //definire structura banda magica
    char value;
    struct node *next;
    struct node *prev;
} Node;

typedef struct list {
    struct node *sentinel, *finger;
} List;

typedef struct Queue {   //definire structura coada
    char *value;
    struct Queue *next;
} Queue;

typedef struct Stack {   //definire structura stiva
    struct node *current_position;
    struct Stack *next;
} Stack;

void pushStack(Node **finger, Stack **top) {
    Stack *aux = (Stack *)malloc(sizeof(Stack));
    aux -> current_position = *finger;
    aux -> next = *top;
    *top = aux;
}

void popStack (Stack **top) {
    Stack *temp;
    temp = *top;
    if (*top != 0) {
        *top = (*top) -> next;
        free (temp);
    }
}

void emptyStack (Stack **top) {
    Stack *aux;
    while (*top != 0) {
    aux = *top;
    *top = (*top) -> next;
    free(aux);
    }
}

void freeQueue(Queue **front) {
    while (*front != NULL) {
        Queue *temp = *front;
        *front = (*front) -> next;
        free(temp -> value);
        free(temp);
    }
}

void freeStack(Stack **top) {
    while (*top != NULL) {
        Stack *temp = *top;
        *top = (*top) -> next;
        free(temp);
    }
}

void freeList(Node **head) {
    while (*head != NULL) {
        Node *temp = *head;
        *head = (*head) -> next;
        free(temp);
    }
}

List *init_list(List **list) {
    *list = (List *)malloc(sizeof(List));
    (*list) -> sentinel = (Node *)malloc(sizeof(Node));
    (*list) -> finger = (Node *)malloc(sizeof(Node));
    (*list) -> sentinel -> value = '\0';
    (*list) -> sentinel -> next = (*list) -> finger;
    (*list) -> sentinel -> prev = NULL;
    (*list) -> finger -> prev = (*list) -> sentinel;
    (*list) -> finger -> value = '#';
    (*list) -> finger -> next = NULL;
    return *list;
}

Node *create_node() {
    Node *newnode = (Node *)malloc(sizeof(Node *));
    newnode -> value = '#';
    newnode -> next = NULL;
    newnode -> prev = NULL;
    return newnode;
}

Node *MOVE_RIGHT(List *list)
{
    Node *newnode;
    newnode = create_node();
    if (list -> finger -> next == NULL)
    {
        list -> finger -> next = newnode;
        newnode -> prev = list -> finger;
        return newnode;
    }
    else
    {
        list -> finger = list -> finger -> next;
        return list -> finger;
    }
}

Node *MOVE_LEFT(List *list)
{
    if (list -> finger -> prev == list -> sentinel)
    {
        return list -> finger;
    }
    else
    {
        list -> finger = list -> finger -> prev;
        return list -> finger;
    }
}

Node *INSERT_LEFT(List *list, char data) {
    Node *newnode;
    newnode = create_node();
    if (list -> finger -> prev != list -> sentinel) {
        newnode -> value = data;
        newnode -> next = list -> finger;
        newnode -> prev = list -> finger -> prev;
        list -> finger -> prev -> next = newnode;
        list -> finger -> prev = newnode;
        list -> finger = newnode;
    }
    return list -> finger;
}

Node *INSERT_RIGHT(List *list, char data) {
    Node *newnode;
    newnode = create_node();
    if (list -> finger -> next == NULL) {
        list -> finger -> next = newnode;
        newnode -> prev = list -> finger;
        newnode -> value = data;
        return newnode;
    } else {
        newnode -> value = data;
        newnode -> prev = list -> finger;
        newnode -> next = list -> finger -> next;
        list -> finger -> next -> prev = newnode;
        list -> finger -> next = newnode;
        return newnode;
    }
}

Node *MOVE_LEFT_CHAR(List *list, char data) {
    Node *temp = list -> finger;
    while (list -> finger != list -> sentinel) {
        if (list -> finger -> value == data) {
            return list -> finger;
            break;
        }
        list -> finger = list -> finger -> prev;
    }
    return temp;
}

Node *MOVE_RIGHT_CHAR(List *list, char data) {
    Node *newnode;
    newnode = create_node();
    int ok = 0;
    while (list -> finger -> next != NULL) {
        if (list -> finger -> value == data) {
            ok = 1;
            return list -> finger;
            break;
        }
        list -> finger = list -> finger -> next;
    }
    if (list -> finger -> value == data) {
        return list -> finger;
    } else if (ok == 0) {
        list -> finger -> next = newnode;
        newnode -> prev = list -> finger;
    }
    if (ok == 1) {
        return list -> finger;
    } else {
        return newnode;
    }
}

int main()
{
    FILE *input, *output;
    input = fopen("tema1.in", "r");
    output = fopen("tema1.out", "w");
    int error = 0, ok = 0;
    char s[lung], n[lung];
    List *list = init_list(&list);
    Node *iter;
    Queue *front = 0, *rear = 0, *newnode, *aux, *temp;
    Stack *undo = 0, *redo = 0;
    if (input == NULL || output == NULL) { // verificam daca fisierele s-au deschis cu succes
        printf("Nu s-au putut deschide fisierele\n");
        return 1;
    }
    fgets(n, lung, input);
    while (fgets(s, lung, input) != NULL) {   //citim din fisier cate o linie
        int len = strlen(s);
        if (s[len-1] == '\n') { // daca exista newline la final, il eliminam
            s[len-1] = '\0';
            len--;
        }
        if ((strcmp(s, "MOVE_LEFT") == 0) || (strcmp(s, "MOVE_RIGHT") == 0)) {
            newnode = (Queue *)malloc(sizeof(Queue));
            newnode -> value = malloc(lung * sizeof(Queue));
            strncpy(newnode -> value, s, strlen(s));
            newnode -> next = NULL;
            if (front == 0 && rear == 0) {
                front = rear = newnode;
            } else {
                rear -> next = newnode;
                rear = newnode;
            }
        } else if ((strstr(s, "WRITE") != 0)) {
            newnode = (Queue *)malloc(sizeof(Queue));
            newnode -> value = malloc(lung * sizeof(Queue));
            strncpy(newnode -> value, s, strlen(s));
            newnode -> next = NULL;
            if (front == 0 && rear == 0) {
                front = rear = newnode;
            } else {
                rear -> next = newnode;
                rear = newnode;
            }
        } else if ((strstr(s, "INSERT_LEFT") != 0)) {
            newnode = (Queue *)malloc(sizeof(Queue));
            newnode -> value = malloc(lung * sizeof(Queue));
            strncpy(newnode -> value, s, strlen(s));
            newnode -> next = NULL;
            if (front == 0 && rear == 0) {
                front = rear = newnode;
            } else {
                rear -> next = newnode;
                rear = newnode;
            }
        } else if ((strstr(s, "INSERT_RIGHT") != 0)) {
            newnode = (Queue *)malloc(sizeof(Queue));
            newnode -> value = malloc(lung * sizeof(Queue));
            strncpy(newnode -> value, s, strlen(s));
            newnode -> next = NULL;
            if (front == 0 && rear == 0) {
                front = rear = newnode;
            } else {
                rear -> next = newnode;
                rear = newnode;
            }
        } else if ((strstr(s, "MOVE_LEFT_CHAR") != 0)) {
            newnode = (Queue *)malloc(sizeof(Queue));
            newnode -> value = malloc(lung * sizeof(Queue));
            strncpy(newnode -> value, s, strlen(s));
            newnode -> next = NULL;
            if (front == 0 && rear == 0) {
                front = rear = newnode;
            } else {
                rear -> next = newnode;
                rear = newnode;
            }
        } else if ((strstr(s, "MOVE_RIGHT_CHAR") != 0)) {
            newnode = (Queue *)malloc(sizeof(Queue));
            newnode -> value = malloc(lung * sizeof(Queue));
            strncpy(newnode -> value, s, strlen(s));
            newnode -> next = NULL;
            if (front == 0 && rear == 0) {
                front = rear = newnode;
            } else {
                rear -> next = newnode;
                rear = newnode;
            }
        }
        if ((strcmp(s, "EXECUTE") == 0)) {
            if (aux == front) {   //reactualizare cap in coada modificata
                front = front -> next;
            }
            temp = front;
            if (front == 0 || rear == 0) {   //verificare coada goala
                printf("Nu avem operatii");
            } else {
                if (front != rear) {   //deplasam capul in coada
                    front = front -> next;
                }
                if (strcmp(temp -> value, "MOVE_RIGHT") == 0) {
                    pushStack(&list -> finger, &undo);   //actualizare stiva UNDO
                    list -> finger = MOVE_RIGHT(list);   //modificare pozitie deget
                }
                 if (strcmp(temp -> value, "MOVE_LEFT") == 0) {
                    iter = list -> finger;
                    list -> finger = MOVE_LEFT(list);   //modificare pozitie deget
                    if (iter != list -> finger) {
                       pushStack(&iter, &undo);   //actualizare stiva UNDO
                    }
                }
                 if (strstr(temp -> value, "WRITE") != 0) {
                    list -> finger -> value = temp -> value[strlen(temp -> value) - 1];
                    emptyStack(&undo);   //golire stiva UNDO
                    emptyStack(&redo);   //golire stiva REDO
                }
                 if (strstr(temp -> value, "MOVE_LEFT_CHAR") != 0) {
                    iter = list -> finger;
                    if (list -> finger -> value == temp -> value[strlen(temp -> value) - 1]) {
                        ok++;
                    }
                    list -> finger = MOVE_LEFT_CHAR(list, temp -> value[strlen(temp -> value) - 1]);
                    if (iter == list -> finger && ok == 0) {   //verificare comanda invalida
                        error++;
                    }
                    emptyStack(&undo);   //golire stiva UNDO
                    emptyStack(&redo);   //golire stiva REDO
                }
                 if (strstr(temp -> value, "MOVE_RIGHT_CHAR") != 0) {
                    list -> finger = MOVE_RIGHT_CHAR(list, temp -> value[strlen(temp -> value) - 1]);
                    emptyStack(&undo);   //golire stiva UNDO
                    emptyStack(&redo);   //golire stiva REDO
                }
                 if (strstr(temp -> value, "INSERT_RIGHT") != 0) {
                    list -> finger = INSERT_RIGHT(list, temp -> value[strlen(temp -> value) - 1]);
                    emptyStack(&undo);   //golire stiva UNDO
                    emptyStack(&redo);   //golire stiva REDO
                }
                 if (strstr(temp -> value, "INSERT_LEFT") != 0) {
                    iter = list -> finger;
                    list -> finger = INSERT_LEFT(list, temp -> value[strlen(temp -> value) - 1]);
                    if (iter == list -> finger) {
                        error++;
                    }
                    emptyStack(&undo);   //golire stiva UNDO
                    emptyStack(&redo);   //golire stiva REDO
                }
                if (front == rear && rear == temp) {
                    aux = front;
                }
            }
        }
        if (strcmp(s, "UNDO") == 0) {
            pushStack(&list -> finger, &redo);   //adaugare pozitie actuala deget in stiva REDO
            list -> finger = undo -> current_position;   //actualizare deget
            popStack(&undo);   //eliminare comanda din stiva UNDO
        }
        if (strcmp(s, "REDO") == 0) {
            pushStack(&list -> finger, &undo);   //adaugare pozitie actuala deget in stiva UNDO
            list -> finger = redo -> current_position;   //actualizare deget
            popStack(&redo);   //eliminare comanda din stiva REDO
        }
        if (strcmp(s, "SHOW") == 0) {
            if (error != 0) {
                fprintf(output, "ERROR\n");
            }
            iter = list -> sentinel -> next;
            while (iter != NULL) {
                 if (iter == list -> finger) {
                    fprintf(output, "|%c|", iter -> value);
                    iter = iter -> next;
                } else {
                fprintf(output, "%c", iter->value);
                iter = iter -> next;
                }
                }
                fprintf(output, "\n");
            error = 0;
        }
        if (strcmp(s, "SHOW_CURRENT") == 0) {
                if (error != 0) {
                    fprintf(output, "ERROR\n");
                }
                fprintf(output, "%c", list -> finger -> value);
                fprintf(output, "\n");
            error = 0;
        }
    }
    freeQueue(&front);
    freeStack(&undo);
    freeStack(&redo);
    freeList(&list -> sentinel);
    return 0;
}
