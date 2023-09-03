#include <stdbool.h>
#include <stdio.h>
#define ARR 14

void merge(int *vector, int inicio, int medio, int tope, bool ascendente)
{
    int aux[tope - inicio + 1];
    int i = inicio;    // subvector 1
    int j = medio + 1; // subvector 2
    int k = 0;         // iterador aux
    while (i <= medio && j <= tope){
        if (ascendente){
            if (vector[i] < vector[j])
                aux[k++] = vector[i++];
            if (vector[i] >= vector[j])
                aux[k++] = vector[j++];
        } else {
            if (vector[i] > vector[j])
                aux[k++] = vector[i++];
            if (vector[i] <= vector[j])
                aux[k++] = vector[j++];
        }
    }
    while (i <= medio)
        aux[k++] = vector[i++];
    while (j <= tope)
        aux[k++] = vector[j++];
    for (int l = inicio; l <= tope; l++)
        vector[l] = aux[l-inicio];
}

void merge_sorter(int *vector, int inicio, int tope, bool ascendente)
{
    if (tope <= inicio) return;
    int medio = (inicio + tope) / 2;
    merge_sorter(vector, inicio, medio, ascendente);
    merge_sorter(vector, medio+1, tope, ascendente);
    merge(vector, inicio, medio, tope, ascendente);
}

void merge_sort(int* numeros, int tope, bool ascendente)
{
    merge_sorter(numeros, 0, tope, ascendente);
}

int main()
{
    int vector[ARR] = {8, 5, -100, -2, 24, -24, 8, 4, -54, -89, -10, -89, -34, -78};
    merge_sort(vector, ARR-1, true);

    for(int i = 0; i < ARR; i++)
        printf("%i ", vector[i]);
    printf("\n");

    return 0;
}