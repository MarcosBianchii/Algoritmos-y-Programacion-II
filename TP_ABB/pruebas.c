#include "src/abb.h"
#include "pa2mm.h"
#include "string.h"

#include <stdio.h>

int g_contador = 0; // Uso esta variable para que me quede mas ordenada la pantalla con los resultados.

bool comparador_null(void *a, void *b)
{
  printf("%i ", *(int *)a);
  g_contador++;
  if (g_contador == 9){
    printf("\n");
    g_contador = 0;
    return false;
  }
  return true;
}

bool comparador(void *a, void *b)
{
  printf("%i ", *(int *)a);
  bool val = (*(int *)a != *(int *)b);
  if (!val) printf("\n");
  return val;
}

int comparador_aux(void *a, void *b)
{
  if (!a && !b) return 0;
  if (!a || !b) return 1;
  return *(int *)a - *(int *)b;
}

void imprimir_vector(void *array[10], int n)
{
  for(int i = 0; i < n; i++)
    printf("%i ", *(int *)array[i]);
  printf("\n");
}

// Funciones de prueba del abb.

void se_puede_crear_el_abb_exitosamente()
{
  abb_t *arbol = abb_crear(comparador_aux);
  pa2m_afirmar(arbol, "Se creo el arbol con exito");
  pa2m_afirmar(arbol->comparador, "Comparador no es NULL");
  abb_destruir(arbol);
}

void pruebas_de_insercion_del_abb()
{
  abb_t *arbol = abb_crear(comparador_aux);
  pa2m_afirmar(abb_vacio(arbol), "El arbol esta vacio pre-insertado");

  int elemento1 = 1;
  pa2m_afirmar(abb_insertar(arbol, &elemento1), "Se inserto un elemento");
  pa2m_afirmar(!abb_vacio(arbol), "El arbol no esta vacio post-insertado");
  pa2m_afirmar(*(int *)(arbol->nodo_raiz->elemento) == 1, "El elemento insertado quedo como raiz");
  pa2m_afirmar(abb_tamanio(arbol) == 1, "El tamanio del ABB es 1");

  int elemento2 = 2;
  pa2m_afirmar(abb_insertar(arbol, &elemento2), "Se inserto otro elemento");
  pa2m_afirmar(*(int *)(arbol->nodo_raiz->elemento) != 2, "El elemento insertado no quedo como raiz");
  pa2m_afirmar(abb_tamanio(arbol) == 2, "El tamanio del ABB es 2");
  
  int elemento3 = 3;
  pa2m_afirmar(abb_insertar(arbol, &elemento3), "Se inserto otro elemento");
  pa2m_afirmar(*(int *)(arbol->nodo_raiz->elemento) != 3, "El elemento insertado no quedo como raiz");
  pa2m_afirmar(abb_tamanio(arbol) == 3, "El tamanio del ABB es 3");
  abb_destruir(arbol);
}

void pruebas_de_extraccion_del_abb()
{
/*
 *               5
 *             /  \
 *            3    7
 *           / \  / \
 *          2  4 6   8
 *         /          \
 *        1            9
 */
  abb_t *arbol = abb_crear(comparador_aux);
  int elemento5 = 5; abb_insertar(arbol, &elemento5);
  int elemento3 = 3; abb_insertar(arbol, &elemento3);
  int elemento7 = 7; abb_insertar(arbol, &elemento7);
  int elemento2 = 2; abb_insertar(arbol, &elemento2);
  int elemento1 = 1; abb_insertar(arbol, &elemento1);
  int elemento4 = 4; abb_insertar(arbol, &elemento4);
  int elemento6 = 6; abb_insertar(arbol, &elemento6);
  int elemento8 = 8; abb_insertar(arbol, &elemento8);
  int elemento9 = 9; abb_insertar(arbol, &elemento9);

  pa2m_afirmar(*(int *)(arbol->nodo_raiz->elemento) == 5, "El nodo raiz apunta al numero 5");
  pa2m_afirmar(abb_tamanio(arbol) == 9, "El arbol tiene 9 elementos");

  pa2m_afirmar(!abb_quitar(arbol, NULL), "En caso de recibir un elemento NULL, devuelve NULL");
  pa2m_afirmar(abb_tamanio(arbol) == 9, "La cantidad de elementos no cambio");

  pa2m_afirmar(abb_quitar(arbol, &elemento1) == &elemento1, "Quitar una hoja fue exitoso");
  pa2m_afirmar(abb_tamanio(arbol) == 8, "La cantidad de elementos bajo en 1");

  pa2m_afirmar(abb_quitar(arbol, &elemento5) == &elemento5, "Quitar la raiz fue exitoso");
  pa2m_afirmar(abb_tamanio(arbol) == 7, "La cantidad de elementos bajo en 1");
  pa2m_afirmar(*(int *)(arbol->nodo_raiz->elemento) == 4, "El nodo raiz ahora apunta al numero 4");

  pa2m_afirmar(abb_quitar(arbol, &elemento3) == &elemento3, "Quitar un nodo con un hijo es exitoso");
  pa2m_afirmar(abb_tamanio(arbol) == 6, "La cantidad de elementos bajo en 1");

  pa2m_afirmar(abb_quitar(arbol, &elemento7) == &elemento7, "Quitar un nodo con dos hijos (no raiz) es exitoso");
  pa2m_afirmar(abb_tamanio(arbol) == 5, "La cantidad de elementos bajo en 1");
  abb_destruir(arbol);
}

