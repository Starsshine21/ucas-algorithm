#include <stdio.h>

// 函数接受一个指向整列的指针和数组的长度
void processColumn(int *columnPointer, int rows) {
    // 在这里进行对数组的处理
    printf("Received column: ");
    for (int i = 0; i < rows; i++) {
        printf("%d ", columnPointer[i]);
    }
    printf("\n");
}

int main() {
    // 定义一个二维数组
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // 传递某一列
    int column = 2;
    int columns = 4;
    processColumn(matrix[2], columns);

    return 0;
}

