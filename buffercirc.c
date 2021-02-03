#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 40

typedef struct no {
  char pal[20];
  int urg;
  struct no *prox;
} Elem;


// Pointers responsible by iterate the circular list, writing and reading elements.
Elem *writePointer = NULL;
Elem *readPointer = NULL;


/**
  * Function that initialize the buffer with 40 empty positions
  * and set the initial position of the writePointer and readPointer.
*/
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


/**
  * Function that free the occupied memory space by the buffer.
*/
void deleteBuffer() {
  Elem *currentElement = writePointer;
  Elem *nextElement;

  for(int index = 0; index < BUFFER_SIZE; index++) {
    nextElement = currentElement->prox;

    free(currentElement);
    
    currentElement = nextElement;
  }
}


/**
  * Function that handle the insert operation of an element from buffer.
  * 
  * @param char[] string: string of readed pack.
  * @param int urgency: urgency of readed pack.
*/
void insert(char *string, int urgency) {
  strcpy(writePointer->pal, string);
  writePointer->urg = urgency;

  writePointer = writePointer->prox;
}


/**
  * Function that handle the read operation of an element from buffer.
  * 
  * @param FILE output: pointer to the output file.
*/
void read(FILE *output) {
  // If the readPoiter and writePoiter are in the same position, there's no elements to be readed.
  if(readPointer != writePointer) {
    char *readedWord;
    
    strcpy(readedWord, readPointer->pal);
    strcpy(readPointer->pal, "/0");
  
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


/**
  * Function that process the readed input using the circular buffer. 
  * 
  * @param FILE input: pointer to the input file.
  * @param FILE output: pointer to the output file.
*/
void process(FILE *input, FILE *output) {
  char string[20];
  int operation, urgency;

  while(fscanf(input, "%d %s %d", &operation, string, &urgency) != EOF) {
    if(strcmp(string, "NULL") == 0) {
      fclose(input);
      fclose(output);

      deleteBuffer();
      
      break;
    }

    else {
      if(operation == 0)
        insert(string, urgency);
    
      else if(operation == 1)
        read(output);
    }
  }
}

int main() {
  FILE *input = fopen("./pacotes.dat", "r");
  FILE *output = fopen("./lidos.dat", "w");

  startBuffer();

  process(input, output);

  return 0;
}