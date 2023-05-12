#include <stdio.h>
#include <stdlib.h>

int lis(int *v, int n, int *d, int *j_max, int i)
{
    if (i == 0) {
        d[i] = 1;

        return d[i];
    } else {
        int d_maxx = 0;

        for (int j = 0; j < i; j++) {
            if (!d[j])
                d[j] = lis(v, n, d, j_max, j);
            
            if (v[j] < v[i] && d[j] > d_maxx) {
                d_maxx = d[j];
                d[i] = d_maxx + 1;
                j_max[i] = j;
            }
        }

        if (!d[i])
            d[i] = 1;

        return d[i];
    }
}

void get_seq(int *v, int *j_max, int *seq, int i, int k)
{
    seq[i] = v[k];

    if (i) get_seq(v, j_max, seq, i - 1, j_max[k]);
}

int main()
{
    int v[] = { 1, 2, 9, 3, 8, 4, 7 };
    int n = sizeof(v) / sizeof(int);
    int j_max[n], d[n];

    for (int i = 0; i < n; i++) {
        j_max[i] = -1;
        d[i] = 0;
    }

    int result = lis(v, n, d, j_max, n - 1);
    printf("Longest increasing subsequence length: %d\n", result);
    
    printf("J_max[i]: ");
    for (int i = 0; i < n; i++)
        printf("%d ", j_max[i]);
    printf("\n");

    printf("D[i]: ");
    for (int i = 0; i < n; i++)
        printf("%d ", d[i]);
    printf("\n");

    int seq[result];
    get_seq(v, j_max, seq, result - 1, n - 1);
    printf("Seq[i]: ");
    for (int i = 0; i < result; i++)
        printf("%d ", seq[i]);
    printf("\n");
    return 0;
}