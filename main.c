#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/bmp.h"

int main(int argc, char* argv[]){

struct bmp_file *rpic;
rpic = malloc(sizeof(struct bmp_file));
char* in=argv[2];
char* out=argv[3];
int x=atoi(argv[4]);
int y=atoi(argv[5]);
int w=atoi(argv[6]);
int h=atoi(argv[7]);
load_bmp(in,rpic);
int32_t width=rpic->iheader.width;
int32_t height=abs(rpic->iheader.height);
if(x+w>=width)w=width-x;
if(y+h>=height)h=height-y;
RGBTRIPLE** cpic=crop(rpic,x,y,w,h);
RGBTRIPLE** rotpic=rotate(cpic,w,h);
savebmp(out,rpic,rotpic,h,w);


return 0;

}
