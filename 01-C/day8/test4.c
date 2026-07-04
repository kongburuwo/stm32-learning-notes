#include <stdio.h>

//有一个数组{10, 20, 30, 40, 50}，请实现如下功能
int main()
{
    int arr[5] = {10, 50, 30, 40, 20};
    int size = sizeof(arr) / sizeof(arr[0]);

    int *p = arr;

    int *start = arr;
    int *end = arr + size - 1;
    int temp;

    int *mptr = arr;
    int max = *mptr;
    int min = *mptr;

    // 重新定义指针用于排序，保持风格统一
    int *i_ptr, *j_ptr, *temp_ptr;


    //1. 编写一个程序，使用指针遍历整型数组并打印每个元素。
    printf("遍历数组：");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", *p);
        p++;
    }
    printf("\n");

    //  2. 编写一个程序，使用指针将数组元素逆序排列。
    while (start < end)
    {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }

    printf("逆序后的数组：");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    //  3. 编写一个程序，使用指针查找整型数组中的最大值和最小值

    for (int i = 0; i < size; i++)
    {
        if (max < *mptr)
        {
            max = *mptr;
        }
        if (min > *mptr)
        {
            min = *mptr;
        }
        mptr++;
    }
    printf("最大值%d 最小值%d\n", max, min);

    //  4. 编写一个程序，使用指针实现冒泡排序算法对整型数组进行排序。
    int *arr_end = arr + size - 1; 
    for (i_ptr = arr; i_ptr < arr_end; i_ptr++)
    {
        for (j_ptr = arr; j_ptr < arr_end - (i_ptr - arr); j_ptr++)
        {
            if (*j_ptr > *(j_ptr + 1))
            {
                temp = *j_ptr;
                *j_ptr = *(j_ptr + 1);
                *(j_ptr + 1) = temp;
            }
        }
    }
    
    printf("冒泡排序后的数组：");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}