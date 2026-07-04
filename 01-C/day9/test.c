#include <stdio.h>  //<> system header系统头文件
// #include "test1.h"  "" user header当前目录下的头文件
#include "test.h"
#define VSERION 5

#if VSERION == 1
#define MAX_SIZE 200
#elif VSERION == 2
#define MAX_SIZE 300
#else
#define MAX_SIZE 400
#endif 

int main(int argc, char *argv[]) {    //argc命令行参数的个数，argv命令行参数的数组
  printf("%.2f \n", PI);

#ifdef PI
  printf("PI is defined \n");
#else
  printf("PI is not defined \n");
#endif

#ifdef MAX_SIZE
  printf("MAX_SIZE is defined \n");
  printf("MAX_SIZE = %d \n", MAX_SIZE);
#endif

#ifdef DEBUG
  printf("DEBUG is defined \n");
  printf("MAX(5, 10) = %d \n", MAX(5, 10));
#endif

  return 0;
}