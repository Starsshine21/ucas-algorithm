#include <stdio.h>
#include <stdbool.h>

int main() {
    int a[201] = {0};
    int b[201] = {0};
    int c[201] = {0};
    char ch;
    int i = 0;

    int a_sign = 1;
    while ((ch = getchar()) != '\n') 
	{
        if (i == 0 && ch == '-') 
            a_sign = -1;
		else 
            a[i++] = ch - '0';
    }
    int count_a = i;
    i = 0;
    int b_sign = 1;
    while ((ch = getchar()) != '\n') 
	{
        if (i == 0 && ch == '-')
            b_sign = -1;
        else
            b[i++] = ch - '0';
    }
    int count_b = i;

    int max = count_a > count_b ? count_a : count_b;
    int cin = 0;
    int sum;
    int j, k;
    if((a_sign == 1 && b_sign == 1) || (a_sign == -1 && b_sign == -1))
    for (i = count_a - 1, j = count_b - 1, k = max - 1; k >= 0; i--, j--, k--) {
        if (i >= 0 && j >= 0) 
		{
            if (0 <= (sum = a[i]*a_sign + b[j]*b_sign + cin) < 10) 
			{
                cin = 0;
                c[k] = sum;
            } 
			else if(sum >= 10) 
			{
                cin = 1;
                c[k] = sum - 10;
            }
            else
            {
            	cin = -1;
            	c[k] = sum + 10;
			}
        } 
		else 
		{
            int t = (i == k) ?a[i]*a_sign : b[j]*b_sign;
           	if (-10 < (sum = t + cin) < 10) 
			{
                cin = 0;
                c[k] = sum;
            } 
			else if(sum >= 10) 
			{
                cin = 1;
                c[k] = sum - 10;
            }
            else
            {
            	cin = -1;
            	c[k] = sum + 10;
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
	    if(cin == -1)
	    	printf("-");
	    if (cin == 1)
	        printf("1");
	    for (i = 0; i < max; i++)
	        printf("%d", c[i]);
	}
    return 0;
}
