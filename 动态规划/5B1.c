#include <stdio.h>
#include <string.h>

#define MIN(a, b) ((a < b) ? a : b)
#define MATCH 0
#define NMATCH 5
#define CGNMATCH 4
#define GAP 3

int needlemanWunsch(char *seq1, char *seq2, int len1, int len2) {

    int matrix[len1 + 1][len2 + 1];
	int i,j;
    for (i = 0; i <= len1; i++)
        matrix[i][0] = i * GAP;

    for (j = 0; j <= len2; j++)
        matrix[0][j] = j * GAP;

    for (i = 1; i <= len1; i++) {
        for (j = 1; j <= len2; j++) {
            int match = matrix[i - 1][j - 1] + ((seq1[i - 1] == seq2[j - 1]) ? MATCH: ((seq1[i - 1] == 'C'&& seq2[j - 1] == 'G' || seq1[i - 1] == 'G' && seq2[j - 1] == 'C') ? CGNMATCH:NMATCH));
            int insert1 = matrix[i - 1][j] + GAP;
            int insert2 = matrix[i][j - 1] + GAP;
            matrix[i][j] = MIN(match, MIN(insert1, insert2));
        }
    }
//	for(i = 0; i<=len1;i++)
//	{
//		printf("\n");
//		for(j=0;j<=len2;j++)
//			printf("%d ",matrix[i][j]);
//	}

    return matrix[len1][len2];
}

int main() {
    char sequence1[1000];
    char sequence2[1000];
    char c;
    int i = 0;
    while((c=getchar()) != '\n')
    	sequence1[i++] = c;
    int len1 = i;
	i = 0;
    while((c=getchar()) != '\n')
    	sequence2[i++] = c;
	int len2 = i;
	int score = needlemanWunsch(sequence1, sequence2, len1, len2);
        printf("%d", score);
    return 0;
}

