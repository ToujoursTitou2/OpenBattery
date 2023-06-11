#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearBuffer(){
  int c = 0;
  while(c != '\n' && c != EOF){
    c = getchar();
  }
}

char charScan(char *input, int size){
  if(fgets(input, size, stdin) != NULL){
    if(input[strlen(input) - 1] == '\n'){
      input[strlen(input) - 1] = '\0'; 
    }else{
      clearBuffer();
    }
  }else{
    clearBuffer();
    return EXIT_FAILURE;
  }
}

int intScan(){
  char input[100] = {0};
  if(charScan(input, 100)){
    return strtol(input, NULL, 10);
  }else{
    return EXIT_FAILURE;
  }
}

double doubleScan(){
  char input[100] = {0};
  if(charScan(input, 100)){
    return strtod(input, NULL);
  }else{
    return EXIT_FAILURE;
  }
}
