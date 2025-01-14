main: dfa.o scanner.o main.o
	gcc -g dfa.o scanner.o main.o -o main

dfa.o: dfa.c
	gcc -c dfa.c

scanner.o: scanner.c
	gcc -c scanner.c

main.o: main.c
	gcc -c main.c

clean:
	rm *.o main