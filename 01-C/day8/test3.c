#include <stdio.h>

//  有"Hello,"和"World！"两个字符串，编写一个程序，使用指针将一个字符串连接到另一个字符串的末尾。
int main()
{
    char dest[50] = "hello,";
    char src[] = "world!";
    char *p_dest = dest;
    char *p_src = src;

    while (*p_dest != '\0') {
        p_dest++;
    }

    while ((*p_dest++ = *p_src++) != '\0') {
        ;
    }

    *p_dest = '\0';
    printf("%s\n", dest);

    return 0;
}