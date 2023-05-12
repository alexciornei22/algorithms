#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_DELIM ", "
#define POST "|"
#define FENCE "="
#define STR_MAX 0xfff

void get_sol_str(char (* sol)[STR_MAX], int i, int k)
{
    char aux[STR_MAX];
    strncpy(aux, sol[i - 1], strlen(sol[i - 1]) + 1);

    char *tok = strtok(aux, STR_DELIM);
    while (tok) {
        strcat(sol[i], tok);
        strcat(sol[i], POST);
        strcat(sol[i], STR_DELIM);

        tok = strtok(NULL, STR_DELIM);
    }

    strncpy(aux, sol[i - k], strlen(sol[i - k]) + 1);
    tok = strtok(aux, STR_DELIM);
    while (tok) {
        strcat(sol[i], tok);
        strcat(sol[i], FENCE);
        strcat(sol[i], STR_DELIM);

        tok = strtok(NULL, STR_DELIM);
    }

    if (i == k) {
        strcat(sol[i], FENCE);
        strcat(sol[i], STR_DELIM);
    }
}

int get_d(int *d, int i, int k, char (* sol)[STR_MAX])
{
    if (i < 2) {
        d[i] = 1;
        return 1;
    }
    if (d[i] >= 0)
        return d[i];

    d[i] = get_d(d, i - 1, k, sol) + get_d(d, i - k, k, sol);
    get_sol_str(sol, i, k);

    return d[i];
}

int main()
{
    int k = 2;
    int n = 6;
    int d[n + 1];
    char sol[n + 1][STR_MAX];

    for (int i = 0; i <= n; i++)
        d[i] = -1;

    strncpy(sol[0], "", strlen("") + 1);
    strncpy(sol[1], "|,", strlen("|,") + 1);

    get_d(d, n, k, sol);

    for (int i = 0; i <= n; i++) {
        printf("d[%d] = %d\n", i, d[i]);
        printf("%s\n", sol[i]);

    }

    return 0;
}