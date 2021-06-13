#include <stdio.h>

#define MAX_RANGE 32

void fibonacci(long unsigned int *current,
               long unsigned int *next);

int main(void){

  long unsigned int number_current = 0,
                    number_next    = 1;

  for(int range = 0; range < MAX_RANGE; ++range){

    fibonacci(&number_current, &number_next);
    printf("%-8d\n", number_current);

  }

  return 0;

}

void fibonacci(long unsigned int *current,
               long unsigned int *next)
{

  long unsigned int temp = (*current) + (*next);

  *current = *next;
  *next    = temp;

}
