/*
Header file of the battery.c source file, which contains const & prototypes of functions
*/
#ifndef BATTERY_H
#define BATTERY_H

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
void handleSignal(int signal);

#endif
