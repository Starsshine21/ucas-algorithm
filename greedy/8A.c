#攻击力最小优先攻击 
#include <stdio.h>
#include <stdlib.h>

#define min(a, b) a > b ? b : a

typedef struct{
	int attack;
	int endurance;
} Undercover;

int compare(const void *a, const void *b) {
    return ((Undercover *)a)->attack - ((Undercover *)b)->attack;
}

int main()
{
	int num;
	scanf("%d",&num);
	Undercover undercover[num];
	for(int i = 0; i < num; i++)
		scanf("%d %d",&undercover[i].attack, &undercover[i].endurance);
	int fear = 0;
	qsort(undercover, num, sizeof(Undercover), compare);
	int min_attack = 10000000;
	for(int i = 0; i < num; i++) {
		min_attack = min(min_attack, undercover[i].attack - fear);
		fear += undercover[i].endurance;
	}
		printf("%d",min_attack);
	return 0;
 } 
