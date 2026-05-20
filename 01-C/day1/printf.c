#include <stdio.h>

int main()
{
    printf("Hello world!\n");

    int a = 123;
    printf("num = %d\n", a);

    printf("num = %x\n", a);

    printf("num = %X\n", a);

    printf("num = %o\n", a);

    printf("char = %c\n", 'a');

    printf("float = %0.2f\n", 123.154515);

    printf("num = %-8dkkkk\n", a);

    printf("num = %+08dkkkk\n", a);

    return 0;
}