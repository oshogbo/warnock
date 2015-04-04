CC=gcc
CFLAGS=-Wall -Wextra
TARGET=warnock.out
LIBS=-lm -lGL -lSDL

SRC=camera.c box.c coord.c surface.c

OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIBS)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
