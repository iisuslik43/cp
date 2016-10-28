#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/phonebook.h"


int main(int argc, char* argv[]){
srand(time(NULL));
phonebook_t book;
book.humans=malloc(sizeof(human_t)*43);
book.size=0;
book.capacity=43;
load_phonebook_xml(argv[1],&book);


print_phonebook(&book);

clear_phonebook(&book);



size_t ss=(size_t)rand()%10;

book.humans=malloc(sizeof(human_t)*ss);
book.size=0;
book.capacity=ss;
gen_phonebook(&book,ss);

save_phonebook_xml(argv[2],&book);

clear_phonebook(&book);

}
