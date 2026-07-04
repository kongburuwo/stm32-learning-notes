#ifndef UTILS_H
#define UTILS_H

struct person {
    char name[50];
    int age;
};

void init_person(struct person *p, const char *name, int age);

#endif