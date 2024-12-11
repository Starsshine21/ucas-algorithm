#include<stdio.h>
#include<string.h>

#define MAX 1000000
#define INF 5000000
#define min(a,b) a < b ? a : b

int a[MAX];
int dist[4][4]={
	{1,4,3,5},
	{2,1,4,3},
	{4,3,1,3},
	{2,4,3,1}
};

int trans(char c)
{
	if(c == 'L')
		return 0;
	else if(c == 'R')
		return 1;
	else if(c == 'U')
		return 2;
	else
		return 3;
}

int main() {
	int n;
    scanf("%d", &n);
    char c;
    int times;
    getchar();
    int result[n];
	for(times = 0; times < n; times++)
	{
	    int l,r;
	    int i = 0;
	    while((c=getchar()) != '\n')
	        a[i++] = trans(c);
		int step = i;     
		int dp[step+1][4][4];
	    memset(dp, INF, sizeof(dp));
	    dp[0][0][1] = 0;
	    for (i = 0; i < step; i++)
		{//更新dp矩阵，没有被更新到的点不会到达 
	        for (l = 0; l < 4; l++)
			{
	            for (r = 0; r < 4; r++)
				{
	            	//左右脚的情况都考虑 
	                dp[i + 1][a[i]][r] = min(dp[i + 1][a[i]][r], dp[i][l][r] + dist[l][a[i]]);
	                dp[i + 1][l][a[i]] = min(dp[i + 1][l][a[i]], dp[i][l][r] + dist[r][a[i]]);
	            }
	        }
	    }
	    int ans = INF;
	    for (l = 0; l < 4; l++)
	        for (r = 0; r < 4; r++)
	            ans = min(dp[step][l][r], ans);
			result[times] = ans;
	}
	for(times = 0; times < n; times ++)
		printf("%d",result[times]);
    return 0;
}
