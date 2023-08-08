#include<stdio.h>
#include<string.h>
int main(int argc, char const *argv[])
{
    char str[10];
    fgets(str, sizeof(str), stdin);

    //scanf("%s",str);
    printf("%s",str);
    
    return 0;
}
