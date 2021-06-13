#include <stdio.h>
#include <unistd.h>

int main(){

  printf("Thread sleep 1 second\n");
  sleep(1);
  printf("Done\n");

  return 0;

}
