#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int weight;
} Item;

void read_items(Item *items, int n)
{
    for (int i = 0; i < n; i++) {
        printf("Item #%d:\n", i + 1);

        printf("value = ");
        scanf("%d", &items[i].value);

        printf("weight = ");
        scanf("%d", &items[i].weight);
    }
}

int max(int a, int b) {
    return (a > b)? a : b;
}

int knapsack_aux(Item *items, int n, int total_weight, int i, int **d) {
    if (i < 0)
        return 0;
    if (d[i][total_weight] != -1)
        return d[i][total_weight];

    int included, not_included;

    if (items[i].weight > total_weight) {
        d[i][total_weight] = knapsack_aux(items, n, total_weight, i - 1, d);
    } else {
        included = items[i].value + knapsack_aux(items, n, total_weight - items[i].weight, i - 1, d);
        not_included = knapsack_aux(items, n, total_weight, i - 1, d);

        d[i][total_weight] = max(included, not_included);
    }

    return d[i][total_weight];
}

int knapsack(Item *items, int n, int total_weight)
{
    int **d;

    d = calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) {
        d[i] = calloc(total_weight + 1, sizeof(int));
        for (int j = 0; j < total_weight + 1; j++) {
            d[i][j] = -1;
        }
    }

    int result = knapsack_aux(items, n, total_weight, n - 1, d);

    for (int i = n - 1; i >= 0; i--) {
        if (i == 0 && d[i][total_weight] > 0)
            printf("Added item %d, val = %d, weight = %d\n", i + 1, items[i].value, items[i].weight);
        else {
             if (d[i][total_weight] != d[i - 1][total_weight]) {
            printf("Added item %d, val = %d, weight = %d\n", i + 1, items[i].value, items[i].weight);
            total_weight -= items[i].weight;
        }
        if (!total_weight)
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        free(d[i]);
    }
    free(d);

    return result;
}

int main()
{
    int n;
    int total_weight;
    Item *items;

    printf("Total weight = ");
    scanf("%d", &total_weight);

    printf("Number of items = ");
    scanf("%d", &n);

    items = calloc(n, sizeof(Item));
    read_items(items, n);

    int max_value = knapsack(items, n, total_weight);

    printf("Max value of knapsack = %d\n", max_value);

    free(items);
    return 0;
}
