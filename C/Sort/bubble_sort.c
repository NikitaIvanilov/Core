#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int array[], int size);
void sort (int array[], int size);

int main(void){

  srand(time(0));

  int array[] = {

    (rand() % 100), (rand() % 100), (rand() % 100),
    (rand() % 100), (rand() % 100), (rand() % 100),
    (rand() % 100), (rand() % 100), (rand() % 100)

  };

  const int size = sizeof(array) / sizeof(int);

  sort (array, size);

  return 0;

}

void sort(int array[], int size){

  for(int i = 0, buff; i + 1 < size; ++i){

    if(array[i + 1] < array[i]){

      buff = array[i + 1];
      array[i + 1] = array[i];
      array[i] = buff;

      i = -1;

      print(array, size);

    }

  }

}

void print(int array[], int size){

  for(int i = 0; i < size; ++i)

    printf("%d ", array[i]);

  printf("\n");

}
