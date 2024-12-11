#include <stdio.h>
#include <stdlib.h>

// 比较函数用于排序
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, m;
    scanf("%d %d",&n, &m);
    int num = n * m;
    int *matrix = (int *)malloc(num * sizeof(int));
    for (int i = 0; i < num; i++)
        scanf("%d",&matrix[i]);
	int sum = 0;
	qsort(matrix, num, sizeof(int), compare);
	int part_max;
	int min = 0;
	int max = num - 1;
	int left_step = (m - 1) / 2;
	int right_step = m / 2;
	for(int i = 0; i < n; i++)
	{
		min += left_step;
		max -= right_step;
		sum += matrix[max];
		max -= 1;
	}
	printf("%d",sum);
    return 0;
}

