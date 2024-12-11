#include <stdio.h>
#include <string.h>
#define min(a,b) (a > b ? b:a)

int n,m,s,t,dis[1010][1010],w[1010],dap[1010],vis[1010],ord[1010];//n为点数，m为边数，dis[i][j]=w表述点i与点j之间有一条权为w的边 


int proc (int x) 
{
	memset(vis,0,sizeof(vis));
	memset(w,0,sizeof(w));
	w[0]=-1;
	int i;
	int j;
	int mx;
	for (i=1;i<=n-x+1;i++) 
	{
		mx=0;
		for (j=1;j<=n;j++) 
			if (!dap[j]&&!vis[j]&&w[j]>w[mx]) 
			    mx=j;

		vis[mx]=1;
		ord[i]=mx;
		for (j=1;j<=n;j++)
			if (!dap[j]&&!vis[j])
			     w[j]+=dis[mx][j];
	}
	s=ord[n-x];
	t=ord[n-x+1];
	return w[t];
}
int main() //返回最小割 
{
	int res=1000000000;
	int i; 
	int j;
	for (i=1;i<n;i++) 
	{
		res=min(res,proc(i));
		dap[t]=1;
		for (j=1;j<=n;j++) 
		{
			dis[s][j]+=dis[t][j];
			dis[j][s]+=dis[j][t];
		}
	}
	printf("%d",res);
}

