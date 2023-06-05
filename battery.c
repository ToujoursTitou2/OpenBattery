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
  printf("Battery v1.5\n");
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
    }else if(strcmp(input, "battery -vn") == 0){
      voltage_now();
    }else{
      printf("Unrecognized input: enter 'battery -h' for more informations.\n");
    }
  }
  free(input);
  return EXIT_SUCCESS;
}

void capacity(){
  FILE *file = NULL;
  char c[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/capacity", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("Battery capacity : %s%%\n", c);
  fclose(file);
}

void status(){
  FILE *file = NULL;
  char c[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/status", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("Battery status : %s\n", c);
  fclose(file);
}

void energy_full(){
  FILE *file = NULL;
  char c[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/energy_full", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("Battery full energy : %sµAh\n", c);
  fclose(file);
}

void energy_now(){
  FILE *file = NULL;
  char c[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/energy_now", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("Battery energy now : %sµAh\n", c);
  fclose(file);
}

void handleSignal(int signal){
  if(signal == SIGINT){
    printf("\nExiting...\n");
    exit(EXIT_SUCCESS);
  }
}

void technology(){
  FILE *file = NULL;
  char c[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/technology", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("Battery technology : %s\n", c);
  fclose(file);
}

void voltage_now(){
  FILE *file = NULL;
  char c[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/voltage_now", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("Battery voltage now : %s\n", c);
  fclose(file);
}

void type(){
  FILE *file = NULL;
  char c[SIZE];
  file = fopen("/sys/class/power_supply/AC/type", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("Battery adapter type : %s\n", c);
  fclose(file);
}
