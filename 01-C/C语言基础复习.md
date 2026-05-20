# C语言基础复习
## 数据类型

| 关键字           | 位数 | 表示范围                     | stdint关键字 | ST关键字 |
| ---------------- | ---- | ---------------------------- | ------------ | -------- |
| char             | 8    | -128 ~ 127                   | int8_t       | s8       |
| unsigned char    | 8    | 0 ~ 255                      | uint8_t      | u8       |
| short            | 16   | -32768 ~ 32767               | int16_t      | s16      |
| unsigned short   | 16   | 0 ~ 65535                    | uint16_t     | u16      |
| int              | 32   | -2147483648 ~ 2147483647     | int32_t      | s32      |
| unsigned int     | 32   | 0 ~ 4294967295               | uint32_t     | u32      |
| long             | 32   | -2147483648 ~ 2147483647     |              |          |
| unsigned long    | 32   | 0 ~ 4294967295               |              |          |
| long long        | 64   | -(2^64)/2 ~ (2^64)/2-1       | int64_t      |          |
| unsigned long long | 64 | 0 ~ (2^64)-1                 | uint64_t     |          |
| float            | 32   | -3.4e38 ~ 3.4e38             |              |          |
| double           | 64   | -1.7e308 ~ 1.7e308           |              |          |


## 宏定义
    #define 宏名 字符串
    #define PI 3.14159

## typedef
    #typedef 数据类型 新名字
    #typedef unsigned int SIZE;

## 条件编译
    #if
    #elif
    #endif

    #ifdef
    #endif

## 结构体
    struct 结构体名 {
        数据类型 成员名1;
        数据类型 成员名2;
        ...
        数据类型 成员名n;
    };

## 枚举
    enum 枚举名 {
        常量1, 常量2, ...
    }


## 指针
    type* ptr;