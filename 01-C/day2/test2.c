#include <stdio.h>

int main()
{
    int result;

    result = 5 + 3 > 6;

    printf("result = %d\n", result);

    result = 5 > 3 == 5 < 10;

    printf("result = %d\n", result);
}