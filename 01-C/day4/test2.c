#include <stdio.h>

//选择排序
int main()
{
    int i, j, min_idx, temp;
    int arr1[] = {52, 48, 93, 45, 18};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if(arr1[j] < arr1[min_idx])
            {
                min_idx = j;
            }
        }
        if(min_idx != i)
        {
            temp = arr1[i];
            arr1[i] = arr1[min_idx];
            arr1[min_idx] = temp;
        }
    }
    for(int k = 0; k < n; k++)
    {
        printf("%d ", arr1[k]);
    }

    return 0;
}