void pruebas_de_busqueda_del_abb()
{
/*
 *               5
 *             /  \
 *            3    7
 *           / \  / \
 *          2  4 6   8
 *         /          \
 *        1            9
 */
  abb_t *arbol = abb_crear(comparador_aux);
  int elemento5 = 5; abb_insertar(arbol, &elemento5);
  int elemento3 = 3; abb_insertar(arbol, &elemento3);
  int elemento7 = 7; abb_insertar(arbol, &elemento7);
  int elemento2 = 2; abb_insertar(arbol, &elemento2);
  int elemento1 = 1; abb_insertar(arbol, &elemento1);
  int elemento4 = 4; abb_insertar(arbol, &elemento4);
  int elemento6 = 6; abb_insertar(arbol, &elemento6);
  int elemento8 = 8; abb_insertar(arbol, &elemento8);
  int elemento9 = 9; abb_insertar(arbol, &elemento9);

  pa2m_afirmar(!abb_buscar(arbol, NULL), "Buscar un elemento NULL devuelve NULL");
  pa2m_afirmar(abb_buscar(arbol, &elemento5) == &elemento5, "Se encontro el elemento del nodo raiz");
  pa2m_afirmar(abb_buscar(arbol, &elemento7) == &elemento7, "Se encontro el elemento en el medio del ABB");
  pa2m_afirmar(abb_buscar(arbol, &elemento1) == &elemento1, "Se encontro el elemento en un nodo hoja");
  abb_destruir(arbol);
}

void pruebas_de_destruccion()
{
  printf("Aca pruebo la funcion de destruccion...\n\
Creo 3 elementos con malloc, no deberia perder memoria\n");
  abb_t *arbol = abb_crear(comparador_aux);
  int *elemento1 = calloc(1, sizeof(int)); abb_insertar(arbol, elemento1);
  int *elemento2 = calloc(1, sizeof(int)); abb_insertar(arbol, elemento2);
  int *elemento3 = calloc(1, sizeof(int)); abb_insertar(arbol, elemento3);
  abb_destruir_todo(arbol, free);
}

void recorrer_elementos_del_abb()
{
/*
 *               5
 *             /  \
 *            3    7
 *           / \  / \
 *          2  4 6   8
 *         /          \
 *        1            9
 */
  abb_t *arbol = abb_crear(comparador_aux);
  int elemento5 = 5; abb_insertar(arbol, &elemento5);
  int elemento3 = 3; abb_insertar(arbol, &elemento3);
  int elemento7 = 7; abb_insertar(arbol, &elemento7);
  int elemento2 = 2; abb_insertar(arbol, &elemento2);
  int elemento1 = 1; abb_insertar(arbol, &elemento1);
  int elemento4 = 4; abb_insertar(arbol, &elemento4);
  int elemento6 = 6; abb_insertar(arbol, &elemento6);
  int elemento8 = 8; abb_insertar(arbol, &elemento8);
  int elemento9 = 9; abb_insertar(arbol, &elemento9);

  printf("  Recorrido Preorden: ");
  pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, comparador, &elemento4) == 5, "La funcion se invoco hasta encontrar el elemento 4");
  printf("  Recorrido Inorden: ");
  pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, comparador, &elemento5) == 5, "La funcion se invoco hasta encontrar el elemento 5");
  printf("  Recorrido Postorden: ");
  pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, comparador, &elemento6) == 5, "La funcion se invoco hasta encontrar el elemento 6");
  printf("\n");
  printf("  Recorrido Preorden: ");
  pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, comparador_null, NULL) == 9, "La funcion imprimio todos los elementos");
  printf("  Recorrido Inorden: ");
  pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, comparador_null, NULL) == 9, "La funcion imprimio todos los elementos");
  printf("  Recorrido Postorden: ");
  pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, comparador_null, NULL) == 9, "La funcion imprimio todos los elementos");
  abb_destruir(arbol);
}

