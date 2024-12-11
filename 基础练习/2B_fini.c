#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

long long mod_pow(long long base, long long exp, long long mod)
{
	long long result = 1;
	while (exp > 0)
	{
		if (exp % 2 == 1)
			result = (result * base) % mod;
		base = (base * base) % mod;
		exp /= 2;
	}
	return result;
}

bool miller_rabin_test(long long n, int k) {
	if (n <= 1) 
		return false;
	if (n <= 3) 
		return true; // This covers n = 2 and n = 3
	if (n % 2 == 0) 
		return false;
	
	long long d = n - 1;
	int s = 0;
	while (d % 2 == 0) {
		d /= 2;
		s += 1;
	}
	
	srand(time(NULL));
	int i;
	for (i = 0; i < k; ++i) 
	{
		long long a = 2 + (n > 4 ? rand() % (n - 4) : 0); // Avoiding invalid modulo
		long long x = mod_pow(a, d, n);
		if (x == 1 || x == n - 1)
			continue;
		bool continue_flag = false;
		int r;
		for (r = 1; r < s; ++r) 
		{
			x = (x * x) % n;
			if (x == n - 1) 
			{
				continue_flag = true;
				break;
			}
		}
		if (!continue_flag)
			return false;
	}
	return true;
}

int main()
{
	int t;
	scanf("%d", &t);
	int num[t];
	int i = 0, j = 0, m = 0;
	while (i < t)
		scanf("%d", &num[i++]);
	for (j = 0; j < t; j++)
	{
		if (miller_rabin_test(num[j], 100))
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
