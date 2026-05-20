#include <stdio.h>

//位运算符：1.针对寄存器的特定位做清0操作
int main()
{
    unsigned char a = 0xFD; //1111 1101
    unsigned char mask = ~(1 << 3); // ~(0000 1000) = 1111 0111
    a &= mask; // a = a & mask; 1111 1101 & 1111 0111 = 1111 0101
    printf("a = %X\n", a);

    unsigned char lowMask = 0x0F;
    a &= lowMask;
    printf("a = %X\n", a);

    unsigned char num = 100;
    unsigned char complement = ~num + 1;
    printf("数值: %d, 补码: %d\n", num, complement);

    return 0;
}