#ifndef MAIN_H
#define MAIN_H

#define SIZE 15

void capacity();
void status();
void energy_full();
void energy_now();
void technology();
void voltage_now();
void type();
void online();
void serial_number();
unsigned short countElementsInFolder(const char *folderPath, const char *excludedName);
void battery_quantity();
void handleSignal(int signal);

#endif
