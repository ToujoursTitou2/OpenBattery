#ifndef MAIN_H
#define MAIN_H

#define SIZE 15
#define PATH_SIZE 50

void help();
void capacity(char *folderName);
void status(char *folderName);
void energy_full(char *folderName);
void energy_now(char *folderName);
void technology(char *folderName);
void voltage_now(char *folderName);
void type();
void online();
void serial_number(char *folderName);
unsigned short countElementsInFolder(const char *folderPath, const char *excludedName);
void battery_quantity();
void cycle_count(char *folderName);
void manufacturer(char *folderName);
void model_name(char *folderName);
void energy_full_design(char *folderName);
void voltage_min_design(char *folderName);
void handleSignal(int signal);

#endif
