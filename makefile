SHELL := /bin/bash
CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c =.o)

RPS: $(OBJ)
	$(CC) -pie $^ -o $@

%.o: %.c $(wildcard *.h)
	$(CC) -fPIE -c $^ -o $@ 