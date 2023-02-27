# Makefile
# Duh!

# https://makefiletutorial.com/

# Flags and Stuff
CC = gcc
CFLAGS = -g -Wall
TARGET = dll_example 



all: $(TARGET)

$(TARGET): main.c vessel_node.o vessel.o
	$(CC) $(CFLAGS) $^ -o $@
#	$(CC) $(CFLAGS) main.c vessel_node.o vessel.o -o $@

#vessel_node.o: vessel_node.c
#	$(CC) $(CFLAGS) vessel_node.c vessel.o -o $@

vessel_node.o: vessel_node.c vessel.o
	$(CC) $(CFLAGS) $^ -o $@


vessel.o: vessel.c
	$(CC) $(CFLAGS) $^ -o $@
#	$(CC) $(CFLAGS) vessel.c -o $@

#install:

clean:
	rm -f *.o $(TARGET)

# ??
.PHONY: build clean