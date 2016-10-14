#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/position.h"
#include "../include/clist.h"


void print_node(intrusive_node *node,void* fmt1) {
    char* fmt= fmt1;
    position_node *pnode = get_position(node);
    printf(fmt,pnode->x,pnode->y);
}


void for_count(intrusive_node *node,void* a) {
    int* b=a;
    *b=*b+1;
}



void apply(intrusive_list *l, void (*op)(intrusive_node*, void*), void* x){
    	intrusive_node *head = &l->head;
    	intrusive_node *node = head->next;

    	for (; node != head->prev; node = node->next){
	op(node,x);
	
}
        

}


int main(int argc, char* argv[]){
intrusive_list list;
intrusive_list* l = &list;
init_list(l);

if(strcmp(argv[1],"loadtext")==0){
	FILE *f = fopen(argv[2], "r");
	while(!feof(f)){
		int a,b;
		fscanf(f, "%d %d", &a,&b);		
        	add_position(l, a, b);		
		}
	fclose(f);
	}


if(strcmp(argv[1],"loadbin")==0){
	FILE *f = fopen(argv[2], "rb");	
	while(!feof(f)){
		char buf[6];
		fread(buf,sizeof(char),6,f);
		int x=0;
		int y=0;
		char* xc=(char*)&x;
		char* yc=(char*)&y;
		*(xc)=buf[0];
		*(xc+1)=buf[1];
		*(xc+2)=buf[2];
		*(yc)=buf[3];
		*(yc+1)=buf[4];
		*(yc+2)=buf[5];
		add_position(l, x, y);
		}
	fclose(f);
	}


for(int i=3;i<argc;i++){
if(strcmp(argv[i],"savetext")==0){
	FILE *sf = fopen(argv[i+1], "w");
	
	intrusive_node *head = &l->head;
        intrusive_node *node = head->next;
        for (; node != head->prev; node = node->next) {
        position_node *pnode = get_position(node);
	fprintf(sf,"%d %d\n",pnode->x,pnode->y);
        }
	fclose(sf);
	i++;
	}


if(strcmp(argv[i],"savebin")==0){
	FILE *sf = fopen(argv[i+1], "w");
	
	intrusive_node *head = &l->head;
        intrusive_node *node = head->next;
        for (; node != head->prev; node = node->next) {
        position_node *pnode = get_position(node);
	char* x1=(char*)&(pnode->x);
	char* y1=(char*)&(pnode->y);
        fwrite(x1, sizeof(char), 3, sf);
	fwrite(y1, sizeof(char), 3, sf);
	}
	fclose(sf);
	i++;
	}
	


if(strcmp(argv[i],"count")==0){
	int c=0;
	apply(l,&for_count,&c);
	printf("%d\n",c);
	}


if(strcmp(argv[i],"print")==0){
	char* fmt=argv[++i];
	apply(l,&print_node,fmt);
	}	    
}
remove_all(l);
}
