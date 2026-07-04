#include <stdio.h>

int main()
{
    int sum = 0;
    int scores[5] = {90, 85, 77, 92, 88};

    for(int i = 0; i < 5; i++)
    {
        sum += scores[i];
    }

    printf("%d\n", sum);

    char str[5] = {'a', 'b', 'c', 'd', '0'};

    printf("sizeof str = %d\n", sizeof(str));

    //计算元素个数
    int len = sizeof(scores) / sizeof(scores[0]);

    printf("len = %d\n", len);


    return 0;
}