CC=gcc
CFLAGS=-Wall -Werror -O3 -std=c99
# CFLAGS=-Wall -Werror -g -std=c99
LIBS=-pthread -lm
EXPR?=1

SOURCES=utils/*c main.c lock.c expr.c test.c counter.c parallel.c worker.c dispatcher.c queue.c result.c serial.c

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=lock

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS)

tune: clean $(EXECUTABLE)
	./$(EXECUTABLE) 64

test: clean $(EXECUTABLE)
	./$(EXECUTABLE) 1

run: clean $(EXECUTABLE)
	./$(EXECUTABLE) $(EXPR)

clean:
	rm -f $(EXECUTABLE) *.o *.tsv *.log
