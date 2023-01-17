CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = mastermind.c game.c input.c output.c 
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = mastermind

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
$(CC) $(CFLAGS) $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ 

clean: 
	rm -f $(OBJECTS)

flcean:
	rm -f $(EXECUTABLE)

re: fclean all 