#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int l, int r, int key) {
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (arr[m] >= key)
            r = m;
        else
            l = m;
    }
    return r;
}

int find_LIS(int arr[], int n) {
    int *tailTable = (int *)malloc(n * sizeof(int));
    int len; 

    tailTable[0] = arr[0];
    len = 1;
	int i;
    for (i = 1; i < n; i++) {
        if (arr[i] < tailTable[0])
            tailTable[0] = arr[i];
        else if (arr[i] > tailTable[len - 1])
            tailTable[len++] = arr[i];
        else
            tailTable[binarySearch(tailTable, -1, len - 1, arr[i])] = arr[i];
    }

    free(tailTable);
    return len;
}

int main() {
	int n;
	scanf("%d",&n); 
    int arr[n];
    int i;
    for(i = 0; i < n; i++)
    	scanf("%d",&arr[i]);
    int result = find_LIS(arr, n);
    printf("%d", result);
    return 0;
}

