CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = mastermind.c game.c input.c output.c 
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = mastermind

