CORES := $(shell nproc)

CFLAGS := -Wall -Wextra

all: battery

battery:
	gcc $(CFLAGS) main.h main.c bat.h bat.c ac.h ac.c -o battery -pthread -lm -O3 -march=native -mtune=native -fopenmp -DNUM_THREADS=$(CORES) 
	mv battery /usr/local/bin
