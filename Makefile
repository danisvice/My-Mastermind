CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = my_mastermind.c 
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = my_mastermind

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS): %.o: %.c  
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean: 
	@rm -f $(OBJECTS)

fclean:
	@rm -f $(EXECUTABLE) $(OBJECTS)

re: fclean all 