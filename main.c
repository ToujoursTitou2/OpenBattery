#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <dirent.h>
#include "main.h"
#include "inputscan.h"

int main(){
  signal(SIGINT, handleSignal);
  char *input = NULL;
  input = malloc(sizeof(char));
  if(input == NULL){
    printf("Error: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  printf("OpenBattery v2.0\n");
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
      printf("battery -h : list of commands\n");
      printf("battery -c : current battery charge level in percentage\n");
      printf("battery -s : current state of the battery(charged, charging, discharging, etc...)\n");
      printf("battery -ef : total battery capacity in microampere-hours(µAh)\n");
      printf("battery -en : current battery capacity in microampere-hours(µAh)\n");
      printf("battery -t : type of technology used by the battery(ex : Li-ion, Li-pol, NiCd, etc...)\n");
      printf("battery -vn : current battery voltage\n");
      printf("battery -ty : battery adapter type\n");
      printf("battery -o : battery adapter is currently connected or not\n");
      printf("battery -sn : battery serial number\n");
      printf("battery -bq : quantity of batteries present on the system\n");
    }else if(strcmp(input, "battery -t") == 0){
      technology();
    }else if(strcmp(input, "battery -vn") == 0){
      voltage_now();
    }else if(strcmp(input, "battery -ty") == 0){
      type();
    }else if(strcmp(input, "battery -o") == 0){
      online();
    }else if(strcmp(input, "battery -sn") == 0){
      serial_number();
    }else if(strcmp(input, "battery -bq") == 0){
      battery_quantity();
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
  printf("%s%%\n", c);
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
  printf("%s\n", c);
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
  printf("%sµAh\n", c);
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
  printf("%sµAh\n", c);
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
  printf("%s\n", c);
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
  printf("%smV\n", c);
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

void serial_number(){
  FILE *file = NULL;
  char c[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/serial_number", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("%s\n", c);
  fclose(file);
}

void battery_quantity(){
  const char *folderPath = "/sys/class/power_supply";
  unsigned short elementCount;
  elementCount = countElementsInFolder(folderPath, "AC");
  if(elementCount >= 0){
    printf("%hu\n", elementCount);
  }
}

unsigned short countElementsInFolder(const char *folderPath, const char *excludedName){
  DIR *directory;
  struct dirent *entry;
  unsigned short count = 0;
  directory = opendir(folderPath);
  if(directory == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  while((entry = readdir(directory)) != NULL){
    if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, excludedName) != 0){
      count++;
    }
  }
  closedir(directory);
  return count;
}

void cycle_count(){
  FILE *file = NULL;
  char c[SIZE];
  file = fopen("/sys/class/power_supply/BAT1/cycle_count", "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("%s\n", c);
  fclose(file);
}
