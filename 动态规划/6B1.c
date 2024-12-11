#include <stdio.h>
#define min(a,b) a < b ? a : b

int num, deli_need, nurti_need;
int nutri[1001], deli[1001], cost[1001];
int dp[101][101];

int main() {
	scanf("%d %d",&nurti_need,&deli_need);
	scanf("%d",&num);
	int i,j,k;
    for (i = 1; i <= num; i++)
        scanf("%d %d %d", &nutri[i], &deli[i], &cost[i]);

    for (i = 1; i <= num; i++) {
        for (j = nurti_need; j >= 0; j--) {
            for (k = deli_need; k >= 0; k--) {
                int nowt = j + nutri[i];
                int nowa = k + deli[i];

                if (nowt > nurti_need) 
					nowt = nurti_need;
                if (nowa > deli_need) 
					nowa = deli_need;

                if ((j == 0 && k == 0 && dp[j][k] == 0) || dp[j][k] != 0) 
				 	if (dp[nowt][nowa]) 
					 	dp[nowt][nowa] = min(dp[nowt][nowa],dp[j][k]+ cost[i]);
					else 
						dp[nowt][nowa] = dp[j][k]+cost[i];
            }
        }
    }
    printf("%d",dp[nurti_need][deli_need]);
    return 0;
}
