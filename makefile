CC = gcc
CFLAGS = -std=gnu99 -Wall -Wimplicit-function-declaration -Wno-int-to-pointer-cast -Wimplicit-function-declaration -g -I.
DEPS = flop.h
OBJ = main.c flop.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run:
	./main

.PHONY: clean
clean:
	rm -f *.o *~ main
