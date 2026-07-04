#include <stdio.h>
#include "common.h"

void print_person(struct person p) {
    printf("Name: %s, Age: %d\n", p.name, p.age);
}