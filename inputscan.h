/*
Header file of inputscan.c but modified for the current project
*/

#ifndef INPUTSCAN_H
#define INPUTSCAN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void clearBuffer();
char charScan(unsigned char *input, int size);
int intScan();
double doubleScan();
#endif
