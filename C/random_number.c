#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_number(int start, int end);

int main(){

  srand(time(0));

  printf("%d\n", random_number(0,1));

  return 0;

}

int random_number(int start, int end){

  ++end;

  return (rand() % (end - start)) - start;

}
