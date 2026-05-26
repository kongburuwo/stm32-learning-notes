#include <stdio.h>

int main() {
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("二维数组的基址: %p\n\n", matrix);
    
    printf("元素地址和值:\n");
    printf("%-12s %-12s %-12s %-12s\n", "元素", "索引", "地址", "值");
    printf("----------------------------------------\n");
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            printf("matrix[%d][%d] %-12s %p %-12d\n", 
                   i, j, "", &matrix[i][j], matrix[i][j]);
        }
    }
    
    return 0;
}