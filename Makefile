all: main

main: bin/bmp.o bin/main.o
	gcc -g bin/main.o bin/bmp.o -o main

bin/main.o: src/main.c include/bmp.h
	gcc -g -c src/main.c -Werror -Wall -std=c99 -o bin/main.o

bin/bmp.o: src/bmp.c include/bmp.h
	gcc -g -c src/bmp.c -Werror -Wall -std=c99 -o bin/bmp.o


clean:
	rm -rf bin/*.o main
