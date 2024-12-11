#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a,b) a > b ? a : b
#define min(a,b) a > b ? b : a

int main() {
    int rows, columns;
    scanf("%d %d", &rows, &columns);

    // 动态分配内存，检查分配是否成功
    char (*matrix)[columns] = malloc(rows * columns * sizeof(char));

    for (int i = 0; i < rows; i++)
        scanf("%s", matrix[i]);

    int (*left)[columns] = malloc(rows * columns * sizeof(int));
    memset(left, 0, sizeof(int) * rows * columns);

    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < columns; j++)
            if (matrix[i][j] == '1') 
                left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;

    int ret = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == '0')
                continue;
            int width = left[i][j];
            int area = width;
            for (int k = i - 1; k >= 0; k--) {
                width = min(width, left[k][j]);
                area = max(area ,(i - k + 1) * width);
            }
            ret = max(ret, area);
        }
    }
    printf("%d", ret);
    return 0;
}

