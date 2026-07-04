#include <string.h>
#include "utils.h"

void init_person(struct person *p, const char *name, int age) {
    strncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0'; // 确保字符串以 null 结尾
    p->age = age;
}