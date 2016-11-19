#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



struct file_header {
 char magic[2];              // 'B' 'M'
 int32_t file_size;
 int16_t reserved[2];
 int32_t offset;            // offset to bitmap data, relative to start of file
}__attribute__((packed));


struct info_header {
 int32_t header_size;                // 40
 int32_t width;
 int32_t height;                     // if height > 0 then bitmap data is upside down (i.e. last scanline first)
                                     // else height = abs(height) and bitmap data is ordered normally
 int16_t planes;                     // 1
 int16_t bits_per_pixel;             // must be 0 (bpp is implied by embedded JPEG or PNG image), 1, 4, 8, 16, 24 or 32
 int32_t compression;                // 0 = uncompressed, 1 = RLE8, 2 = RLE4, 3 = bitfields, 4 = JPEG, 5 = PNG
 int32_t bitmap_data_size;
 int32_t hor_pixels_per_meter;
 int32_t vert_pixels_per_meter;
 int32_t number_of_colors;           // only relevant for bits_per_pixel < 16; if set to zero, it's assumed to be 2^bits_per_pixel
 int32_t number_of_important_colors; // 0 means all colors are important
}__attribute__((packed));

typedef struct {
 uint8_t blue;
 uint8_t green;
 uint8_t red;
} RGBTRIPLE;

struct bmp_file{
struct file_header fheader;
struct info_header iheader;
RGBTRIPLE** picture;

}__attribute__((packed));

void load_bmp(char *filename,struct bmp_file *rpic);
RGBTRIPLE** crop(struct bmp_file* pic,int x,int y, int w,int h);
RGBTRIPLE **rotate(RGBTRIPLE** pic,int w,int h);
void savebmp(char* filename,struct bmp_file* bmp,RGBTRIPLE** pic,int h,int w);
