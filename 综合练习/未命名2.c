#include <stdio.h>

// ��������һ��ָ�����е�ָ�������ĳ���
void processColumn(int *columnPointer, int rows) {
    // ��������ж�����Ĵ���
    printf("Received column: ");
    for (int i = 0; i < rows; i++) {
        printf("%d ", columnPointer[i]);
    }
    printf("\n");
}

int main() {
    // ����һ����ά����
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // ����ĳһ��
    int column = 2;
    int columns = 4;
    processColumn(matrix[2], columns);

    return 0;
}

