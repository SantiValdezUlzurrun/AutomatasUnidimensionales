CFLAGS=-g -std=gnu99 -Wall -Wconversion -Wtype-limits -pedantic
VFLAGS=--leak-check=full  --track-origins=yes --show-reachable=yes
TARGET=autocel

all:
ifeq ($(shell uname -m), mips64)
	gcc $(CFLAGS) -DUSE_MIPS -o $(TARGET) src/proximo.S src/automata.c src/main.c
else
	gcc $(CFLAGS) -o $(TARGET) src/automata.c src/main.c
endif

test: all
	$(shell tests/tests)

.PHONY : clean

clean:
	rm $(TARGET)
	rm test
	rm *.o
