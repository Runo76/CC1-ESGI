CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

SRC = main.c commands.c tree.c
OBJ = $(SRC:.c=.o)
TARGET = database

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /f /q $(OBJ) $(TARGET).exe
	