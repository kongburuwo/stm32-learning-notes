#include <stdio.h>

// 编写一个程序，使用指针将一个字符串复制到另一个字符串。
int main()
{
    char arr[] = "Hello World";
    char arr2[100]; // 确保目标数组足够大以容纳源字符串
    char *p = arr;
    char *q = arr2;

    while (*p != '\0')
    {
        *q = *p;
        p++;
        q++;
    }
    *q = '\0'; // 添加字符串结束标志
    printf("%s\n", arr);
    printf("%s\n", arr2);
}