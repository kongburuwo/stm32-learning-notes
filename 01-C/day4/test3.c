#include <stdio.h>

//编写一个程序，打印出1到100中所有的素数
int main(){
    int i,j;
    
    for(i=2;i<=100;i++){
        int flag=1;//假设i是素数
        for(j=2;j<i;j++){
            if(i%j==0){
                flag=0;//i不是素数
                break;
            }
        }
        if(flag==1){
            printf("%d ",i);
        }
    }
    
}