#include <stdbool.h>
#include <stdio.h>

void swap_int(int *a, int *b)
{
        int aux = *a;
        *a = *b;
        *b = aux;
}

void sift_down(int *numeros, int tope, int pos)
{
        int izq = pos*2+1;
        int der = pos*2+2;
        if (izq >= tope)
                return;
        
        int mayor = izq;
        if (der < tope && numeros[der] > numeros[izq])
                mayor = der;
        
        if (numeros[pos] < numeros[mayor]){
                swap_int(&numeros[pos], &numeros[mayor]);
                sift_down(numeros, tope, mayor);
        }
}

void heap_sort(int *numeros, int tope, bool ascendente)
{
        for (int i = tope/2-1; i >= 0; i--)
                sift_down(numeros, tope, i);

        for (int i = 0; i < tope; i++){
                swap_int(&numeros[0], &numeros[tope-1-i]);
                sift_down(numeros, tope-1-i, 0);
        }
    
        if (!ascendente){
                int i = 0;
                while (tope-1-i > i)
                        swap_int(&numeros[i++], &numeros[tope-1-i]);
        }
}

void print_array(int *arr, int n)
{
        for (int i = 0; i < n; i++)
                printf("%i ", arr[i]);
        printf("\n");
}

int main()
{
        int numeros[] = {1,6,2,63,0,9,7,456,34,523,412,35,4,5756,856,7856,75,2345,123};
        int n = sizeof(numeros)/sizeof(*numeros);
        
        heap_sort(numeros, n, true);
        print_array(numeros, n);

        return 0;
}