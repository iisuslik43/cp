#include "../include/phonebook.h"
#include "../include/names.h"
#include <stddef.h>
#include <expat.h>
#include <string.h>
#include <stdio.h>
#define BUFFER_SIZE 100000
human_t now_human;
phonebook_t *now_book;
int comp(const void *v1, const void *v2){
human_t h1=*((human_t*)v1);
human_t h2=*((human_t*)v2);
return strcmp(h1.family_name,h2.family_name);
}
void start_element(void *data, const char *element, const char **attribute) {
    int i = 0;
    if (attribute[0]) {
	human_t h;
	for(int i=0;i<10;i++)
		for(int j=0;j<21;j++)	
		h.phones[i][j]='\0';
	char* pch = strtok(attribute[1]," ");
	strcpy(h.name,pch);
	pch = strtok (NULL, " ");
	strcpy(h.middle_name,pch);
	pch = strtok (NULL, " ");
	strcpy(h.family_name,pch);
	now_human=h;
}
}

void end_element(void *data, const char *element) {
    if (strcmp(element,"human")==0){
	push_back_human(now_book, &now_human);
	now_human.name[0]='\0';
	now_human.middle_name[0]='\0';
	now_human.family_name[0]='\0';
	for(int i=0;i<10;i++)
		for(int j=0;j<21;j++)	
		now_human.phones[i][j]='\0';	
	
}
}

void handle_data(void *data, const char *content, int length) {
    int i=0;
    for(;i<10;i++){
	if(now_human.phones[i][0]=='\0')
	break;
    }
    strncpy(now_human.phones[i], content, length);
}

int parse_xml(char *buff, size_t buff_size,const char *filename) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    XML_Parser  parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);

    memset(buff, 0, buff_size);

    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), buff_size, fp);
        done = len < buff_size;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
            return 2;
        }
    } while (!done);

    XML_ParserFree(parser);
    fclose(fp);

    return 0;
}

int load_phonebook_xml(const char *filename, phonebook_t *book){
    int result;
    char buffer[BUFFER_SIZE];
    now_book=book;
    result = parse_xml(buffer, BUFFER_SIZE,filename);
    return 0;
}

int save_phonebook_xml(const char *filename, phonebook_t *book){
FILE *fp;
fp = fopen(filename,"w");
fprintf(fp,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
fprintf(fp,"%s","<phonebook>");
for(int i=0;i<book->size;i++){\
	fprintf(fp,"\t<human name=\"%s %s %s\">",book->humans[i].name,book->humans[i].middle_name,book->humans[i].family_name);
	for(int j=0;j<10&&book->humans[i].phones[j][0]>='0'&&book->humans[i].phones[j][0]<='9';j++){
	fprintf(fp,"\t\t<phone>%s</phone>",book->humans[i].phones[j]);	
	}
	fprintf(fp,"\t</human>");
}
fprintf(fp,"</phonebook>");
fclose(fp);
}

void print_phonebook(phonebook_t *book){
qsort(book->humans,book->size,sizeof(human_t),&comp);
printf("%o\n",book->size);
if(book->size==0)return;
for(size_t i=0;i<book->size;i++){
	printf("name: %s\nmiddle name: %s\nfamily name: %s\n",book->humans[i].name,book->humans[i].middle_name,book->humans[i].family_name);
	for(int j=0;j<10;j++){
		if(book->humans[i].phones[j][0]>='0'&&book->humans[i].phones[j][0]<='9'){
		printf("phone: %s\n",book->humans[i].phones[j]);
		}
	}
	printf("\n");	
}
}
void gen_phonebook(phonebook_t *book, size_t size){
srand(time(NULL));
for(size_t i=0;i<size;i++){
human_t h;
for(int i=0;i<10;i++)
		for(int j=0;j<21;j++)	
		h.phones[i][j]='\0';
strcpy(h.name,kNames[rand()%NAMES_CNT]);
strcpy(h.family_name,kFamilyNames[rand()%FAMILY_NAMES_CNT]);
strcpy(h.middle_name,kMiddleNames[rand()%MIDDLE_NAMES_CNT]);
int k =rand()%10;
for(int g=0;g<k;g++){
	int m=rand()%21;
	for(int j=0;j<m;j++)
	h.phones[g][j]='0'+(char)(rand()%9);
}
push_back_human(book, &h);
}
}

void clear_phonebook(phonebook_t *book){

free(book->humans);
book->capacity=0;
book->size=0;
}

human_t get_human(phonebook_t *book, char* family_name){
for(int i=0;i<book->size;i++){
if(strcmp(book->humans[i].family_name,family_name)==0)return book->humans[i];
}
return book->humans[0];
}

void push_back_human(phonebook_t *book, human_t *human){
if(book->size==book->capacity){
book->humans=realloc(book->humans,sizeof(human_t)*2*book->capacity);
book->capacity*=2;
}
book->humans[book->size]=*human;
book->size++;
}
