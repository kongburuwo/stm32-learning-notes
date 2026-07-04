#include <stdio.h>

int main() {
    int i, j;
    
    printf("10x10乘法表：\n\n");
    
    // 打印表头
    printf("    ");
    for (i = 1; i <= 10; i++) {
        printf("%4d", i);
    }
    printf("\n");
    
    // 打印分隔线
    printf("    ");
    for (i = 1; i <= 10; i++) {
        printf("----");
    }
    printf("\n");
    
    // 使用嵌套循环打印乘法表
    for (i = 1; i <= 10; i++) {
        // 打印行标
        printf("%2d |", i);
        
        // 打印每一行的乘积
        for (j = 1; j <= 10; j++) {
            printf("%4d", i * j);
        }
        
        printf("\n");
    }
    
    return 0;
}