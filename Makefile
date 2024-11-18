CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
SOURCES = main.c repl.c btree.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = database

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
