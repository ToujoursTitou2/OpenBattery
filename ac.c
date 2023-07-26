#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

void type(){
  FILE *file = NULL;
  char c[SIZE];
  file = fopen("/sys/class/power_supply/AC/type", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("%s\n", c);
  fclose(file);
}

void online(){
  FILE *file = NULL;
  unsigned short i;
  file = fopen("/sys/class/power_supply/AC/online", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fscanf(file, "%hu", &i);
  if(i == 1){
    printf("connected\n");    
  }else if(i == 0){
    printf("disconnected\n");
  }else{
    printf("Error: invalid file content\n");
    fclose(file);
    exit(EXIT_FAILURE);
  }
  fclose(file);
}
