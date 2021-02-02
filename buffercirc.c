#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 40

typedef struct no {
  char pal[20];
  int urg;
  struct no *prox;
} Elem;

Elem *writePointer = NULL;
Elem *readPointer = NULL;

void startBuffer() {
  Elem *head = (Elem *) malloc(sizeof(Elem));
  Elem *node = (Elem *) malloc(sizeof(Elem));

  strcpy(node->pal, "/0");
  node->urg = 0;

  head = node;
  node->prox = head;

  for(int index = 1; index < BUFFER_SIZE; index++) {
    Elem *temporary = (Elem *) malloc(sizeof(Elem));

    strcpy(temporary->pal, "/0");
    temporary->urg = 0;

    temporary->prox = head->prox;
    head->prox = temporary;
    head = temporary;
  }

  writePointer = head->prox;
  readPointer = head->prox;
}

void insert(char *string, int urgency) {
  strcpy(writePointer->pal, string);
  writePointer->urg = urgency;

  writePointer = writePointer->prox;

}

void read(FILE *output) {
  char *readedWord;
  strcpy(readedWord, readPointer->pal);

  if(readPointer != writePointer) {
    if(strcmp(readedWord, "PRTY") == 0) {
      int urgency = readPointer->urg;

      for(int index = 0; index < urgency; index++) {
        if(readPointer->prox == writePointer)
          break;
        else
          readPointer = readPointer->prox;
      }
    }
    else
      readPointer = readPointer->prox;
    
    fprintf(output, "%s\n", readedWord);
  }
}

void processBuffer(FILE *input, FILE *output) {
  char string[20];
  int operation, urgency;

  while(fscanf(input, "%d %s %d", &operation, string, &urgency) != EOF) {
    if(strcmp(string, "NULL") == 0) {
      fclose(input);
      fclose(output);
      
      break;
    }

    else {
      if(operation == 0) {
        insert(string, urgency);
      }
      else if(operation == 1) {
        read(output);
      }
    }
  }
}

int main() {
  FILE *input = fopen("./pacotes.dat", "r");
  FILE *output = fopen("./lidos.dat", "w");

  Elem *buffer = NULL;

  startBuffer();

  processBuffer(input, output);

  return 0;
}