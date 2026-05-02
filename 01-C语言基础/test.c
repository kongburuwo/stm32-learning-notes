#include <stdio.h>
#include <stdlib.h>

// typedef unsigned int SIZE;
// #define XC

// struct Student {
//     char gender;
//     int age;
//     float score;
// } ;

// typedef struct {
//     char gender;
//     int age;
//     float score;
// } stu_t;
// enum weekday{MONDAY = 1, TUESDAY = 2,WEDNEDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};
// typedef enum 
// {   MONDAY = 1, 
//     TUESDAY = 2,
//     WEDNEDAY, 
//     THURSDAY, 
//     FRIDAY, 
//     SATURDAY, 
//     SUNDAY}week_t;

int main() {
    printf("hello world!\r\n");
    // 测试1：只有 \n 换行
    // printf("ABC\n123");
    // printf("\n------------------\n");

    // 测试2：只有 \r 回车（不换行）
    // printf("ABC\r123");  // 关键：\r 会让光标回到行首，123覆盖ABC
    // printf("\n");

    // SIZE a = 0;
    // printf("a = %d\r\n",a);

// #if 0
//     printf("111\r\n");
// #elif 0
//     printf("222\r\n");
// #else
//     printf("333\r\n");
// #endif

// #ifdef XC
//     printf("444\r\n");
// #endif

// struct{
//     char gender;
//     int age;
//     float score;
// } b;
// stu_t b;

// b.age = 18;
// b.gender = 'm';
// b.score = 100;

// printf("age = %d, gender = %c, score = %.2f\r\n", b.age,b.gender,b.score);


    // enum {MONDAY = 1, TUESDAY = 2,WEDNEDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY}week;
    // week_t week;
    // week = SATURDAY;
    // printf("week = %d\r\n",week);
    // int x = 10;
    // int *p = &x;

    // *p = 20;
    
    // int value = x;
    // printf("value = %d\r\n", value);

    // int arr[5] = {1, 2, 3, 4, 5};

    // int *ptr = arr;

    // for(int i = 0; i < 5; i++)
    // {
    //     printf("%d ", *(ptr + i));
    // }

    int *p = (int *)malloc(sizeof(int));
    if(p != NULL)
    {
        *p = 20;
        printf("%d\r\n", *p);
        free(p);
        p = NULL;
    }

    return 0;
}