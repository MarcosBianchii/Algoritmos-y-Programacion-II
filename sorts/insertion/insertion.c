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

void insertion_sort(char *arr, int end)
{
        for (int i = 1; i < end; i++){
                int j = i;
                while (j > 0 && arr[j] < arr[j-1])
                        swap(&arr[j--], &arr[j-1]);
        }
}

int main()
{
        char arr[] = {'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'};
        int SIZE = sizeof(arr)/sizeof(*arr);
        insertion_sort(arr, SIZE);
        print_arr(arr, SIZE);
        return 0;
}