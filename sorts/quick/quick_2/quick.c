#include <stdio.h>
#include <stdbool.h>
#define ARR 14

void swap(int *a, int *b)
{
        int aux = *a;
        *a = *b;
        *b = aux;
}

int conseguir_pivote(int *vector, int inicio, int tope, bool ascendente)
{
        int pivote = vector[tope];
        int i = inicio;
        int j = inicio;
        for (;j < tope; j++){
                if (ascendente)
                        if (vector[j] < pivote)
                                swap(&vector[i++], &vector[j]);
                if (!ascendente)
                        if (vector[j] > pivote)
                                swap(&vector[i++], &vector[j]);
        }
        swap(&vector[i], &vector[tope]);
        return i;
}

void quick_sorter(int *vector, int inicio, int tope, bool ascendente)
{
        if (tope <= inicio) return;
        int pivote = conseguir_pivote(vector, inicio, tope, ascendente);
        quick_sorter(vector, inicio, pivote-1, ascendente);
        quick_sorter(vector, pivote+1, tope, ascendente);
}

void quick_sort(int *numeros, int tope, bool ascendente)
{
        quick_sorter(numeros, 0, tope, ascendente);
}

int main()
{
        int vector[ARR] = {8, 5, -100, -2, 24, -24, 8, 4, -54, -89, -10, -89, -34, -78};
        quick_sort(vector, ARR-1, true);
        for(int i = 0; i < ARR; i++)
                printf("%i ", vector[i]);
        printf("\n");
        return 0;
}