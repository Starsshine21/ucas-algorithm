#include <stdio.h>


int main()
{
	int n,k;
	scanf("%d %d",&n,&k);
	int s[n+1];
	int leftmax[n+1];
	int leftmin[n+1] ;
	int rightmax[n+1] ;
	int rightmin[n+1] ;
	getchar();
	int i;
	for(i=1;i<n;i++)
		scanf("%d ",&s[i]);
	scanf("%d",&s[i]);
	int max,min,diff;
	diff = 0;
	leftmax[1] = leftmin[1] = s[1];
	rightmax[n] = rightmin[n] = s[n];

//更新left和right数组 
	for(i=2;i<n-k+1;i++)
	{
		if(s[i] > leftmax[i-1])
			leftmax[i] = s[i];
		else
			leftmax[i] = leftmax[i-1];
		if(s[i] < leftmin[i-1])
			leftmin[i] = s[i];
		else
			leftmin[i] = leftmin[i-1];
			
		if(s[n-i+1] > rightmax[n-i+2])
			rightmax[n-i+1] = s[n-i+1];
		else
			rightmax[n-i+1] = rightmax[n-i+2];
		if(s[n-i+1] < rightmin[n-i+2])
			rightmin[n-i+1] = s[n-i+1];
		else
			rightmin[n-i+1] = rightmin[n-i+2];
	} 
	diff = rightmax[k+1] - rightmin[k+1] ;

//窗口移动 先不讨论左右两边的情况 
	for(i=2;i<=n-k;i++)
	{
		int max_1 = leftmax[i-1];
		int min_1 = leftmin[i-1];
		int max_2 = rightmax[i+k];
		int min_2 = rightmin[i+k];
		max = max_1 > max_2 ? max_1 : max_2;
		min = min_1 < min_2 ? min_1 : min_2;
		if((max-min) < diff)
			diff = max - min; 
	}
	if(leftmax[n-k] - leftmin[n-k] < diff)
		diff = leftmax[n-k] - leftmin[n-k] ;
	printf("%d",diff);
	return 0;
}

//int findmax(int s[100001],int i,int k)//i起点，k长度 
//{
//	int j;
//	int max = 0;
//	for(j=i;j<i+k;j++)
//		if(s[j] > max)
//			max = s[j];
//	return max;
//}
//
//int findmin(int s[100001], int i, int k)
//{
//	int j;
//	int min = 1000000000;
//	for(j=1;j<i+k;j++)
//		if(s[j] < min)
//			min = s[j];
//	return min;
//}

