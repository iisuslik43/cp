all: lab6

lab6: bin/phonebook.o bin/main.o
	gcc -g bin/phonebook.o bin/main.o -o lab6 -lexpat 

bin/main.o: src/main.c include/phonebook.h
	gcc -g -c src/main.c -o bin/main.o -lexpat 

bin/phonebook.o: src/phonebook.c include/phonebook.h include/names.h
	gcc -g -c src/phonebook.c -o bin/phonebook.o -lexpat

clean:
	rm -rf bin/*.o lab6

