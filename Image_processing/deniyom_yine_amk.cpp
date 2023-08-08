#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#pragma pack(1)
typedef unsigned char BYTE;//1 bytes of memory
typedef unsigned short WORD;//2 bytes of memory
typedef unsigned int DWORD;//4 bytes of memory
typedef int LONG;//4 bytes of memory
typedef struct _BMPFH//takes 14 bytes of memory
{
	BYTE bftype1;//1 byte and must be 'B'
	BYTE bftype2;//1 byte and must be 'M'
	DWORD bfsize;//4 bytes gives us the all size of bmp file (including headers,palette (if it has) data)
	WORD bfreserved1;// 2 btyes of memory could be set as 0
	WORD bfreserved2;// 2 btyes of memory could be set as 0
	DWORD bfOffbits;//4 bytes of memeory gives the position of data starts in the bmp file
} BMPFH;
typedef struct _BMPIH//40 bytes for windows bitmap file
{
	DWORD biSize;//4 bytes and it gives the size of info header
	LONG  biw;//4 bytes and it is the biw of image
	LONG bih;//4 bytes and it is the height of iimage
	WORD biplane;//2 bytes which is not important for us
	WORD bibitcount;//2 bytes it is about the type of bitmap file if it is 1 2 color, 4 (16 colors) ..
	DWORD biComp;//4 bytes not important
	DWORD bisizeimage;//4 bytes and it gives the size of data in the image 
	LONG bix;//4 bytes not importatnt
	LONG biy;//4 bytes not important
	DWORD biclused;//4 bytes not important
 	DWORD biclimp;//4 byets not importatnt for us
} BMPIH;
typedef struct _PALETTE//in palette it describes colors (what is the color number)
{
	BYTE blue;//blue commponent
	BYTE green;//green component
	BYTE red;//red component
	BYTE reserved;//reserved byte the user can use this for therir aims
} PALETTE;
typedef struct _IMAGE
{
	BMPFH   bmpfh;
	BMPIH   bmpih;
	PALETTE   *palette;
	BYTE    *data;
}  IMAGE;

IMAGE *imageRead(IMAGE *image,char *filename){
    BMPFH bmpfh;
    BMPIH bmpih;
    FILE *fp;
    DWORD r,size,rowsize;

    fp=fopen(filename,"rb");
    if(fp==NULL)exit(1);

    fread(&bmpfh,sizeof(BMPFH),1,fp);
    if(bmpfh.bftype1 != 'B' || bmpfh.bftype2 != 'M'){
        exit(1);
    }
    fread(&bmpih,sizeof(BMPIH),1,fp);
    image=(IMAGE*) malloc(bmpfh.bfsize);//allocates memory for image
	if(image==NULL) {printf("There is no enough memory for this operation");exit(1);}
	image->bmpfh=bmpfh;//sets bmpfh to image 
	image->bmpih=bmpih;

    r=0;//r is set to 0 in case 24 bits per pixel or more (this kind of images does not have color palette)
    if(bmpih.bibitcount==1) r=2;//if the image 1 bit per pixel (the number of clor is 2)
	if(bmpih.bibitcount==4) r=16;//if the image 4 bits per pixel (the number of clor is 16)
	if(bmpih.bibitcount==8) r=256;////if the image 8 bits per pixel (the number of clor is 256)
	if(r!=0){
        image->palette=(PALETTE *)malloc(4*r);//allocate memory for color palette
		fread(image->palette,sizeof(BYTE),4*r,fp);//read color palette from image to the memory
    }
    rowsize = (image->bmpih.biw * image->bmpih.bibitcount+31)/32*4;
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

    fwrite(&image->bmpfh,sizeof(BMPFH),1,fp);//writes the bitmap file header to the file
	fwrite(&image->bmpih,sizeof(BMPIH),1,fp);//writes he bitmep info header to the file		
	r=0;//r is set to 0 in case 24 bits per pixel or more (this kind of images does not have color palette)
    if(image->bmpih.bibitcount==1) r=2;//if the image 1 bit per pixel (the number of clor is 2)
	if(image->bmpih.bibitcount==4) r=16;//if the image 4 bits per pixel (the number of clor is 16)
	if(image->bmpih.bibitcount==8) r=256;////if the image 8 bits per pixel (the number of clor is 256)
	if(r!=0){
        fwrite(image->palette,4*r,1,fp);
    }
    rowsize=(image->bmpih.biw*image->bmpih.bibitcount+31)/32*4;//a row size of image is calculated 
	size=rowsize*image->bmpih.bih;

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
    for(i=0 ; i<size ; i++)hist[image->data[i]]++;
    FILE *fp;
    fp = fopen("hist_nums.txt","w");
    //for(i=0 ; i<256 ; i++)printf("%d : %d\n",i,hist[i]);
    for(i=0 ; i<256 ; i++){
        fprintf(fp,"%d : %d\n",i,hist[i]);
    }
    fclose(fp);
} 
void histogram(IMAGE *image,double hist[]){
    LONG rowsize,h,w;
    h = image->bmpih.bih;
    w = image->bmpih.biw;
    rowsize = (image->bmpih.bibitcount * image->bmpih.biw + 31)/32*4;
    
    LONG i,j;
    LONG size = rowsize * h;
    for(i=0 ; i<size ; i++)hist[image->data[i]]++;
}
void histogramEqualization(IMAGE *image){
    LONG rowsize,h,w;
    double hist[256] = {0};
    h = image->bmpih.bih;
    w = image->bmpih.biw;
    rowsize = (image->bmpih.bibitcount * image->bmpih.biw + 31)/32*4;
    LONG i,j,sum=0;
    LONG size = rowsize * h;
    histogram(image,hist);
    for(i=0 ; i<512 ; i++)hist[i] /= (h*rowsize);// PMF

    for(i=0 ; i<256 ; i++){
        sum += hist[i];
        hist[i]=(int)(sum*255);
    }

    for(i=0 ; i<size ; i++)(BYTE)hist[image->data[i]];
    
}
    
int main(int argc, char const *argv[])
{
    IMAGE *image = (IMAGE*)malloc(sizeof(IMAGE));
    image = imageRead(image,"Charles.BMP");
    //histogramEqualization(image);
    imageWrite(image,"test7.bmp");
    free(image);
    return 0;
}
