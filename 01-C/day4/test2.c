#include <stdio.h>

int main() {
    // 待排序数组
    int arr[] = {78, 92, 85, 64, 88};
    // 计算数组长度
    int n = sizeof(arr) / sizeof(arr[0]);

    // ========== 选择排序核心 ==========
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;  // 假设当前位置是最小值下标

        // 找后面所有数里最小的那个
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;  // 更新最小值下标
            }
        }

        // 把找到的最小值 交换到当前 i 位置
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }

    // 输出结果
    printf("排序后：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}