#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#pragma pack(1)

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;

typedef struct _BMPFH{
    BYTE bftype1 = 'B';
    BYTE bftype2 = 'M';
    DWORD bfsize;
    DWORD bfOffbits;
    WORD bfreserved1;
    WORD bfreserved2;
}BMPFH;

typedef struct _BMPIH{
    DWORD biSize;
    LONG biw;
    LONG bih;
    WORD biBitCount;
    DWORD biSizeImage;
    //-----------------------------------
    LONG bix;
    LONG biy;
    DWORD biComp;
    WORD biplane;
    DWORD biClused;
    DWORD biClimp;
}BMPIH;

typedef struct _PALETTE{
    BYTE red;
    BYTE green;
    BYTE blue;
    BYTE reserved;
}PALETTE;

typedef struct _IMAGE{
    BMPFH bmpfh;
    BMPIH bmpih;
    PALETTE *palette;
    BYTE *data;
}IMAGE;

IMAGE *imageRead(IMAGE *image,char *filename);
void imageWrite(IMAGE *image,char *filename);
void writeInfo(IMAGE *image,char *filename);
void setZero(IMAGE *image);

int main(int argc, char const *argv[])
{
    char *fname = "kelebek.bmp";
    /*IMAGE *image = (IMAGE*)malloc(sizeof(IMAGE));
    image = imageRead(image,fname);*/
    
    
    IMAGE *image = (IMAGE*)malloc(sizeof(IMAGE));
    image = imageRead(image,fname);
    //writeInfo(image,fname);
    imageWrite(image,"test3.bmp");
    return 0;
}

IMAGE *imageRead(IMAGE *image,char *filename){
    BMPFH bmpfh;
    BMPIH bmpih;
    FILE *fp;
    DWORD r,rowsize,size;

    fp=fopen(filename,"rb");
    
    if(fp==NULL)exit(1);
    
    fread(&bmpfh,sizeof(BMPFH),1,fp);

    if(bmpfh.bftype1 != 'B' || bmpfh.bftype2 != 'M')exit(1);

    fread(&bmpih,sizeof(BMPIH),1,fp);

    image = (IMAGE*)malloc(bmpfh.bfsize);
    if(image==NULL)exit(1);

    image->bmpfh = bmpfh;
    image->bmpih = bmpih;

    r=0;
    if(bmpih.biBitCount == 1)r=2;
    if(bmpih.biBitCount == 2)r=16;
    if(bmpih.biBitCount == 8)r=256;
    if(r!=0){
        image->palette = (PALETTE*)malloc(4*r);
        fread(image->palette,sizeof(BYTE),4*r,fp);
    }

    rowsize = (image->bmpih.biw * image->bmpih.biBitCount +31)/32*4;
    size = rowsize * image->bmpih.bih;

    image->data = (BYTE*)malloc(size);
    fread(image->data,size,1,fp);
        
    fclose(fp);
        
    return image;
    
}

void imageWrite(IMAGE *image,char *filename){
    FILE *fp;
    int r,rowsize,size;

    fp=fopen(filename,"wb");
    if(fp==NULL)exit(1);

    fwrite(&image->bmpfh,sizeof(BMPFH),1,fp);
    fwrite(&image->bmpih,sizeof(BMPIH),1,fp);

    r=0;
    if(image->bmpih.biBitCount==1)r=2;
    if(image->bmpih.biBitCount==4)r=16;
    if(image->bmpih.biBitCount==8)r=256;
    if(r!=0)fwrite(image->palette,4*r,1,fp);

    rowsize = (image->bmpih.biw * image->bmpih.biBitCount +31)/32*4;
    size = rowsize * image->bmpih.bih;

    fwrite(image->data,size,1,fp);
    printf("File succesfully write.");
    fclose(fp);
}
void setZero(IMAGE *image){
    int i ,rowsize, size;
    rowsize = (image->bmpih.biw * image->bmpih.biBitCount +31)/32*4;
    size = image->bmpih.bih*rowsize;
    for(i = 0 ; i<size ; i++){
        image->data[i]=0;
    }
}