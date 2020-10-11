/*

  How to get variable name?

*/

#include <stdio.h>

#define VAR_NAME(var) #var

int main(void){

  int num = 10;

  printf("%s\n", VAR_NAME(num));

  return 0;

}