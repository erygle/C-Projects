#include<stdio.h>
int ekok(int firstd,int secondd){//12 5
	int i,k;
	
	for(i=1; i<=secondd; i++){
		firstd = firstd * i;
		
        for(k=1; secondd*k<=firstd; k++){
			
            secondd = secondd * k;
			
            if(firstd==secondd){
				return firstd;
			}
			
            else{
				secondd = secondd/k;
			}
		}
			firstd = firstd/i;
			ekok(firstd,secondd);
	}
}

int main(){
	int num1,num2,x=0;
	
	printf("enter first number: ");
	scanf("%d",&num1);
	
	printf("enter second number: ");
	scanf("%d",&num2);
	
	x=ekok(num1,num2);
	
    printf("ekok: %d",x);
		
	return 0;
}*\