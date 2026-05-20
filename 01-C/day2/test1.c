#include <stdio.h>

//将华氏温度转换为摄氏温度
int main()
{
    float fahrenheit, celsius;
    printf("请输入华氏温度：");

    scanf("%f", &fahrenheit);

    celsius = (fahrenheit - 32) * 5.0 / 9.0;

    printf("摄氏温度是：%.2f\n", celsius);

}