#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 4

int validate(const int *v, int i) {
    for (int k = 0; k < i; k++) {
        if (v[k] == v[i])
            return 0;

        if (i - k == abs(v[i] - v[k]))
            return 0;
    }

    return 1;
}

void print_line_border(int len_sol)
{
    printf("  +");
    for (int j = 0; j < len_sol; j++) {
        if (j == len_sol - 1)
            printf("---+");
        else
            printf("----");
    }
    printf("\n");
}

void print_table(const int *v, int len_sol)
{
    printf("   ");
    for (int i = 0; i < len_sol; i++) {
        printf(" %d  ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < len_sol; i++) {
        print_line_border(len_sol);

        printf("%d |", i + 1);
        for (int j = 0; j < len_sol; j++) {
            if (v[i] == j + 1)
                printf(" * |");
            else
                printf("   |");
        }
        printf("\n");
    }
    print_line_border(len_sol);
}

void print_solution(const int *v, int len_sol, int cnt)
{
    printf("%d: ", cnt);
    for (int i = 0; i < len_sol; i++) {
        printf("%d ", v[i]);
    }
    printf("\n\n");

    print_table(v, len_sol);

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
    int res = backtrack(TABLE_SIZE, 0, TABLE_SIZE, 1);
    printf("Total solutions: %d\n", res);

    return 0;
}
