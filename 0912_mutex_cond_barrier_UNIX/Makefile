IN1=1.c
IN2=2.c
IN3=3.c
EX10=10.c
OUT1=1
OUT2=2
OUT3=3
OUT10=10

CC=gcc
FLAGS=-lpthread

all: T1 T2 T10 T3

T1: $(IN1)
	$(CC) -o $(OUT1) $(IN1) $(FLAGS)
	
T2: $(IN2)
	$(CC) -o $(OUT2) $(IN2) $(FLAGS)
	
T3: $(IN3)
	$(CC) -o $(OUT3) $(IN3) $(FLAGS)
	
T10: $(IN10)
	$(CC) -o $(OUT10) $(IN10) $(FLAGS)

.PHONY: all
