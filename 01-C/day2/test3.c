#include <stdio.h>

/*
    位运算符：1.位移运算符： <<,>>
    2.按位与：&
*/
int main()
{
    unsigned char a = 5;    // 0000 0101
    unsigned char b = 9;    // 0000 1001
    // a & b                   0000 0001
    printf("a & b = %d\n", a & b);
    // a | b                   0000 1101
    printf("a | b = %d\n", a | b);
    // a ^ b                // 0000 1100
    printf("a ^ b = %d\n", a ^ b);
    //~a                    // 1111 1010
    printf("~a = %d\n", (unsigned char)~a);
    //a << 1    0000 0101 << 1 -> 0000 1010
    printf("a << 1 = %d\n", a << 1);
    //a >> 1    0000 0101 >> 1 -> 0000 0010
    printf("a << 1 = %d\n", a >> 1);

    return 0;
}