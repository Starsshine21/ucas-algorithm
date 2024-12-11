#include <stdio.h>

int main() {
    int a[201] = {0};
    int b[201] = {0};
    int c[201] = {0};
    char ch;
    int i = 0;
    int a_sign = 1;
    int p = 0;
    while ((ch = getchar()) != '\n') 
	{
		if (i == 0 && ch == '-') 
            a_sign = -1;
		else if(p == 0 && ch == '0')
			continue;
		else
		{
            a[i++] = ch - '0';
			p = 1;
		}
	}
    int count_a = i;
    i = 0;
    p = 0;
    int b_sign = 1;
    while ((ch = getchar()) != '\n') 
	{
		if (i == 0 && ch == '-')
            b_sign = -1;
		else if(p == 0 && ch == '0')
			continue;
        else
        {
            b[i++] = ch - '0';
    		p = 1;
		}
	}
    int count_b = i;
	int max = count_a > count_b ? count_a : count_b;
	int cin = 0;
	int sum;
	int j,k;
	if((a_sign == 1 && b_sign == 1) || (a_sign == -1 && b_sign == -1))
	{
		for(i=count_a-1,j=count_b-1,k=max-1;k>=0;i--,j--,k--)
		{
			if(i>=0 && j >=0)
			{
				if((sum = a[i] + b[j] + cin) < 10)
				{
					cin = 0;
					c[k] = sum;
				}
				else
				{
					cin = 1;
					c[k] = sum - 10;
				}
			}
			else
			{
				int t = i == k? a[i] : b[j];
				if((sum = t + cin) < 10)
				{
					cin = 0;
					c[k] = sum;
				}
				else
				{
					cin = 1;
					c[k] = sum - 10;
				}
			}
		}
	int state = 0;
	for(i=0;i<max;i++)
		if(c[i] != 0)
			state = 1;
	if(state == 0)
		printf("0");

	else
	{
		int q;
		for(q=0;q<max;q++)
			if(c[q] != 0)
				break;
		if(a_sign == -1)
			printf("-");
		if(cin==1)
			printf("1");
		for(i=q;i<max;i++)
			printf("%d",c[i]);
	}

	}
	else
	{
		int sign = 1;
		if(a_sign == -1 && b_sign == 1)
		{
			if(count_a > count_b)
				sign = -1;
			else if(count_a == count_b)
			{
				for(i=0;i<max;i++)
					if(a[i] > b[i])
					{
						sign = -1;
						break;
					}
			}
		}
		else
		{
			if(count_a < count_b)
				sign = -1;
			else if(count_a == count_b)
			{
				for(i=0;i<max;i++)
					if(b[i] > a[i])
					{
						sign = -1;
						break;
					}
					else if(b[i] < a[i])
						break; 
			}
		}
		if(sign == 1)
		{
			for(i=count_a-1,j=count_b-1,k=max-1;k>=0;i--,j--,k--)
			{
				if(i>=0 && j >=0)
				{
					if((sum = a[i]*a_sign + b[j]*b_sign + cin) >= 0)
					{
						cin = 0;
						c[k] = sum;
					}
					else
					{
						cin = -1;
						c[k] = sum + 10;
					}
				}
				else
				{
					int t = i == k? a[i]*a_sign : b[j]*b_sign;
					if((sum = t + cin) >= 0)
					{
						cin = 0;
						c[k] = sum;
					}
					else
					{
						cin = -1;
						c[k] = sum + 10;
					}
				}
			}
		}
		else
		{
			for(i=count_a-1,j=count_b-1,k=max-1;k>=0;i--,j--,k--)
			{
				if(i>=0 && j >=0)
				{
					if((sum = -a[i]*a_sign - b[j]*b_sign + cin) >= 0)
					{
						cin = 0;
						c[k] = sum;
					}
					else
					{
						cin = -1;
						c[k] = sum + 10;
					}
				}
				else
				{
					int t = i == k? -a[i]*a_sign : -b[j]*b_sign;
					if((sum = t + cin) >= 0)
					{
						cin = 0;
						c[k] = sum;
					}
					else
					{
						cin = -1;
						c[k] = sum + 10;
					}
				}
			}
		}
		int state = 0;
		for(i=0;i<max;i++)
			if(c[i] != 0)
				state = 1;
		if(state == 0)
			printf("0");
		else
		{
			int q;
			for(q=0;q<max;q++)
				if(c[q] != 0)
					break;
			if(sign == -1)
				printf("-");
			for(i=q;i<max;i++)
				printf("%d",c[i]);
		}
	}

	return 0;
}
