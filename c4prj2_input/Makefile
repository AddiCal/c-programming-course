CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
PROGRAM=pokerTest

$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) -o $(PROGRAM) $(OBJS)

%.o: %.c 
	gcc -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~

cards.o: cards.h
deck.o: deck.h
eval.o: eval.h
main.o: cards.h
main.o: deck.h
main.o: eval.h
main.o: future.h
