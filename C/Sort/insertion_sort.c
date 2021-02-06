#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int array[], int size);
void sort (int array[], int size);
void swap (int *left,   int *right);

int main(void){

  srand(time(0));

  int array[] = {

    (rand() % 100), (rand() % 100), (rand() % 100),
    (rand() % 100), (rand() % 100), (rand() % 100),
    (rand() % 100), (rand() % 100), (rand() % 100)

  };

  const int size = sizeof(array) / sizeof(int);

  sort(array, size);

  return 0;

}

void sort(int array[], int size){

  for(int right = 1; right < size; ++right){

    print(array, size);

    for(int left = right; left > 0 && array[left - 1] > array[left]; --left)

      swap(&array[left - 1], &array[left]);

  }

}

void print(int array[], int size){

  for(int i = 0; i < size; ++i)

    printf("%d ", array[i]);

  printf("\n");

}

void swap(int *left, int *right){

  int buffer;

  buffer = *left;
  *left = *right;
  *right = buffer;

}