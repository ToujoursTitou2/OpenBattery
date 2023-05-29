#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "battery.h"

int main(){
  FILE *file = NULL;
  char path[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/capacity", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  fgets(path, SIZE, file);
  fclose(file);
  printf("Battery percent : %s%%\n", path);
  return EXIT_SUCCESS;
}