void recorrer_elementos_guardandolos_en_vector()
{
/*
 *               5
 *             /  \
 *            3    7
 *           / \  / \
 *          2  4 6   8
 *         /          \
 *        1            9
 */
  abb_t *arbol = abb_crear(comparador_aux);
  int elemento5 = 5; abb_insertar(arbol, &elemento5);
  int elemento3 = 3; abb_insertar(arbol, &elemento3);
  int elemento7 = 7; abb_insertar(arbol, &elemento7);
  int elemento2 = 2; abb_insertar(arbol, &elemento2);
  int elemento1 = 1; abb_insertar(arbol, &elemento1);
  int elemento4 = 4; abb_insertar(arbol, &elemento4);
  int elemento6 = 6; abb_insertar(arbol, &elemento6);
  int elemento8 = 8; abb_insertar(arbol, &elemento8);
  int elemento9 = 9; abb_insertar(arbol, &elemento9);
  
  void *vector_int[9];
  pa2m_afirmar(abb_recorrer(arbol, PREORDEN, vector_int, 3) == 3, "La funcion recorrio 3 elementos");
  printf("  Recorrido Preorden: ");
  imprimir_vector(vector_int, 3);
  pa2m_afirmar(abb_recorrer(arbol, INORDEN, vector_int, 5) == 5, "La funcion recorrio 5 elementos");
  printf("  Recorrido Inorden: ");
  imprimir_vector(vector_int, 5);
  pa2m_afirmar(abb_recorrer(arbol, POSTORDEN, vector_int, 100) == 9, "La funcion recorrio todos los elementos \n  mandando cantidad > tamanio");
  printf("  Recorrido Postorden: ");
  imprimir_vector(vector_int, 9);
  abb_destruir(arbol);
}

void pruebas_con_un_abb_NULL()
{
  void *array[10];
  pa2m_afirmar(!abb_crear(NULL), "No se puede crear un abb sin mandarle comparador");
  pa2m_afirmar(!abb_insertar(NULL, NULL), "No se puede insertar en un abb NULL");
  pa2m_afirmar(!abb_quitar(NULL, NULL), "No se puede quitar un elemento de un abb NULL");
  pa2m_afirmar(!abb_buscar(NULL, NULL), "No se puede buscar un elemento en un abb NULL");
  pa2m_afirmar(abb_vacio(NULL), "Un abb NULL esta vacio");
  pa2m_afirmar(abb_tamanio(NULL) == 0, "El tamanio de un abb NULL es 0");
  pa2m_afirmar(!abb_con_cada_elemento(NULL, INORDEN, comparador, NULL), "No se puede recorrer un abb NULL (funcion)");
  pa2m_afirmar(!abb_recorrer(NULL, INORDEN, array, 100), "No se puede recorrer un abb NULL (array)");
}

// Llamadas a funciones.

void pruebas_abb_basicas()
{
  pa2m_nuevo_grupo("Pruebas de abb_crear()");
  se_puede_crear_el_abb_exitosamente();
  pa2m_nuevo_grupo("Pruebas de abb_insertar()");
  pruebas_de_insercion_del_abb();
  pa2m_nuevo_grupo("Pruebas de abb_quitar()");
  pruebas_de_extraccion_del_abb();
  pa2m_nuevo_grupo("Pruebas de abb_buscar()");
  pruebas_de_busqueda_del_abb();
  pa2m_nuevo_grupo("Pruebas de abb_destruir_todo()");
  pruebas_de_destruccion();
}

void pruebas_de_recorrido_con_funcion()
{
  pa2m_nuevo_grupo("Pruebas de abb_con_cada_elemento()");
  recorrer_elementos_del_abb();
}

void pruebas_de_recorrido_con_vector()
{
  pa2m_nuevo_grupo("Pruebas de abb_recorrer()");
  recorrer_elementos_guardandolos_en_vector();
}

void pruebas_abb_NULL()
{
  pa2m_nuevo_grupo("Pruebas del ABB NULL");
  pruebas_con_un_abb_NULL();
}

int main()
{
  pa2m_nuevo_grupo("Pruebas de ABB");
  pruebas_abb_basicas();
  pruebas_de_recorrido_con_funcion();
  pruebas_de_recorrido_con_vector();
  pruebas_abb_NULL();
  return pa2m_mostrar_reporte();
}
