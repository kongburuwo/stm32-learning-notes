#include <stdio.h>
int main()
{
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// 使用指针访问多维数组
int *p = &matrix[0][0];
for(int i = 0; i < 3 * 4; i++) {
    printf("%d ", *(p + i));
}
}