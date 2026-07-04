#include <stdio.h>

//编写一个程序，使用指针计算字符串的长度。

int main()
{
    char arr[] = "Hello World";
    char *p = arr; // 定义一个指针，指向字符串的首地址
    int count = 0; // 定义一个计数器，初始值为0

    while (*p != '\0')
    {
        count++;
        p++;
    }

    printf("字符串长度为：%d\n", count);
}