CC = gcc
CFLAGS = -pthread -Wall
TARGET = corrida_carros

all: $(TARGET)

$(TARGET): corrida_carros.c
	$(CC) $(CFLAGS) -o $(TARGET) corrida_carros.c

clean:
	rm -f $(TARGET)