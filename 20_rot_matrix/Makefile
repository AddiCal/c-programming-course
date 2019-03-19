rotate-matrix: rotate.o read-matrix.o
	gcc -o rotate-matrix rotate.o read-matrix.o
rotate: rotate.c
	gcc -o rotate -Wall -Werror -pedantic -std=gnu99 -ggdb3 rotate.c

.PHONY: clean

clean:
	rm -f rotate *.o *.c~ *.h~
