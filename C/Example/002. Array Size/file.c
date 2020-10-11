
/*

  How to get array size?

*/

#include <stdio.h>

int main(void){

  int array[123];

  size_t

    method_one = sizeof(array) / sizeof(int),
    method_two = sizeof(array) / sizeof(array[0]);

  printf("m1: %d\nm2: %d\n",

    method_one,
    method_two

  );

  return 0;

}