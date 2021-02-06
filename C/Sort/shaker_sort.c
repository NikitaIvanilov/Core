#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int array[], int size);
void sort (int array[], int size);

void swap(int *array_left, int *array_right);

int main(void){

  srand(time(0));

  int array[] = {

    (rand() % 100), (rand() % 100), (rand() % 100),
    (rand() % 100), (rand() % 100), (rand() % 100),
    (rand() % 100), (rand() % 100), (rand() % 100)

  };

  const int size = sizeof(array) / sizeof(int);

  sort(array, size);

}

void sort(int array[], int size){

  for(int left = 0, right = size - 1; left <= right; ++left, --right){

    print(array, size);

    for(int i = right; i > left; --i)

      if(array[i - 1] > array[i])

        swap(&array[i - 1], &array[i]);

    for(int i = left; i < right; ++i)

      if(array[i + 1] < array[i])

        swap(&array[i + 1], &array[i]);

  }

}

void swap(int *array_left, int *array_right){

  int buff;

  buff = *array_right;
  *array_right = *array_left;
  *array_left = buff;

}

void print(int array[], int size){

  for(int i = 0; i < size; ++i)

    printf("%d ", array[i]);

  printf("\n");

}