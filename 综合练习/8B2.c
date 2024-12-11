#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a,b) a > b ? a : b
#define min(a,b) a > b ? b : a

int largestRectangleArea(int* heights, int n) {
    int* left = (int*)malloc(n * sizeof(int));
    int* right = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        left[i] = -1;
        right[i] = n;
    }
    int* mono_stack = (int*)malloc(n * sizeof(int));
    int top = -1;
    for (int i = 0; i < n; ++i) {
        while (top != -1 && heights[mono_stack[top]] >= heights[i])
            right[mono_stack[top--]] = i;
        left[i] = (top == -1 ? -1 : mono_stack[top]);
        mono_stack[++top] = i;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i)
        ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
    return ans;
}

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
                left[i][j] = (i == 0 ? 0 : left[i - 1][j] + 1);
	
    int result = 0;
    for(int i = 0; i < rows; i++)
		result = max(largestRectangleArea(left[i], columns), result);
	printf("%d", result);
    return 0;
}

