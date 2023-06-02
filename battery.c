#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "battery.h"
#include "inputscan.h"

int main(){
  signal(SIGINT, handleSignal);
  char *input = NULL;
  input = malloc(sizeof(char));
  if(input == NULL){
    printf("Error: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  printf("Battery v1.4\n");
  while(1){
    printf(">> ");
    charScan(input, SIZE);
    if(strcmp(input, "battery -c") == 0){
      capacity();
    }else if(strcmp(input, "battery -s") == 0){
      status();
    }else if(strcmp(input, "battery -ef") == 0){
      energy_full();
    }else if(strcmp(input, "battery -en") == 0){
      energy_now();
    }else if(strcmp(input, "battery -h") == 0){
      printf("battery -c : battery capacity\n");
      printf("battery -s : battery status\n");
      printf("battery -ef : battery energy full\n");
      printf("battery -en : battery energy now\n");
      printf("battery -h : battery help\n");
    }else{
      printf("Unrecognized input: enter 'battery -h' for more informations.\n");
    }
  }
  free(input);//Toujours libérer la mémoire après un malloc
  return EXIT_SUCCESS;
}

void capacity(){
  FILE *file = NULL;
  char path[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/capacity", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(path, SIZE, file);
  printf("Battery capacity : %s%%\n", path);
  fclose(file);
}

void status(){
  FILE *file = NULL;
  char path[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/status", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(path, SIZE, file);
  printf("Battery status : %s\n", path);
  fclose(file);
}

void energy_full(){
  FILE *file = NULL;
  char path[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/energy_full", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(path, SIZE, file);
  printf("Battery full energy : %sµAh\n", path);
  fclose(file);
}

void energy_now(){
  FILE *file = NULL;
  char path[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/energy_now", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(path, SIZE, file);
  printf("Battery energy now : %sµAh\n", path);
  fclose(file);
}

void handleSignal(int signal){
  if(signal == SIGINT){
    printf("\nExiting...\n");
    exit(EXIT_SUCCESS);
  }
}
