#include <stdio.h>

int find_LIS(int arr[], int n) {
    int lis[n];
    int i,j;
	for (i = 0; i < n; i++) {
        lis[i] = 1;
    }

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    int max_length = 0;
    for (i = 0; i < n; i++) {
        if (lis[i] > max_length) {
            max_length = lis[i];
        }
    }
    return max_length;
}

int main() {
    int arr[] = {9,10,4,5,7,7,1,0,6};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = find_LIS(arr, n);
    printf("%d", result);

    return 0;
}

