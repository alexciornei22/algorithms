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

int compare_items(const void *a, const void *b)
{
    Item item_a = *(Item *) a;
    Item item_b = *(Item *) b;

    double crit_a = item_a.value / item_a.weight;
    double crit_b = item_b.value / item_b.weight;

    if (crit_a > crit_b)
        return -1;
    else
        return 1;
}

double fractional_knapsack(Item *items, int n, int total_weight)
{
    qsort(items, n, sizeof(Item), compare_items);
    double max_value = 0;

    for (int i = 0; i < n; i++) {
        if (items[i].weight <= total_weight) {
            max_value += items[i].value;
            total_weight -= items[i].weight;

            printf("added item value = %d, weight = %d\n", items[i].value, items[i].weight);
        } else {
            max_value += items[i].value *
                ((double) total_weight / (double) items[i].weight);
            
            printf("added %.2f%% of item value = %d, weight = %d\n", (double) total_weight / (double) items[i].weight * 100, items[i].value, items[i].weight);
            break;
        }
    }
    
    return max_value;
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

    double max_value = fractional_knapsack(items, n, total_weight);

    printf("Max value of knapsack = %.2f\n", max_value);

    free(items);
    return 0;
}
