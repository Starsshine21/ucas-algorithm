#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max(a,b) a > b ? a : b

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
        ans = max(ans , (right[i] - left[i] - 1) * heights[i]);

    return ans;
}

int main() {
    int heights[] = {2,3,5,0};
    int n = sizeof(heights) / sizeof(heights[0]);
    int result = largestRectangleArea(heights, n);
    printf("%d", result);
    return 0;
}

