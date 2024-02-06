# Makefile for the project

# Compiler
CC = gcc

# Compiler flags
#CFLAGS = -Wall -Wextra -std=c11

# Source files
SRCS = $(wildcard *.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGETS = $(SRCS:.c=)

SQLITE_LIB = -lsqlite3

all: $(TARGETS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(SQLITE_LIB) 

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(SQLITE_LIB)

clean:
	rm -f $(OBJS) $(TARGET)

