IN=main.c tbanc.c utils.c
OUT=tbanc
CC=gcc
FLAGS=-lrt -pthread -lm -fmax-errors=3

all: TBANC

TBANC: $(IN)
	$(CC) -o $(OUT) -g $(IN) $(FLAGS)
	
.PHONY: all
