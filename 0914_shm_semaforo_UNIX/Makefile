IN4=4.c
IN5=5.c
IN6=6.c
IN7=7.c
OUT4=4
OUT5=5
OUT6=6
OUT7=7

CC=gcc
FLAGS=-lrt -pthread

all: T4 T5 T6 T7

T4: $(IN4)
	$(CC) -o $(OUT4) $(IN4) $(FLAGS)
	
T5: $(IN5)
	$(CC) -o $(OUT5) $(IN5) $(FLAGS)
	
T6: $(IN6)
	$(CC) -o $(OUT6) $(IN6) $(FLAGS)
	
T7: $(IN7)
	$(CC) -o $(OUT7) $(IN7) $(FLAGS)

.PHONY: all
