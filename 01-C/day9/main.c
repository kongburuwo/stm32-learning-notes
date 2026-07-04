#include <stdio.h>
#include <stdlib.h>
#include "common.h" // 包含 print_person 声明和 struct person 定义
#include "utils.h"  // 包含 init_person 声明

int main() {
    struct person person; // 现在编译器知道 struct person 的大小
    init_person(&person, "张三", 25);
    print_person(person);
    printf("Person information printed.\n");

    system("pause");
    return 0;
}