#include <stdio.h>

int main()
{
    char *str = "hello world";
    char str2[20] = {0};

    int len = 0;
    char *p = str;
    char *q = str2;

    while(*p != '\0')
    {
        len++;
        p++;
    }

    printf("str的长度是%d\n", len);

    // 拷贝字符串
    // 建议使用副本指针或重置指针，避免修改原始 str (可选，视需求而定)
    p = str; 
    q = str2;

    //拷贝字符串
    while(*p != '\0')
    {
        *q = *p; // 拷贝字符
        p++;
        q++;
    }
    *q = '\0'; // 【关键】手动添加字符串结束符

    printf("%s\n", str2);
    return 0;
}