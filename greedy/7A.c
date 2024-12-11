#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    char str1[8], str2[8];
    sprintf(str1, "%d%d", *(int*)a, *(int*)b);
    sprintf(str2, "%d%d", *(int*)b, *(int*)a);
    return strcmp(str2, str1);
}

int main() {
	int numsSize;
	scanf("%d",&numsSize);
	int nums[numsSize];
	int i = 0;
	for(i = 0; i < numsSize; i++)
		scanf("%d",&nums[i]);
	qsort(nums, numsSize, sizeof(int), compare);
	for(i = 0; i < numsSize; i++)
		printf("%d",nums[i]);
    return 0;
}

