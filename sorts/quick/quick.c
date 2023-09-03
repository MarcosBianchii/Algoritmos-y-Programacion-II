#include <stdio.h>

void print_arr(char *arr, int n)
{
        for (int i = 0; i < n; i++)
                printf("%c", arr[i]);
        printf("\n");
}

void swap(char *a, char *b)
{
        char aux = *a;
        *a = *b;
        *b = aux;
}

int get_pi(char *arr, int start, int end)
{
        char pi = arr[end];
        int i = start;
        int j = start;
        for (;j < end; j++){
                if (arr[j] < pi)
                        swap(&arr[i++], &arr[j]);
        }
        swap(&arr[i], &arr[end]);
        return i;
}

void quick_sort(char *arr, int start, int end)
{
        if (end <= start) return;
        int pi = get_pi(arr, start, end);
        quick_sort(arr, start, pi-1);
        quick_sort(arr, pi+1, end);
}

int main()
{
        char arr[] = {'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'};
        int SIZE = sizeof(arr) / sizeof(*arr);
        quick_sort(arr, 0, SIZE-1);
        print_arr(arr, SIZE);
        return 0;
}