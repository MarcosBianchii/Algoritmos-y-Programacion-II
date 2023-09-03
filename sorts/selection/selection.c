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

void selection_sort(char *arr, int end)
{
        for (int i = 0; i < end-1; i++)
                for (int j = i+1; j < end; j++)
                        if (arr[j] < arr[i])
                                swap(&arr[j], &arr[i]);
}

int main()
{
        char arr[] = {'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'};
        int SIZE = sizeof(arr)/sizeof(*arr);
        selection_sort(arr, SIZE);
        print_arr(arr, SIZE);
        return 0;
}