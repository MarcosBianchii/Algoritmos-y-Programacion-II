#include <stdio.h>
#include <stdbool.h>

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

void sift_down(char *arr, int end, int pos)
{
        int l = pos*2+1;
        int r = pos*2+2;
        if (l >= end)
                return;
        
        int larger = l;
        if (r < end && arr[r] > arr[l])
                larger = r;
        
        if (arr[pos] < arr[larger]){
                swap(&arr[pos], &arr[larger]);
                sift_down(arr, end, larger);
        }
}

void heap_sort(char *arr, int end)
{
        for (int i = end/2-1; i >= 0; i--)
                sift_down(arr, end, i);

        for (int i = 0; i < end; i++){
                swap(&arr[0], &arr[end-1-i]);
                sift_down(arr, end-1-i, 0);
        }
}

int main()
{
        char arr[] = {'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'};
        int SIZE = sizeof(arr)/sizeof(*arr);
        heap_sort(arr, SIZE);
        print_arr(arr, SIZE);
        return 0;
}
