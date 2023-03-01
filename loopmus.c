#include<stdio.h>
#include<math.h>
#include<stdlib.h>
/*int main(int argc, char const *argv[])//prime numbers summon 1 to n
{
    int num,sum=0;
    printf("Enter num : ");
    scanf("%d",&num);
    for(int i=2; i<=num ;i++){
        int counter = 0;
        for(int j=2 ; j<i/2+1 ; j++){
            if(i%j == 0){
                counter++;
            }
        }if(counter==0) sum += i;
    }printf("%d",sum);
    puts("");
    return 0;
}*/
/*int main(int argc, char const *argv[]){//palindromes to num
    int i=10,num;
    printf("Enter number : ");
    scanf("%d",&num);
    
    while(i<=num){
        int tempDigit = log10(i);
        int temp=i;
        int revNum=0;
        while(temp>0){
            revNum += (temp%10)*pow(10,tempDigit);
            temp /= 10;
            tempDigit--;
        }if(i == revNum)printf("%d\n",i);
    i++;
    }
    return 0;
}*/
/*#include<stdio.h>//encrpyt
#include<stdlib.h>
void search(char *snt,int size);
void reverseSearch(char *snt,int size);

int main(int argc, char const *argv[]){//Anahtarlar Paspasin Altindadir.
    char sentence[100];
    int i=0,size=0;
    printf("Enter sentence : ");
    fgets(sentence,100,stdin);
    printf("%s",sentence);
    while(sentence[i]!=0){
        size++;i++;}
    search(sentence,size);
    puts("");
    reverseSearch(sentence,size);
return 0;
}
void search(char *snt,int size){
    int counter=0;
    for(int i=0 ; i<size ; i++){
        if(snt[i]==0) break;
        snt[i] = (int)snt[i] + 10;
    }for(int i=0 ; i<size ; i++){
        if(snt[i]>=97 && snt[i]<=122){
            counter++;
        }
    }printf("%s%d%d",snt,size-1,counter);
}void reverseSearch(char *snt,int size){
    for(int i=0 ; i<size ; i++){
        if(snt[i]==0) break;
        snt[i] = (int)snt[i] - 10;
    }printf("%s",snt);
}*/
/*#include<stdio.h>//summon max1 and max values of array
#include<stdlib.h>  
void swap(int *a,int *b);
void arrangement(int arr[],int size);
void maxvalues(int[],int size);

int main(int argc, char const *argv[]){
    int size,i;
    printf("Enter your size : ");
    scanf("%d",&size);

    int *arr = (int*) malloc(size*sizeof(int));
    
    for(i=0 ; i<size ; i++){
        printf("Enter %d element : ",i+1);
        scanf("%d",&arr[i]);}

    arrangement(arr,size);

    for(i=0 ; i<size ; i++){
        printf("%d element : %d\n",i+1,arr[i]);
    }

    maxvalues(arr,size);

puts("");
return 0;
}
void swap(int *a,int *b){
    int c = *a;
    *a = *b;
    *b = c;
}
void arrangement(int arr[],int size){
    int i,j;
    for(i=0 ; i<size-1 ; i++){
        for(j=0 ; j<size-1-i ; j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}
void maxvalues(int arr[],int size){
    int max1,max2,maxsummon;
    max1 = arr[size-1];
    max2 = arr[size-2];
    maxsummon = max1 + max2;
    printf("\nFirst maximum value of array : %d",max1);
    printf("\nSecond maximum value of array : %d",max2);
    printf("\nSummon of two maximum values : %d",maxsummon);
}*/