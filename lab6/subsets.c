#include <stdio.h>
#include <stdlib.h>

int validate(const int *v, int i) {
    return 1;
}

void print_solution(const int *v, int len_sol, int cnt)
{
    printf("%d: ", cnt);
    for (int i = 0; i < len_sol; i++) {
        if (v[i]) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}

int backtrack(int len_sol, int  init_val, int maxx, int val)
{
    int *v = calloc(len_sol, sizeof(int));
    for (int i = 0; i < len_sol; i++)
        v[i] = init_val;

    int i = 0, cnt = 0;
    while (i >= 0) {
        int valid = 0;

        while (!valid && v[i] <= maxx) {
            v[i] += val;
            valid = validate(v, i);
        }

        if (v[i] <= maxx) {
            if (i == len_sol - 1) {
                cnt++;
                print_solution(v, len_sol, cnt);
            } else {
                i++;
            }
        } else {
            v[i] = init_val;
            i--;
        }
    }

    free(v);
    return cnt;
}

int main()
{
    int res = backtrack(3, -1, 1, 1);
    printf("Total solutions: %d\n", res);

    return 0;
}
