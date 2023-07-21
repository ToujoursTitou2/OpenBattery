#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "common.h"

void capacity(char **bat, unsigned short numStrings){
  for(unsigned short i = 0; i < numStrings; i++){
    const char *directory = "/sys/class/power_supply";
    const char *fileName = "capacity";
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
    FILE *file = NULL;
    char c[SIZE];
    file = fopen(filePath, "r");
    if(file == NULL){
      continue;
    }
    fscanf(file, "%s", c);
    printf("Battery %s: %s%%\n", bat[i], c);
    fclose(file);
  }
}


void status(char **bat, unsigned short numStrings){
  for(unsigned short i = 0; i < numStrings; i++){
    const char *directory = "/sys/class/power_supply";
    const char *fileName = "status";
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
    FILE *file = NULL;
    char c[SIZE];
    file = fopen(filePath, "r");
    if(file == NULL){
      continue;
    }
    fscanf(file, "%s", c);
    printf("Battery %s: %s\n", bat[i], c);
    fclose(file);
  }
}

void energy_full(char **bat, unsigned short numStrings){
  for(unsigned short i = 0; i < numStrings; i++){
    const char *directory = "/sys/class/power_supply";
    const char *fileName = "energy_full";
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
    FILE *file = NULL;
    int c;
    file = fopen(filePath, "r");
    if(file == NULL){
      const char *fileName = "charge_full";
      snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
      file = fopen(filePath, "r");
      if(file == NULL){
	continue;
      }
    }
    fscanf(file,"%d", &c);
    printf("Battery %s: %d\n", bat[i], c);
    fclose(file);
  }
}

void energy_now(char **bat, unsigned short numStrings){
  for(unsigned short i = 0; i < numStrings; i++){
    const char *directory = "/sys/class/power_supply";
    const char *fileName = "energy_now";
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
    FILE *file = NULL;
    int c;
    file = fopen(filePath, "r");
    if(file == NULL){
      const char *fileName = "charge_now";
      snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
      file = fopen(filePath, "r");
      if(file == NULL){
	continue;
      }
    }
    fscanf(file, "%d", &c);
    printf("Battery %s: %d\n", bat[i], c);
    fclose(file);
  }
}

void technology(char **bat, unsigned short numStrings){
  for(unsigned short i = 0; i < numStrings; i++){
    const char *directory = "/sys/class/power_supply";
    const char *fileName = "technology";
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
    FILE *file = NULL;
    char c[SIZE];
    file = fopen(filePath, "r");
    if(file == NULL){
      continue;
    }
    fgets(c, SIZE, file);
    printf("Battery %s: %s\n", bat[i], c);
    fclose(file);
  }
}

void voltage_now(char **bat, unsigned short numStrings){
  for(unsigned short i = 0; i < numStrings; i++){
    const char *directory = "/sys/class/power_supply";
    const char *fileName = "voltage_now";
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
    FILE *file = NULL;
    int c;
    file = fopen(filePath, "r");
    if(file == NULL){
      continue;
    }
    fscanf(file, "%d", &c);
    printf("Battery %s: %dmV\n", bat[i], c);
    fclose(file);
  }
}

void serial_number(char **bat, unsigned short numStrings){
  for(unsigned short i = 0; i < numStrings; i++){
    const char *directory = "/sys/class/power_supply";
    const char *fileName = "serial_number";
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
    FILE *file = NULL;
    unsigned short c;
    file = fopen(filePath, "r");
    if(file == NULL){
      continue;
    }
    fscanf(file, "%hu", &c);
    printf("Battery %s: %hu\n", bat[i], c);
    fclose(file);
  }
}

void cycle_count(char **bat, unsigned short numStrings){
  for(unsigned short i = 0; i < numStrings; i++){
    const char *directory = "/sys/class/power_supply";
    const char *fileName = "cycle_count";
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
    FILE *file = NULL;
    unsigned short c;
    file = fopen(filePath, "r");
    if(file == NULL){
      continue;
    }
    fscanf(file, "%hu", &c);
    printf("Battery %s: %hu\n", bat[i], c);
    fclose(file);
  }
}

void manufacturer(char **bat, unsigned short numStrings){
  for(unsigned short i = 0; i < numStrings; i++){
    const char *directory = "/sys/class/power_supply";
    const char *fileName = "manufacturer";
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
    FILE *file = NULL;
    char c[SIZE];
    file = fopen(filePath, "r");
    if(file == NULL){
      continue;
    }
    fgets(c, SIZE, file);
    printf("Battery %s: %s\n", bat[i], c);
    fclose(file);
  }
}

void model_name(char **bat, unsigned short numStrings){
  for(unsigned short i = 0; i < numStrings; i++){
    const char *directory = "/sys/class/power_supply";
    const char *fileName = "model_name";
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
    FILE *file = NULL;
    char c[SIZE];
    file = fopen(filePath, "r");
    if(file == NULL){
      continue;
    }
    fgets(c, SIZE, file);
    printf("Battery %s: %s\n", bat[i], c);
    fclose(file);
  }
}

void energy_full_design(char **bat, unsigned short numStrings){
  for(unsigned short i = 0; i < numStrings; i++){
    const char *directory = "/sys/class/power_supply";
    const char *fileName = "energy_full_design";
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
    FILE *file = NULL;
    char c[SIZE];
    file = fopen(filePath, "r");
    if(file == NULL){
      const char *fileName = "charge_full_design";
      snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
      file = fopen(filePath, "r");
      if(file == NULL){
	continue;
      }
    }
    fgets(c, SIZE, file);
    printf("Battery %s: %s\n", bat[i], c);
    fclose(file);
  }
}

void voltage_min_design(char **bat, unsigned short numStrings){
  for(unsigned short i = 0; i < numStrings; i++){
    const char *directory = "/sys/class/power_supply";
    const char *fileName = "voltage_min_design";
    char filePath[PATH_MAX];
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, bat[i], fileName);
    FILE *file = NULL;
    char c[SIZE];
    file = fopen(filePath, "r");
    if(file == NULL){
      continue;
    }
    fgets(c, SIZE, file);
    printf("Battery %s: %s\n", bat[i], c);
    fclose(file);
  }
}
