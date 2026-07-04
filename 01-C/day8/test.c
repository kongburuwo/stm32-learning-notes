#include <stdio.h>
#include <string.h>
// 编写一个程序，使用指针比较"apple"和"banana"两个字符串。
// 如果第一个字符串小于第二个字符串，输出负值；如果相等，输出0；如果大于，输出正值。

int my_strcmp(char *a, char *b)
{
    while (*a != '\0' && *b != '\0') {
        if (*a != *b) {
            return *a - *b;
        }
        *a++;
        *b++;
        }
    return *a - *b;
}
int main() {
    char *a = "apple";
    char *b = "banana";

    int result = my_strcmp(a, b);
    // printf("%d\n", strcmp(a, b));
    printf("%d\n", result);
    return 0;
}