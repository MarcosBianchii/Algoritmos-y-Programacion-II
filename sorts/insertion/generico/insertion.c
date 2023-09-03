#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int comp_int(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int comp_char(const void *a, const void *b)
{
    return *(char *)a - *(char *)b;
}


void print_arr_char(char *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%c", arr[i]);
    printf("\n");
}

void print_arr_int(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%i ", arr[i]);
    printf("\n");
}


void print_arr(void *arr, int n, int size)
{
    if (size == sizeof(char))
        print_arr_char((char *)arr, n);
    else if (size == sizeof(int))
        print_arr_int((int *)arr, n);
}

void swap(void *a, void *b, int size)
{
    uint8_t tmp[size];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

void sort_generico(void *arr, int n, int size, int (*comp)(const void *, const void*))
{
    for (int i = 1; i < n; i++){
        int j = i;
        while (j > 0 && comp(arr+(j*size), arr+((j-1)*size)) < 0)
            swap(arr+(j--*size), arr+((j-1)*size), size);
    }
}

int main()
{
    int arr[] = {534, 246, 933, 127, 277, 321, 454, 565, 220};
    int n = sizeof(arr)/sizeof(*arr);

    sort_generico(arr, n, sizeof(*arr), comp_int); // Hay que cambiar el comparador.
    print_arr(arr, n, sizeof(*arr));
    
    return 0;
}