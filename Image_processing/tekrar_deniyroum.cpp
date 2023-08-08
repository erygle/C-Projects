#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#pragma pack(1)
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;

typedef struct _BMPFH{
    BYTE bftype1 ;
    BYTE bftype2 ;
    DWORD bfSize;
    WORD bfreserved1;
    WORD bfreserved2;
    DWORD bfOffBits;
}BMPFH;

typedef struct _BMPIH{
    DWORD biSize;
    LONG biw;
    LONG bih;
    WORD biplane;
    WORD bibitcount;
    DWORD biComp;
    DWORD biSizeImage;
    LONG bix;
    LONG biy;
    DWORD biclused;
    DWORD biclimp;
}BMPIH;

typedef struct _PALETTE{
    BYTE blue;
    BYTE green;
    BYTE red;
    BYTE reserved;
}PALETTE;

typedef struct _IMAGE{
    BMPFH bmpfh;
    BMPIH bmpih;
    PALETTE *palette;
    BYTE *data;
}IMAGE;

IMAGE *imageRead(IMAGE *image,char *filename){
    FILE *fp;
    DWORD r,size,rowsize;
    BMPFH bmpfh;
    BMPIH bmpih;

    fp = fopen(filename,"rb");
    if(fp == NULL)exit(1);

    fread(&bmpfh,sizeof(BMPFH),1,fp);
    if(bmpfh.bftype1 != 'B' || bmpfh.bftype2 != 'M')exit(1);
    fread(&bmpih,sizeof(BMPIH),1,fp);

    image = (IMAGE*)malloc(bmpfh.bfSize);
    if(image == NULL)exit(1);

    image->bmpfh = bmpfh;
    image->bmpih = bmpih;

    r=0;
    if(bmpih.bibitcount == 1)r=2;
    if(bmpih.bibitcount == 4)r=16;
    if(bmpih.bibitcount == 8)r=256;
    if(r!=0){
        image->palette = (PALETTE*)malloc(4*r);
        fread(image->palette,sizeof(BYTE),4*r,fp);
    }
    rowsize = (image->bmpih.biw * image->bmpih.bibitcount +31)/32*4;
    size = rowsize * image->bmpih.bih;

    image->data = (BYTE*)malloc(size);
    fread(image->data,size,1,fp);
    fclose(fp);
    return image;
}

void imageWrite(IMAGE *image,char *filename){
    FILE *fp;
    int r,rowsize,size;
    fp = fopen(filename,"wb");
    if(fp==NULL)exit(1);
    fwrite(&image->bmpfh,sizeof(BMPFH),1,fp);
    fwrite(&image->bmpih,sizeof(BMPIH),1,fp);

    r=0;
    if(image->bmpih.bibitcount == 1)r=2;
    if(image->bmpih.bibitcount == 4)r=16;
    if(image->bmpih.bibitcount == 8)r=256;
    if(r!=0)fwrite(image->palette,r*4,1,fp);

    rowsize = (image->bmpih.biw * image->bmpih.bibitcount +31)/32*4;
    size = rowsize * image->bmpih.bih;

    image->data=(BYTE*)malloc(size);
    fwrite(image->data,size,1,fp);
    fclose(fp);

}
void histogram(IMAGE *image){
    LONG rowsize,h,w;
    LONG hist[256] = {0};
    h = image->bmpih.bih;
    w = image->bmpih.biw;
    rowsize = (image->bmpih.bibitcount * image->bmpih.biw + 31)/32*4;
    
    LONG i,j;
    LONG size = rowsize * h;
    for(i=0 ; i<size ; i++){
        hist[image->data[i]]++;
    }
    for(i=0 ; i<256 ; i++)printf("%d : %d",i,hist[i]);
}

int main(int argc, char const *argv[])
{
    IMAGE *image;
    image = (IMAGE*)malloc(sizeof(IMAGE));
    image = imageRead(image,"biber2.bmp");
    imageWrite(image,"test3.bmp");
    histogram(image);
    free(image);
    return 0;
}
