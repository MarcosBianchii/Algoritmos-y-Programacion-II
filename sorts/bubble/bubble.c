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

void bubble_sort(char *arr, int end)
{
        for (int i = 0; i < end-1; i++)
                for (int j = 0; j < end-i-1; j++)
                        if (arr[j] > arr[j+1])
                                swap(&arr[j], &arr[j+1]);
}

int main()
{
        char arr[] = {'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'};
        int SIZE = sizeof(arr)/sizeof(*arr);
        bubble_sort(arr, SIZE);
        print_arr(arr, SIZE);
        return 0;
}