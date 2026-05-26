#include <stdio.h>

//冒泡排序
void bubble_sort(int arr[], int n)
{
    int i, j, temp;
    int flag;
    for (i = 1; i < n; i++)
    {
        flag  = 0;  // 每轮开始前，假设没有发生交换

        for(j = 0; j < n - i; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                flag = 1;   // 发生了交换，将标志位置为 1
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
}

int main()
{
    int arr1[] = {52, 48, 93, 45, 18};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    bubble_sort(arr1, n);

    for(int k = 0; k < n; k++)
    {
        printf("%d ", arr1[k]);
    }


    return 0;
}


// 1 2 3 4  -3
// 2 3 4 1  -2
// 3 4 2 1  -1
//n个数一共要进行n-1轮，第一轮要比较n-1次，第二轮要比较n-2次，第三轮要比较n-3次：第m论要比较n - m次