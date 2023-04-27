#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_d(int *set, int (* d)[3], int i, int j)
{
    if (i == 0) {
        d[i][j] = 0;
        return 0;
    }

    if (d[i][j] >= 0)
        return d[i][j];

    int r = set[i - 1] % 3;

    switch (r) {
        case 0:
            switch (j) {
                case 0:
                    d[i][j] = 1 + 2 * get_d(set, d, i - 1, 0);
                    break;
                case 1:
                    d[i][j] = 2 * get_d(set, d, i - 1, 1);
                    break;
                case 2:
                    d[i][j] = 2 * get_d(set, d, i - 1, 2);
                    break;
            }
            break;
        case 1:
            switch (j) {
                case 0:
                    d[i][j] = get_d(set, d, i - 1, 0) + get_d(set, d, i - 1, 2);
                    break;
                case 1:
                    d[i][j] = 1 + get_d(set, d, i - 1, 0) + get_d(set, d, i - 1, 1);
                    break;
                case 2:
                    d[i][j] = get_d(set, d, i - 1, 2) + get_d(set, d, i - 1, 1);
                    break;
            }
            break;
        case 2:
            switch (j) {
                case 0:
                    d[i][j] = get_d(set, d, i - 1, 0) + get_d(set, d, i - 1, 1);
                    break;
                case 1:
                    d[i][j] = get_d(set, d, i - 1, 2) + get_d(set, d, i - 1, 1);
                    break;
                case 2:
                    d[i][j] = 1 + get_d(set, d, i - 1, 2) + get_d(set, d, i - 1, 0);
                    break;
            }
            break;
    }

    return d[i][j];
}

void sum3(int *set, int n, int (* d)[3])
{
    get_d(set, d, n, 0);
    get_d(set, d, n, 1);
    get_d(set, d, n, 2);
}

int main()
{
    int set[] = { 3, 1, 2, 4 };
    int n = sizeof(set) / sizeof(int);
    int d[n + 1][3];

    for (int i = 0; i < n + 1; i++) {
        d[i][0] = d[i][1] = d[i][2] = -1;
    }
    
    sum3(set, n, d);

    printf("d[%d][0] = %d\n\n", n, d[n][0]);

    for (int i = 0; i < n + 1; i++) {
        printf("d[%d][0] = %d, d[%d][1] = %d, d[%d][2] = %d\n", i, d[i][0], i, d[i][1], i, d[i][2]);
    }
    
    return 0;
}