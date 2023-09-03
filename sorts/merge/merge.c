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

void merge(char *arr, int start, int mid, int end)
{
        int temp[end - start + 1]; 
        int i = start;
        int j = mid + 1;
        int k = 0;
        while (i <= mid && j <= end){
                if (arr[i] < arr[j])
                        temp[k++] = arr[i++];
                if (arr[i] >= arr[j])
                        temp[k++] = arr[j++];
        }
        while (i <= mid)
                temp[k++] = arr[i++];
        while (j <= end)
                temp[k++] = arr[j++];
        for (i = start; i <= end; i++)
                arr[i] = temp[i-start];
}

void merge_sort(char *arr, int start, int end)
{       
        if (end <= start) return;
        int mid = (start + end) / 2;
        merge_sort(arr, start, mid);
        merge_sort(arr, mid+1, end);
        merge(arr, start, mid, end);
}

int main()
{
        char arr[] = {'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'};
        int SIZE = sizeof(arr)/sizeof(*arr);
        merge_sort(arr, 0, SIZE-1);
        print_arr(arr, SIZE);
        return 0;
}