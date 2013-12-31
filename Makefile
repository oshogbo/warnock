CC=gcc
CFLAGS=-Wall -Wextra
TARGET=a.out
LIBS=-lm -lGL -lSDL

SRC=camera.c box.c coord.c plane.c

OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIBS)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
