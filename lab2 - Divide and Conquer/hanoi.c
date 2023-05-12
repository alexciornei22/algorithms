#include <stdio.h>

void hanoi(int n, char from_tower, char to_tower, char aux_tower)
{
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from_tower, to_tower);
        return;
    }

    hanoi(n - 1, from_tower, aux_tower, to_tower);
    printf("Move disk %d from %c to %c\n", n, from_tower, to_tower);
    hanoi(n - 1, aux_tower, to_tower, from_tower);
}

int main()
{
    int n;
    printf("n = ");
    scanf("%d", &n);

    hanoi(n, 'A', 'C', 'B');
    return 0;
}