#include <stdio.h>
#include <stdlib.h>

#define MAXX 5007

struct Node {
    int x, y;
};

int cmp(const void *a, const void *b) {
    struct Node *nodeA = (struct Node *)a;
    struct Node *nodeB = (struct Node *)b;

    if (nodeA->x != nodeB->x)
        return (nodeA->x - nodeB->x);
    return (nodeA->y - nodeB->y);
}

int cmp2(const void *a, const void *b) {
    struct Node *nodeA = (struct Node *)a;
    struct Node *nodeB = (struct Node *)b;

    if (nodeA->y != nodeB->y)
        return (nodeA->y - nodeB->y);
    return (nodeA->x - nodeB->x);
}

int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);

    struct Node *nod = (struct Node *)malloc((MAXX + 4) * sizeof(struct Node));
    
    for (int i = 1; i <= s; ++i)
        scanf("%d %d", &nod[i].x, &nod[i].y);

    nod[++s] = (struct Node){n, 0};
    nod[++s] = (struct Node){n, m};
    nod[++s] = (struct Node){0, m};
    nod[++s] = (struct Node){0, 0};

    qsort(nod + 1, s + 1, sizeof(struct Node), cmp);

    int ans = 0;
    for (int i = 1; i <= s; ++i) {
        int h1 = m, h2 = 0, k = n - nod[i].x, flag = 0;
        for (int j = i + 1; j <= s; ++j) {
            if (nod[j].y <= h1 && nod[j].y >= h2) {
                if (k * (h1 - h2) <= ans)
                    break;
                ans = (ans > (h1 - h2) * (nod[j].x - nod[i].x)) ? ans : (h1 - h2) * (nod[j].x - nod[i].x);
                if (nod[i].y == nod[j].y) {
                    flag = 1;
                    break;
                }
                if (nod[j].y > nod[i].y)
                    h1 = (h1 < nod[j].y) ? h1 : nod[j].y;
                else
                    h2 = (h2 > nod[j].y) ? h2 : nod[j].y;
            }
        }
        if (!flag)
            ans = (ans > k * (h1 - h2)) ? ans : k * (h1 - h2);

        h1 = m, h2 = 0, k = nod[i].x, flag = 0;
        for (int j = i - 1; j >= 1; --j) {
            if (nod[j].y <= h1 && nod[j].y >= h2) {
                if (k * (h1 - h2) <= ans)
                    break;
                ans = (ans > (h1 - h2) * (nod[i].x - nod[j].x)) ? ans : (h1 - h2) * (nod[i].x - nod[j].x);
                if (nod[i].y == nod[j].y) {
                    flag = 1;
                    break;
                }
                if (nod[j].y > nod[i].y)
                    h1 = (h1 < nod[j].y) ? h1 : nod[j].y;
                else
                    h2 = (h2 > nod[j].y) ? h2 : nod[j].y;
            }
        }
        if (!flag)
            ans = (ans > k * (h1 - h2)) ? ans : k * (h1 - h2);
    }
    qsort(nod + 1, s + 1, sizeof(struct Node), cmp2);
    for (int i = 1; i < s; ++i)
        ans = (ans > n * (nod[i + 1].y - nod[i].y)) ? ans : n * (nod[i + 1].y - nod[i].y);
    printf("%d", ans);
    return 0;
}

