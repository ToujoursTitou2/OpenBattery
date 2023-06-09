battery:
	gcc battery.h battery.c inputscan.h inputscan.c -o battery
	mv battery /usr/local/bin
