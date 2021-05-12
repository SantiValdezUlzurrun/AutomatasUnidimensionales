CFLAGS=-g -O0 -std=c99 -Wall -Wconversion -Wtype-limits -pedantic
VFLAGS=--leak-check=full  --track-origins=yes --show-reachable=yes
TARGET=autocel

all:
	gcc $(CFLAGS) -o $(TARGET) src/main.c

test: compilar-test
	./test

compilar-test:
	gcc $(CFLAGS) -o test tests/test.c tests/tester.c


.PHONY : clean

clean:
	rm $(TARGET)
	rm test
	rm *.o
