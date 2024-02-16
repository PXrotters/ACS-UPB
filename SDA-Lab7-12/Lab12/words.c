#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Key;
typedef int Value;
typedef long(*HashFunction)(Key, long);

typedef struct Element {
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable {
  Element** elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable **h, long size, HashFunction f) {
  // Aloca memorie pentru structura HashTable
  *h = (HashTable *)malloc(sizeof(HashTable));
  
  // Aloca memorie pentru vectorul de pointeri la Element
  (*h)->elements = (Element **)malloc(size * sizeof(Element *));
  
  // Initializeaza fiecare element din vector cu valoarea NULL
  for (long i = 0; i < size; i++) {
    (*h)->elements[i] = NULL;
  }
  
  // Seteaza dimensiunea si functia de dispersie in structura HashTable
  (*h)->size = size;
  (*h)->hashFunction = f;
}

// Verificam sa vedem daca cheia se afla in tabela de dispersie
int exists(HashTable *hashTable, Key key) {
  // Calculeaza valoarea de dispersie pentru cheie
  long hashValue = hashTable->hashFunction(key, hashTable->size);
  
  // Obtine pointerul catre elementul corespunzator valorii de dispersie
  Element *current = hashTable->elements[hashValue];
  
  // Parcurge lista si verifica daca cheia exista
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      // Cheia a fost gasita in lista de elemente
      return 1; // Returneaza valoarea de adevar (1)
    }
    current = current->next;
  }
  
  // Cheia nu a fost gasita
  return 0;
}

//Intoarcem valoarea asociata unei chei din tabela de dispersie
Value get(HashTable *hashTable, Key key) {
  // Calculeaza valoarea de dispersie pentru cheie
  long hashValue = hashTable->hashFunction(key, hashTable->size);

  // Obtine pointerul catre elementul corespunzator valorii de dispersie
  Element *current = hashTable->elements[hashValue];

  // Parcurge lista si cauta cheia in elemente
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      // Cheia a fost gasita in lista de elemente
      return current->value; // Returneaza valoarea asociata cheii
    }
    current = current->next;
  }

  // Cheia nu a fost gasita
  return (Value)0;
}

// Asociem o valoare unei chei in tabela de dispersie
void put(HashTable *hashTable, Key key, Value value) {
  // Calculeaza valoarea de dispersie pentru cheie
  long hashValue = hashTable->hashFunction(key, hashTable->size);

  // Obtine pointerul catre elementul corespunzator valorii de dispersie
  Element *current = hashTable->elements[hashValue];
  Element *previous = NULL;

  // Parcurge lista si cauta cheia in elemente
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      // Cheia a fost gasita in lista de elemente
      current->value = value; // Suprascrie valoarea asociata cheii
      return;
    }
    previous = current;
    current = current->next;
  }

  // Cheia nu a fost gasita in lista de elemente
  // Adauga o noua intrare in tabela
  Element *newElement = (Element *)malloc(sizeof(Element));
  newElement->key = strdup(key); // Copiaza cheia intr-un nou sir
  newElement->value = value;
  newElement->next = NULL;

  if (previous != NULL) {
    // Adauga elementul la sfârsitul listei
    previous->next = newElement;
  } else {
    // Lista este goala, astfel incât elementul devine primul element
    hashTable->elements[hashValue] = newElement;
  }
}

// Stergem o intrare in tabela de dispersie
void deleteKey(HashTable *hashTable, Key key) {
    // Calculeaza valoarea de dispersie pentru cheie
  long hashValue = hashTable->hashFunction(key, hashTable->size);

  // Obtine pointerul catre elementul corespunzator valorii de dispersie
  Element *current = hashTable->elements[hashValue];
  Element *previous = NULL;

  // Parcurge lista si cauta cheia in elemente
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      // Cheia a fost gasita in lista de elemente
      if (previous != NULL) {
        // Cheia nu este primul element in lista
        previous->next = current->next;
      } else {
        // Cheia este primul element in lista
        hashTable->elements[hashValue] = current->next;
      }
      
      // Elibereaza memoria ocupata de cheie
      free(current->key);
      // Elibereaza memoria ocupata de element
      free(current);
      return;
    }
    
    previous = current;
    current = current->next;
  }
}

//Afisam tabela de dispersie (pentru fiecare cheie afisam lista de coliziuni)
void print(HashTable *hashTable) {
   for (long i = 0; i < hashTable->size; i++) {
    printf("Index %ld: ", i);
    Element *current = hashTable->elements[i];
    while (current != NULL) {
      printf("(%s, %d) ", current->key, current->value);
      current = current->next;
    }
    printf("\n");
  }
}

//Eliberam memoria pentru HashTable
void freeHashTable(HashTable *hashTable) {
   for (long i = 0; i < hashTable->size; i++) {
    Element *current = hashTable->elements[i];
    while (current != NULL) {
      Element *temp = current;
      current = current->next;
      free(temp->key);
      free(temp);
    }
  }
  free(hashTable->elements);
  free(hashTable);
}


long hash1(Key word, long size) {
  long h = 0;
  for (int i = 0; i < strlen(word); i++) {
    h = h * 17 + word[i];
  }
  return h % size;
}

int main(int argc, char* argv[]) {
  HashTable *hashTable;
  FILE *f1, *f2;
  char word[256];
  long hashSize, common = 0;

  hashSize = atoi(argv[1]);
  f1 = fopen(argv[2], "r");
  f2 = fopen(argv[3], "r");

  initHashTable(&hashTable, hashSize, &hash1);

  // Cerinta 3
  while (fscanf(f1, "%s", word) == 1) {
    put(hashTable, word, get(hashTable, word) + 1);
  }


  // Cerinta 4
  while (fscanf(f2, "%s", word) == 1) {
    if (get(hashTable, word) > 0) {
      common++;
      put(hashTable, word, get(hashTable, word) - 1);
    }
  }

  printf("Common words: %ld\n", common);

  fclose(f1);
  fclose(f2);
  freeHashTable(hashTable);
  return 0;
}
