#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <dirent.h>
#include "main.h"
#include "inputscan.h"

int main(){
    DIR *dir = opendir("/sys/class/power_supply");
    if(dir == NULL){
      printf("Error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL){
      if(strstr(entry->d_name, "BAT") != NULL){
	break;
      }
    }
    char *folderName = NULL;
    folderName = malloc(sizeof(char));
    if(folderName == NULL){
      printf("Error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    folderName = entry->d_name;  
    signal(SIGINT, handleSignal);
    char *input = NULL;
    input = malloc(sizeof(char));
    if(input == NULL){
      printf("Error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    printf("OpenBattery v2.5\n");
    while(1){
      printf(">> ");
      charScan(input, SIZE);
      if(strcmp(input, "battery -c") == 0){
	capacity(folderName);
      }else if(strcmp(input, "battery -s") == 0){
	status(folderName);
      }else if(strcmp(input, "battery -ef") == 0){
	energy_full(folderName);
      }else if(strcmp(input, "battery -en") == 0){
	energy_now(folderName);
      }else if(strcmp(input, "battery -h") == 0){
	help();
      }else if(strcmp(input, "battery -t") == 0){
	technology(folderName);
      }else if(strcmp(input, "battery -vn") == 0){
	voltage_now(folderName);
      }else if(strcmp(input, "battery -ty") == 0){
	type();
      }else if(strcmp(input, "battery -o") == 0){
	online();
      }else if(strcmp(input, "battery -sn") == 0){
	serial_number(folderName);
      }else if(strcmp(input, "battery -bq") == 0){
	battery_quantity();
      }else if(strcmp(input, "battery -cc") == 0){
	cycle_count(folderName);
      }else if(strcmp(input, "battery -m") == 0){
	manufacturer(folderName);
      }else if(strcmp(input, "battery -mn") == 0){
	model_name(folderName);
      }else if(strcmp(input, "battery -efd") == 0){
	energy_full_design(folderName);
      }else{
	printf("Unrecognized input: enter 'battery -' for more informations.\n");
      }
    }
    closedir(dir);
    free(folderName);
    free(input);
    return EXIT_SUCCESS;
}

void help(){  
  printf("battery -h : list of commands\n");
  printf("battery -c : current battery charge level in percentage\n");
  printf("battery -s : current state of the battery(charged, charging, discharging, etc...)\n");
  printf("battery -ef : total battery capacity\n");
  printf("battery -en : current battery capacity\n");
  printf("battery -t : type of technology used by the battery(ex : Li-ion, Li-pol, NiCd, etc...)\n");
  printf("battery -vn : current battery voltage\n");
  printf("battery -ty : battery adapter type\n");
  printf("battery -o : battery adapter is currently connected or not\n");
  printf("battery -sn : battery serial number\n");
  printf("battery -bq : quantity of batteries present on the system\n");
  printf("battery -cc : number of battery charge and discharge cycles\n");
  printf("battery -m : name of battery manufacturer\n");
  printf("battery -mn : battery model name\n");
  printf("battery -efd : total battery design capacity\n");
}

void capacity(char *folderName){
  const char *directory = "/sys/class/power_supply";
  const char *fileName = "capacity";
  char filePath[PATH_SIZE];
  snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
  FILE *file = NULL;
  unsigned short i;
  file = fopen(filePath, "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fscanf(file, "%hu", &i);
  printf("%hu%%\n", i);
  fclose(file);
}

void status(char *folderName){
  const char *directory = "/sys/class/power_supply";
  const char *fileName = "status";
  char filePath[PATH_SIZE];
  snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
  FILE *file = NULL;
  char c[SIZE];
  file = fopen(filePath, "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("%s\n", c);
  fclose(file);
}

void energy_full(char *folderName){
  const char *directory = "/sys/class/power_supply";
  const char *fileName = "energy_full";
  char filePath[PATH_SIZE];
  snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
  FILE *file = NULL;
  int i;
  file = fopen(filePath, "r");
  if(file == NULL){
    const char *fileName = "charge_full";
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
    file = fopen(filePath, "r");
    if(file == NULL){
      printf("Error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  fscanf(file,"%d", &i);
  printf("%d\n", i);
  fclose(file);
}

void energy_now(char *folderName){
  const char *directory = "/sys/class/power_supply";
  const char *fileName = "energy_now";
  char filePath[PATH_SIZE];
  snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
  FILE *file = NULL;
  int i;
  file = fopen(filePath, "r");
  if(file == NULL){
    const char *fileName = "charge_now";
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
    file = fopen(filePath, "r");
    if(file == NULL){
      printf("Error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  fscanf(file, "%d", &i);
  printf("%d\n", i);
  fclose(file);
}

void handleSignal(int signal){
  if(signal == SIGINT){
    printf("\nExiting...\n");
    exit(EXIT_SUCCESS);
  }
}

void technology(char *folderName){
  const char *directory = "/sys/class/power_supply";
  const char *fileName = "technology";
  char filePath[PATH_SIZE];
  snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
  FILE *file = NULL;
  char c[SIZE];
  file = fopen(filePath, "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("%s\n", c);
  fclose(file);
}

void voltage_now(char *folderName){
  const char *directory = "/sys/class/power_supply";
  const char *fileName = "voltage_now";
  char filePath[PATH_SIZE];
  snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
  FILE *file = NULL;
  int i;
  file = fopen(filePath, "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fscanf(file, "%d", &i);
  printf("%dmV\n", i);
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

void serial_number(char *folderName){
  const char *directory = "/sys/class/power_supply";
  const char *fileName = "serial_number";
  char filePath[PATH_SIZE];
  snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
  FILE *file = NULL;
  unsigned short i;
  file = fopen(filePath, "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fscanf(file, "%hu", &i);
  printf("%hu\n", i);
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

void cycle_count(char *folderName){
  const char *directory = "/sys/class/power_supply";
  const char *fileName = "cycle_count";
  char filePath[PATH_SIZE];
  snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
  FILE *file = NULL;
  unsigned short i;
  file = fopen(filePath, "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fscanf(file, "%hu", &i);
  printf("%hu\n", i);
  fclose(file);
}

void manufacturer(char *folderName){
  const char *directory = "/sys/class/power_supply";
  const char *fileName = "manufacturer";
  char filePath[PATH_SIZE];
  snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
  FILE *file = NULL;
  char c[SIZE];
  file = fopen(filePath, "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  fgets(c, SIZE, file);
  printf("%s\n", c);
  fclose(file);
}

void model_name(char *folderName){
  const char *directory = "/sys/class/power_supply";
  const char *fileName = "model_name";
  char filePath[PATH_SIZE];
  snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
  FILE *file = NULL;
  char c[SIZE];
  file = fopen(filePath, "r");
  if(file == NULL){
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE); 
  }
  fgets(c, SIZE, file);
  printf("%s\n", c);
  fclose(file);
}

void energy_full_design(char *folderName){
  const char *directory = "/sys/class/power_supply";
  const char *fileName = "energy_full_design";
  char filePath[PATH_SIZE];
  snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
  FILE *file = NULL;
  char c[SIZE];
  file = fopen(filePath, "r");
  if(file == NULL){
    const char *fileName = "charge_full_design";
    snprintf(filePath, sizeof(filePath), "%s/%s/%s", directory, folderName, fileName);
    file = fopen(filePath, "r");
    if(file == NULL){
      printf("Error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  fgets(c, SIZE, file);
  printf("%s\n", c);
  fclose(file);
}
