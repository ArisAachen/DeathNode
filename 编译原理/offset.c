#include<stdio.h>

int main() {
    int myVar = 10;  // 声明变量

    printf("Original value of myVar: %d\n", myVar);  // 打印原始值
    printf("Address of myVar: %p\n", &myVar);  // 打印地址

    int* ptr = &myVar;  // 创建指向myVar的指针
    *ptr = 20;  // 使用指针修改myVar的值

    printf("Modified value of myVar: %d\n", myVar);  // 打印修改后的值

    return 0;
}