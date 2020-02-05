edit: lab.o linkedlist.o
	cc -o wordfreak lab.o linkedlist.o

linkedlist.o: linkedlist.o linkedlist.c
	cc -c linkedlist.c

lab.o: lab.c linkedlist.h
	cc -c lab.c

clean:
	rm wordfreak lab.o linkedlist.o