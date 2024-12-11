#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

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

int main(){
	int n, m, k;
	scanf("%d %d %d",&n, &m, &k);
	int top[m + 1];
	int down[m + 1];
	int left[n + 1];
	int right[n + 1];
	for (int i = 0; i <= m; i++)
    	top[i] = n;
	for (int i = 0; i <= n; i++)
    	right[i] = m;


	memset(down, 0, sizeof(down));
	memset(left, 0, sizeof(left));

	int x, y;
	for(int i = 0; i < k; i++)
	{
		scanf("%d %d", &x, &y);
		if(left[x] < y)
			left[x] = y;
		if(right[x] > y)
			right[x] = y;
		if(top[y] > x)
			top[y] = x;
		if(down[y] < x)
			down[y] = x;
	}
	int judge = 0; //ÅÐ¶ÏÊÇ·ñÊÇ¿Õ°×ÇøÓò 
	for(int i = 0; i <= m; i++)
	{
		if(down[i] != 0)
			judge = 1;
		if(down[i] == 0 && judge)
			down[i] = n;
		top[i] = n - top[i];
	}
	judge = 0;
	for(int i = m; i >= 0; i--)
		if(down[i] != n)
			break;
		else
			down[i] = 0;
	judge = 0;
	for(int i = 0; i <= n; i++)
	{
		if(left[i] != 0)
			judge = 1;
		if(left[i] == 0 && judge)
			left[i] = m;
		right[i] = m - right[i];
	}
	judge = 0;
	for(int i = n; i >= 0; i--)
		if(left[i] != m)
			break;
		else
			left[i] = 0;
	int ret = largestRectangleArea(top, m + 1);
	ret = max(largestRectangleArea(down, m + 1), ret);
	int a = max(largestRectangleArea(left, n + 1), largestRectangleArea(right, n + 1)); 
	ret = max(ret, a);
	printf("%d", ret);
	
	return 0;
}
