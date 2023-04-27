#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Show;

void read_shows(Show *shows, int n)
{
    for (int i = 0; i < n; i++) {
        printf("Show #%d:\n", i + 1);

        printf("start = ");
        scanf("%d", &shows[i].start);

        printf("end = ");
        scanf("%d", &shows[i].end);
    }
}

int compare_shows(const void *a, const void *b)
{
    Show show_a = *(Show *) a;
    Show show_b = *(Show *) b;

    return show_a.end - show_b.end;
}

int max_shows(Show *shows, int n)
{
    qsort(shows, n, sizeof(Show), compare_shows);
    int nr_shows = 0;
    
    int last_end = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            nr_shows++;
            last_end = shows[i].end;

            printf("added show: start = %d, end = %d\n", shows[i].start, shows[i].end);
        } else {
            if (shows[i].start >= last_end) {
                nr_shows++;
                last_end = shows[i].end;
                printf("added show: start = %d, end = %d\n", shows[i].start, shows[i].end);
            }
        }
    }

    return nr_shows;
}

int main()
{
    int n;
    Show *shows;

    printf("Number of shows = ");
    scanf("%d", &n);

    shows = calloc(n, sizeof(Show));
    read_shows(shows, n);

    int nr_shows = max_shows(shows, n);

    printf("Max number of shows in a day = %d\n", nr_shows);

    free(shows);
    return 0;
}
