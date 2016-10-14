all: lab5

lab5: bin/clist.o bin/main.o bin/position.o
	gcc -g bin/clist.o bin/main.o bin/position.o -o lab5

bin/main.o: src/main.c include/clist.h include/position.h
	gcc -g -c src/main.c -o bin/main.o

bin/clist.o: src/clist.c include/clist.h
	gcc -g -c src/clist.c -o bin/clist.o

bin/position.o: src/position.c include/clist.h include/position.h
	gcc -g -c src/position.c -o bin/position.o

clean:
	rm -rf bin/*.o lab5
