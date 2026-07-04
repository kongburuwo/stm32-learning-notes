#include <stdio.h>

int main()
{
    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;
    int sum = 0;

    // for (int i = 0; i < 5; i++)
    // {
    //     printf("%d ", *p);
    //     sum += *p;
    //     p++;
    
    // }

    // for (int i = 0; i < 5; i++)
    // {
    //     printf("%d ", *(p+i));
    //     sum += *(p+i);
    // }

    for (p = arr; p < arr + 5; p++)
    {
        printf("%d ", *p);
        sum += *p;
    }

    printf("\n");
    printf("sum = %d", sum);

    return 0;

}