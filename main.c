#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include "main.h"
#include "bat.h"
#include "ac.h"

int main(int argc, char *argv[]){
  char *bat[]= {
    "BAT0",
    "BAT1",
    "BAT2",
    "BAT3"
  };
  unsigned short  numStrings = sizeof(bat) / sizeof(bat[0]);
  if(argc > 1){
    for(unsigned short i = 1; i < argc; i++){
      if(strcmp(argv[i], "-h") == 0){
	help();
      }else if(strcmp(argv[i], "-c") == 0){
	capacity(bat, numStrings);
      }else if(strcmp(argv[i], "-s") == 0){
	status(bat, numStrings);
      }else if(strcmp(argv[i], "-ef") == 0){
	energy_full(bat, numStrings);
      }else if(strcmp(argv[i], "-en") == 0){
	energy_now(bat, numStrings);
      }else if(strcmp(argv[i], "-t") == 0){
	technology(bat, numStrings);
      }else if(strcmp(argv[i], "-vn") == 0){
	voltage_now(bat, numStrings);
      }else if(strcmp(argv[i], "-ty") == 0){
	type();
      }else if(strcmp(argv[i], "-o") == 0){
	online();
      }else if(strcmp(argv[i], "-sn") == 0){
	serial_number(bat, numStrings);
      }else if(strcmp(argv[i], "-bq") == 0){
	battery_quantity();
      }else if(strcmp(argv[i], "-cc") == 0){
	cycle_count(bat, numStrings);
      }else if(strcmp(argv[i], "-m") == 0){
	manufacturer(bat, numStrings);
      }else if(strcmp(argv[i], "-mn") == 0){
	model_name(bat, numStrings);
      }else if(strcmp(argv[i], "-efd") == 0){
	energy_full_design(bat, numStrings);
      }else if(strcmp(argv[i], "-vmd") == 0){
	voltage_min_design(bat, numStrings);
      }else if(strcmp(argv[i], "-v") == 0){
	version();
      }else{
	printf("OpenBattery: %s: unrecognized command\n", argv[1]);
      }
    }
  }else{
    printf("Usage: battery [arg]\n");
  }
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
  printf("battery -vmd : minimum voltage recommended by the manufacturer for optimal battery operation\n");
  printf("battery -v : openbattery current version\n");
}

void battery_quantity(){
  const char *folderPath = "/sys/class/power_supply";
  unsigned short elementCount;

  elementCount = countElementsInFolder(folderPath, "AC");
  printf("%hu\n", elementCount);
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

void version(){
  printf("%s\n", VERSION);
}
