CORES := $(shell nproc)

CFLAGS := -Wall -Wextra

all: battery

battery:
	gcc $(CFLAGS) battery.h battery.c -o battery -pthread -lm -O3 -march=native -mtune=native -fopenmp -DNUM_THREADS=$(CORES) 
	mv battery /usr/local/bin
