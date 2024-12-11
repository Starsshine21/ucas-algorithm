#include <stdio.h>
#include <stdlib.h>


int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int maximizeMinDistance(int L, int N, int M, int stone_positions[]) {
    qsort(stone_positions, N, sizeof(int), compare);
    int left = 0;
    int right = L;

    while (left <= right)
	{
        int mid = (left + right) / 2;
        int count_to_remove = 0;
        int prev_position = 0;
		int i; 
        for (i = 0; i < N; i++) {
            if (stone_positions[i] - prev_position < mid)
                count_to_remove++;
            else
                prev_position = stone_positions[i];
        }

        if (count_to_remove > M)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return right;
}

int main(){
    int L,N,M;
    scanf("%d %d %d",&L,&N,&M);
    int stone_positions[N];
    int i;
    for(i=0;i<N;i++)
    	scanf("%d",&stone_positions[i]);
	stone_positions[N] = L;
    int result = maximizeMinDistance(L, N+1, M, stone_positions);
    printf("%d", result);

    return 0;
}

