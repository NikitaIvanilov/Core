#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print    (int array[], int size);
void sort     (int array[], int left, int right);
int  sort_part(int array[], int left, int right);
void swap     (int *left, int *right);

int main(void){

  srand(time(0));

  int array[] = {

    (rand() % 100), (rand() % 100), (rand() % 100),
    (rand() % 100), (rand() % 100), (rand() % 100),
    (rand() % 100), (rand() % 100), (rand() % 100),
    (rand() % 100), (rand() % 100), (rand() % 100)

  };

  const int size = sizeof(array) / sizeof(int);

  print(array, size);
  sort(array, 0, size - 1);
  print(array, size);

  return 0;

}

void sort(int array[], int left, int right){

  if(left < right){

    int pivot = sort_part(array, left, right);

    sort(array, left, pivot - 1);
    sort(array, pivot + 1, right);

  }

}

int sort_part(int array[], int left, int right){

  int pivot    = array[right],
      previous = left - 1,
      current  = left;

  while(current <= right - 1){

    if(array[current] < pivot){

      ++previous;
      swap(&array[previous], &array[current]);

    }

    ++current;

  }

  ++previous;

  swap(&array[previous], &array[right]);
  return previous;

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
