#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int *left_arr = calloc(n1, sizeof(int));
	int *right_arr = calloc(n2, sizeof(int));

	for (int i = 0; i < n1; i++)
		left_arr[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		right_arr[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (left_arr[i] <= right_arr[j]) {
			arr[k++] = left_arr[i++];
		}
		else {
			arr[k++] = right_arr[j++];
		}
	}

	while (i < n1)
		arr[k++] = left_arr[i++];

	while (j < n2)
		arr[k++] = right_arr[j++];

	free(left_arr);
	free(right_arr);
}

void merge_sort(int *arr, int l, int r)
{
	if (l < r) {
		int m = (l + r) / 2;

		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

int main()
{
	int n, *arr;

    printf("n = ");
    scanf("%d", &n);
    arr = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &(arr[i]));
    }

	merge_sort(arr, 0, n - 1);

	printf("Sorted:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

	free(arr);
	return 0;
}
