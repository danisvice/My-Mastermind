CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = mastermind.c 
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = mastermind

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS): %.o: %.c  
	$(CC) $(CFLAGS) -c $< -o $@ 

clean: 
	rm -f $(OBJECTS)

fclean:
	rm -f $(EXECUTABLE)

re: fclean all 