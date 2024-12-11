#include <stdio.h>
#define min(a,b) a < b ? a : b
#define max(a,b) a > b ? a : b
#define INF 10000

int num, deli_need, nurti_need;
int nutri[1001], deli[1001], cost[1001];
int dp[101][101];


int main() {
	scanf("%d %d",&nurti_need,&deli_need);
	scanf("%d",&num);
 
	int i,j,k;
	memset(dp, INF, sizeof(dp));
		dp[0][0] = 0;
    for (i = 1; i <= num; i++)
        scanf("%d %d %d", &nutri[i], &deli[i], &cost[i]);

     for (k = 1; k <= num; k++)  //从后往前更新 防止出现同一个东西买两边的情况 
        for (i = nurti_need; i >= 0; i--)
            for (j = deli_need; j >= 0; j--) 
                dp[i][j] = min(dp[i][j], dp[max(0, i - nutri[k])][max(0, j - deli[k])] + cost[k]);

    printf("%d",dp[nurti_need][deli_need]);
    return 0;
}

