#include <stdio.h>

long long a[100000], ordered_array[100000];

int countleftright(long long a[], int left, int mid, int right)
{
	int count = 0;
	int i = left, j = mid + 1;
	int k;
	for (k = left; k <= right; k++)
	{
		int t = left;
		if ((j > right) || (i <= mid) && (a[i] <= a[j]))  //左边的小，或者右边已经扫完了 
		{
			ordered_array[k] = a[i++];
		}
		else   //右边的小，或者左边已经扫完了 
		{
			while(t <= mid)
			{
				if(a[t] > 3 * a[j]) 
				{
					count += mid - t + 1;
					break;
				}
				else
					t++;
			}
			ordered_array[k] = a[j++];
		}
	}
	for (i = left; i <= right; i++)
		a[i] = ordered_array[i];
	return count;
}

int countsignificant(int a[], int left, int right)
{
	if (left < right) {
		int mid = left + (right - left) / 2;
		return countsignificant(a, left, mid) 
			+ countsignificant(a, mid + 1, right)
			+ countleftright(a, left, mid, right);
	}
	else
		return 0;
}

int main()
{
	int num;
	scanf("%d",&num);
	int i;
	for(i=0;i<num;i++)
		scanf("%d",&a[i]);
	int result = countsignificant(a,0,num-1);
	printf("%d",result);
	return 0;
}

