#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/bmp.h"

void load_bmp(char* filename, struct bmp_file* rpic){

FILE *f = fopen(filename, "rb");

fread(&rpic->fheader,sizeof(struct file_header),1,f);
fread(&rpic->iheader,sizeof(struct info_header),1,f);

int32_t width=rpic->iheader.width;
int32_t height=abs(rpic->iheader.height);
int32_t numbo =(4-width%4)%4;
rpic->picture=malloc(sizeof(RGBTRIPLE*)*height);
RGBTRIPLE* buf=malloc(sizeof(RGBTRIPLE)*4);
for(int i=height-1;i>=0;i--){
	rpic->picture[i]=malloc(sizeof(RGBTRIPLE)*width);
	fread(rpic->picture[i],sizeof(RGBTRIPLE),width,f);
	if(numbo!=0)fread(buf,sizeof(RGBTRIPLE),numbo,f);
}
free(buf);
fclose(f);
}

RGBTRIPLE** crop(struct bmp_file* pic,int x,int y, int w,int h){
int32_t width=pic->iheader.width;
int32_t height=abs(pic->iheader.height);
RGBTRIPLE **croppic=malloc(sizeof(RGBTRIPLE*)*h);
for(int i=y;i<y+h&&i<height;i++){
	croppic[i-y]=malloc(sizeof(RGBTRIPLE*)*w);
	for(int j=x;j<x+w&&j<width;j++){
				
		croppic[i-y][j-x]=pic->picture[i][j];
		//RGBTRIPLE* a=&croppic[i-y][j-x];
		//RGBTRIPLE* b=&(pic->picture[i][j]);
		//a->red=b->red;
		//a->green=b->green;
		//a->blue=b->blue;
	}
}
for(int i=0;i<height;i++)free(pic->picture[i]);
free(pic->picture);
return croppic;
}

RGBTRIPLE **rotate(RGBTRIPLE** pic,int w,int h){
RGBTRIPLE **rotpic=malloc(sizeof(RGBTRIPLE*)*w);
for(int i=0;i<w;i++){
	rotpic[i]=malloc(sizeof(RGBTRIPLE*)*h);
	for(int j=0;j<h;j++){
				
		rotpic[i][j]=pic[h-j-1][i];
		//RGBTRIPLE* a=&rotpic[j][i];
		//RGBTRIPLE* b=&(pic[j][i]);
		//a->red=b->red;
		//a->green=b->green;
		//a->blue=b->blue;
	}
}
for(int i=0;i<h;i++)free(pic[i]);
free(pic);
return rotpic;

}

void savebmp(char* filename,struct bmp_file* bmp,RGBTRIPLE** pic,int w,int h){
FILE *sf = fopen(filename, "w");
bmp->iheader.height=h;
bmp->iheader.width=w;
size_t nullsize = (4-w%4)%4;
bmp->iheader.bitmap_data_size=(w+nullsize)*h*3;

fwrite(&bmp->fheader, sizeof(struct file_header), 1, sf);
fwrite(&bmp->iheader, sizeof(struct info_header),1,sf);
RGBTRIPLE tmp;
tmp.red=0;
tmp.blue=0;
tmp.green=0;

for(int i=h-1;i>=0;i--){
	fwrite(pic[i],sizeof(RGBTRIPLE),w,sf);
	if(nullsize)fwrite(&tmp,sizeof(RGBTRIPLE),nullsize,sf);
}
for(int i=0;i<h;i++)free(pic[i]);
free(pic);
free(bmp);
return;
}
