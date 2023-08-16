#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

int comparador(void *a, void *b)
{
  if (!a || !b)
    return -1;

  int *_a = a;
  int *_b = b;

  return *_a == *_b;
}

bool comparador_interno(void *elemento, void *n)
{
  if (!elemento || !n)
    return false;
  
  int *a = elemento;
  int *b = n;

  if (*a == *b)
    return false;

  return true;
}

// Pruebas del TDA Pila

  // Prueba de creacion de pila

void crear_una_pila_me_devuelve_una_pila_de_tamanio_0_y_tope_nulo()
{
  pila_t *pila = pila_crear();

  pa2m_afirmar(pila != NULL, "La pila creada es valida");
  pa2m_afirmar(pila_vacia(pila), "La pila creada tiene tamanio 0");
  pa2m_afirmar(!pila_tope(pila), "La pila creada tiene tope NULL");

  pila_destruir(pila);
}

  // Pruebas de apilamiento de la pila

void apilar_un_elemento_incrementa_el_tamanio_de_la_pila_y_el_tope_es_el_ultimo_elemento_apilado()
{
  pila_t *pila = pila_crear();

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;

  pa2m_afirmar(pila_apilar(pila, &elemento1) != NULL, "Se pudo apilar el primer elemento");
  pa2m_afirmar(pila_tamanio(pila) == 1, "El tamanio de la pila es 1");
  pa2m_afirmar(pila_tope(pila) == &elemento1, "El tope de la pila es el correcto");

  pa2m_afirmar(pila_apilar(pila, &elemento2) != NULL, "Se pudo apilar el segundo elemento");
  pa2m_afirmar(pila_tamanio(pila) == 2, "El tamanio de la pila es 2");
  pa2m_afirmar(pila_tope(pila) == &elemento2, "El tope de la pila es el correcto");

  pa2m_afirmar(pila_apilar(pila, &elemento3) != NULL, "Se pudo apilar el tercer elemento");
  pa2m_afirmar(pila_tamanio(pila) == 3, "El tamanio de la pila es 3");
  pa2m_afirmar(pila_tope(pila) == &elemento3, "El tope de la pila es el correcto");

  pila_destruir(pila);
  printf("\n");
}

void apilar_un_elemento_nulo_apila_el_elemento()
{
  pila_t *pila = pila_crear();

  pa2m_afirmar(pila_apilar(pila, NULL) != NULL, "Se pudo apilar un elemento NULL");
  pa2m_afirmar(pila_tamanio(pila) == 1, "El tamanio de la pila incremento en 1");
  pa2m_afirmar(!pila_tope(pila), "El tope de la pila es NULL");

  pila_destruir(pila);
}

  // Pruebas de desapilamiento de la pila

void desapilar_un_elemento_disminuye_el_tamanio_de_la_pila_y_el_tope_es_el_elemento_anterior()
{
  pila_t *pila = pila_crear();

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;

  pila_apilar(pila, &elemento1);
  pila_apilar(pila, &elemento2);
  pila_apilar(pila, &elemento3);

  printf("Se apilaron 3 elementos para esta prueba\n\n");

  pa2m_afirmar(pila_desapilar(pila) == &elemento3, "Se desapilo el ultimo elemento");
  pa2m_afirmar(pila_tamanio(pila) == 2, "El tamanio de la pila es 2");
  pa2m_afirmar(pila_tope(pila) == &elemento2, "El tope de la pila es el correcto");

  pa2m_afirmar(pila_desapilar(pila) == &elemento2, "Se desapilo el ultimo elemento");
  pa2m_afirmar(pila_tamanio(pila) == 1, "El tamanio de la pila es 1");
  pa2m_afirmar(pila_tope(pila) == &elemento1, "El tope de la pila es el correcto");

  pa2m_afirmar(pila_desapilar(pila) == &elemento1, "Se desapilo el ultimo elemento");
  pa2m_afirmar(pila_vacia(pila), "La pila quedo vacia");
  pa2m_afirmar(!pila_tope(pila), "El tope de la pila es NULL");

  pila_destruir(pila);
  printf("\n");
}

void desapilar_en_una_pila_vacia_da_error()
{
  pila_t *pila = pila_crear();

  pa2m_afirmar(!pila_desapilar(pila), "No se pudo desapilar en una pila vacia");

  pila_destruir(pila);
}

  // Pruebas con una pila NULL

void pruebas_en_una_pila_NULL()
{
  int elemento = 10;

  pa2m_afirmar(!pila_apilar(NULL, &elemento), "No se pudo apilar en una pila NULL");
  pa2m_afirmar(!pila_desapilar(NULL), "No se pudo desapilar en una pila NULL");
  pa2m_afirmar(!pila_tope(NULL), "No existe un tope en una pila NULL");
  pa2m_afirmar(pila_tamanio(NULL) == 0, "El tamanio de la pila es 0");
  pa2m_afirmar(pila_vacia(NULL), "pila_vacia devuelve true");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// Pruebas del TDA Cola

  // Pruebas de creacion de cola

void crear_una_cola_me_devuelve_una_cola_de_tamanio_0_y_frente_nulo()
{
  cola_t *cola = cola_crear();

  pa2m_afirmar(cola != NULL, "La cola creada es valida");
  pa2m_afirmar(cola_vacia(cola), "La cola creada tiene tamanio 0");
  pa2m_afirmar(!cola_frente(cola), "La cola creada tiene frente NULL");

  cola_destruir(cola);
}

 // Pruebas de encolacion de la cola

void encolar_un_elemento_incrementa_el_tamanio_de_la_cola_y_el_frente_es_el_primer_elemento_encolado()
{
  cola_t *cola = cola_crear();

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;

  pa2m_afirmar(cola_encolar(cola, &elemento1) != NULL, "Se pudo encolar el primer elemento");
  pa2m_afirmar(cola_tamanio(cola) == 1, "El tamanio de la cola es 1");
  pa2m_afirmar(cola_frente(cola) == &elemento1, "El frente de la cola es el correcto");

  pa2m_afirmar(cola_encolar(cola, &elemento2) != NULL, "Se pudo encolar el segundo elemento");
  pa2m_afirmar(cola_tamanio(cola) == 2, "El tamanio de la cola es 2");
  pa2m_afirmar(cola_frente(cola) == &elemento1, "El frente de la cola es el correcto");

  pa2m_afirmar(cola_encolar(cola, &elemento3) != NULL, "Se pudo encolar el tercer elemento");
  pa2m_afirmar(cola_tamanio(cola) == 3, "El tamanio de la cola es 3");
  pa2m_afirmar(cola_frente(cola) == &elemento1, "El frente de la cola es el correcto");

  cola_destruir(cola);
  printf("\n");
}

void encolar_un_elemento_nulo_encola_el_elemento()
{
  cola_t *cola = cola_crear();

  pa2m_afirmar(cola_encolar(cola, NULL) != NULL, "Se pudo encolar un elemento NULL");
  pa2m_afirmar(cola_tamanio(cola) == 1, "El tamanio de la cola incremento en 1");
  pa2m_afirmar(!cola_frente(cola), "El frente de la cola es NULL");

  cola_destruir(cola);
}

 // Pruebas de desencolacion de la cola

void desencolar_un_elemento_disminuye_el_tamanio_de_la_cola_y_el_frente_es_el_elemento_siguiente()
{
  cola_t *cola = cola_crear();

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;

  cola_encolar(cola, &elemento1);
  cola_encolar(cola, &elemento2);
  cola_encolar(cola, &elemento3);

  printf("Se encolaron 3 elementos para esta prueba\n\n");

  pa2m_afirmar(cola_desencolar(cola) == &elemento1, "Se desencolo el primer elemento");
  pa2m_afirmar(cola_tamanio(cola) == 2, "El tamanio de la cola es 2");
  pa2m_afirmar(cola_frente(cola) == &elemento2, "El frente de la cola es el correcto");

  pa2m_afirmar(cola_desencolar(cola) == &elemento2, "Se desencolo el segundo elemento");
  pa2m_afirmar(cola_tamanio(cola) == 1, "El tamanio de la cola es 1");
  pa2m_afirmar(cola_frente(cola) == &elemento3, "El frente de la cola es el correcto");

  pa2m_afirmar(cola_desencolar(cola) == &elemento3, "Se desencolo el tercer elemento");
  pa2m_afirmar(cola_vacia(cola), "La cola quedo vacia");
  pa2m_afirmar(!cola_frente(cola), "El frente de la cola es NULL");

  cola_destruir(cola);
  printf("\n");
}

void desencolar_en_una_cola_vacia_da_error()
{
  cola_t *cola = cola_crear();

  pa2m_afirmar(!cola_desencolar(cola), "No se pudo desencolar en una cola vacia");

  cola_destruir(cola);
}

  // Pruebas con una cola NULL

void pruebas_en_una_cola_NULL()
{
  int elemento = 10;

  pa2m_afirmar(!cola_encolar(NULL, &elemento), "No se pudo encolar en una cola NULL");
  pa2m_afirmar(!cola_desencolar(NULL), "No se pudo desencolar en una cola NULL");
  pa2m_afirmar(!cola_frente(NULL), "No existe un frente en una cola NULL");
  pa2m_afirmar(cola_tamanio(NULL) == 0, "El tamanio de la cola es 0");
  pa2m_afirmar(cola_vacia(NULL), "cola_vacia devuelve true");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// Pruebas del TDA Lista

  // Pruebas de creacion de lista

void crear_una_lista_me_devuelve_una_lista_de_tamanio_0_y_nodos_nulos()
{
  lista_t *lista = lista_crear();

  pa2m_afirmar(lista != NULL, "La lista creada es valida");
  pa2m_afirmar(lista_vacia(lista), "La lista creada tiene tamanio 0");
  pa2m_afirmar(!lista_primero(lista), "El primer elemento de la lista es NULL");
  pa2m_afirmar(!lista_ultimo(lista), "El ultimo elemento de la lista es NULL");

  lista_destruir(lista);
}

  // Pruebas de enlistado de la lista

void enlistar_un_elemento_incrementa_el_tamanio_de_la_lista_y_sus_nodos_apuntan_correctamente()
{
  lista_t *lista = lista_crear();

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;

  printf("Estas pruebas agregan un elemento al final de la lista\n\n");

  pa2m_afirmar(lista_insertar(lista, &elemento1) != NULL, "Se pudo enlistar el primer elemento");
  pa2m_afirmar(lista_tamanio(lista) == 1, "El tamanio de la lista es 1");
  pa2m_afirmar(lista_primero(lista) == &elemento1, "nodo_inicio apunta al primer nodo");
  pa2m_afirmar(lista_ultimo(lista) == &elemento1, "nodo_final apunta al ultimo nodo");

  pa2m_afirmar(lista_insertar(lista, &elemento2) != NULL, "Se pudo enlistar el segundo elemento");
  pa2m_afirmar(lista_tamanio(lista) == 2, "El tamanio de la lista es 2");
  pa2m_afirmar(lista_primero(lista) == &elemento1, "nodo_inicio apunta al primer nodo");
  pa2m_afirmar(lista_ultimo(lista) == &elemento2, "nodo_final apunta al ultimo nodo");

  pa2m_afirmar(lista_insertar(lista, &elemento3) != NULL, "Se pudo enlistar el tercer elemento");
  pa2m_afirmar(lista_tamanio(lista) == 3, "El tamanio de la lista es 3");
  pa2m_afirmar(lista_primero(lista) == &elemento1, "nodo_inicio apunta al primer nodo");
  pa2m_afirmar(lista_ultimo(lista) == &elemento3, "nodo_final apunta al ultimo nodo");

  lista_destruir(lista);
  printf("\n");
}

void enlistar_un_elemento_nulo_enlista_el_elemento()
{
  lista_t *lista = lista_crear();

  pa2m_afirmar(lista_insertar(lista, NULL) != NULL, "Se pudo enlistar un elemento NULL");
  pa2m_afirmar(lista_tamanio(lista) == 1, "El tamanio de la lista incremento en 1");
  pa2m_afirmar(!lista_ultimo(lista), "El ultimo elemento de la lista es NULL");

  lista_destruir(lista);
}

void enlistar_un_elemento_en_cualquier_lugar_de_la_lista_funciona_correctamente()
{
  lista_t *lista = lista_crear();

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;
  int elemento4 = 4;
  int elemento5 = 5;
  int elemento6 = 6;
  int elemento7 = 7;

  lista_insertar(lista, &elemento1);
  lista_insertar(lista, &elemento2);
  lista_insertar(lista, &elemento3);

  printf("Para esta prueba se insertaron 3 elementos al final de la lista previamente\n\n");

  pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento4, 0) != NULL, "Se pudo insertar el elemento en la lista");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &elemento4, "El elemento se inserto en la primer posicion correctamente");
  pa2m_afirmar(lista_tamanio(lista) == 4, "El tamanio de la lista es 4");
  pa2m_afirmar(lista_primero(lista) == &elemento4, "El primer elemento es el correcto");
  pa2m_afirmar(lista_ultimo(lista) == &elemento3, "El ultimo elemento es el correcto");

  pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento5, 3) != NULL, "Se pudo insertar el elemento en la lista");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == &elemento5, "El elemento se inserto en la tercer posicion correctamente");
  pa2m_afirmar(lista_tamanio(lista) == 5, "El tamanio de la lista es 5");
  pa2m_afirmar(lista_primero(lista) == &elemento4, "El primer elemento es el correcto");
  pa2m_afirmar(lista_ultimo(lista) == &elemento3, "El ultimo elemento es el correcto");

  pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento6, 5) != NULL, "Se pudo insertar el elemento en la lista");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 5) == &elemento6, "El elemento se inserto en la ultima posicion correctamente");
  pa2m_afirmar(lista_tamanio(lista) == 6, "El tamanio de la lista es 6");
  pa2m_afirmar(lista_primero(lista) == &elemento4, "El primer elemento es el correcto");
  pa2m_afirmar(lista_ultimo(lista) == &elemento6, "El ultimo elemento es el correcto");

  pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento7, 10000) != NULL, "Se pudo insertar el elemento en la lista mandando posicion > lista->cantidad");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 6) == &elemento7, "El elemento se inserto en la ultima posicion correctamente");
  pa2m_afirmar(lista_tamanio(lista) == 7, "El tamanio de la lista es 7");
  pa2m_afirmar(lista_primero(lista) == &elemento4, "El primer elemento es el correcto");
  pa2m_afirmar(lista_ultimo(lista) == &elemento7, "El ultimo elemento es el correcto");

  lista_destruir(lista);
  printf("\n");
}

void enlistar_un_elemento_NULL_en_cualquier_lugar_de_la_lista_enlista_un_elemento_NULL()
{
  lista_t *lista = lista_crear();

  int elemento = 10;

  lista_insertar(lista, &elemento);

  pa2m_afirmar(lista_insertar_en_posicion(lista, NULL, 0) != NULL, "Se pudo enlistar un elemento NULL");
  pa2m_afirmar(lista_tamanio(lista) == 2, "El tamanio de la lista incremento en 1");
  pa2m_afirmar(!lista_elemento_en_posicion(lista, 0), "El nodo de la lista es NULL");

  lista_destruir(lista);
}

  // Pruebas de deslistado de la lista

void deslistar_un_elemento_disminuye_el_tamanio_de_la_lista_y_los_nodos_apuntan_correctamante()
{
  lista_t *lista = lista_crear();

  int elemento1 = 1;
  int elemento2 = 2; 
  int elemento3 = 3;

  lista_insertar(lista, &elemento1);
  lista_insertar(lista, &elemento2);
  lista_insertar(lista, &elemento3);

  printf("Se enlistaron 3 elementos para esta prueba\n");
  printf("Estas pruebas eliminan el ultimo elemento en la lista\n\n");

  pa2m_afirmar(lista_quitar(lista) == &elemento3, "Se deslisto el ultimo elemento");
  pa2m_afirmar(lista_tamanio(lista) == 2, "El tamanio de la lista es 2");
  pa2m_afirmar(lista_ultimo(lista) == &elemento2, "El ultimo elemento es el correcto");

  pa2m_afirmar(lista_quitar(lista) == &elemento2, "Se deslisto el ultimo elemento");
  pa2m_afirmar(lista_tamanio(lista) == 1, "El tamanio de la lista es 1");
  pa2m_afirmar(lista_ultimo(lista) == &elemento1, "El ultimo elemento es el correcto");

  pa2m_afirmar(lista_quitar(lista) == &elemento1, "Se deslisto el ultimo elemento");
  pa2m_afirmar(lista_vacia(lista), "La lista quedo vacia");
  pa2m_afirmar(!lista_primero(lista), "nodo_inicio es NULL");
  pa2m_afirmar(!lista_ultimo(lista), "nodo_final es NULL");

  lista_destruir(lista);
  printf("\n");
}

void deslistar_en_una_lista_vacia_da_error()
{
  lista_t *lista = lista_crear();

  pa2m_afirmar(!lista_quitar(lista), "No se pudo quitar el ultimo elemento en una lista vacia");

  lista_destruir(lista);
}

void deslistar_un_elemento_en_cualquier_lugar_de_la_lista_funciona_correctamante()
{
  lista_t *lista = lista_crear();

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;
  int elemento4 = 4;
  int elemento5 = 5;

  lista_insertar(lista, &elemento1);
  lista_insertar(lista, &elemento2);
  lista_insertar(lista, &elemento3);
  lista_insertar(lista, &elemento4);
  lista_insertar(lista, &elemento5);

  printf("Se enlistaron 5 elementos para esta prueba\n\n");

  pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == &elemento1, "El primer elemento fue deslistado correctamente");
  pa2m_afirmar(lista_primero(lista) == &elemento2, "El elemento siguiente tomo su lugar");
  pa2m_afirmar(lista_tamanio(lista) == 4, "El tamanio de la lista disminuyo en 1");

  pa2m_afirmar(lista_quitar_de_posicion(lista, 2) == &elemento4, "El tercer elemento fue deslistado correctamente");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == &elemento5, "El elemento siguiente tomo su lugar");
  pa2m_afirmar(lista_tamanio(lista) == 3, "El tamanio de la lista disminuyo en 1");

  pa2m_afirmar(lista_quitar_de_posicion(lista, 2) == &elemento5, "El ultimo elemento fue deslistado correctamente");
  pa2m_afirmar(lista_ultimo(lista) == &elemento3, "El elemento anterior es el nuevo final");
  pa2m_afirmar(lista_tamanio(lista) == 2, "El tamanio de la lista disminuyo en 1");

  pa2m_afirmar(lista_quitar_de_posicion(lista, 1000) == &elemento3, "El ultimo elemento fue deslistado correctamente mandando posicion > lista->cantidad");
  pa2m_afirmar(lista_ultimo(lista) == &elemento2, "El elemento anterior es el nuevo final");
  pa2m_afirmar(lista_tamanio(lista) == 1, "El tamanio de la lista disminuyo en 1");

  lista_destruir(lista);
  printf("\n");
}

void deslistar_en_una_lista_vacia_con_posicion_da_error()
{
  lista_t *lista = lista_crear();

  pa2m_afirmar(!lista_quitar_de_posicion(lista, 0), "No se pudo quitar un elemento de una lista vacia");

  lista_destruir(lista);
}

  // Pruebas con una lista NULL

void pruebas_en_una_lista_NULL()
{
  int elemento = 10;

  pa2m_afirmar(!lista_insertar(NULL, &elemento), "No se puede insertar un elemento en una lista NULL");
  pa2m_afirmar(!lista_insertar_en_posicion(NULL, &elemento, 0), "No se puede insertar un elemento en posiicon x en una lista NULL");
  pa2m_afirmar(!lista_quitar(NULL), "No se puede quitar un elemento en una lista NULL");
  pa2m_afirmar(!lista_quitar_de_posicion(NULL, 0), "No se puede quitar un elemento en posicion x en una lista NULL");
  pa2m_afirmar(!lista_elemento_en_posicion(NULL, 0), "No se puede devolver la posicion de un elemento en posicion en una lista NULL");
  pa2m_afirmar(!lista_buscar_elemento(NULL, comparador, &elemento), "No se puede buscar un elemento en una lista NULL");
  pa2m_afirmar(!lista_primero(NULL), "No se puede obtener el primer elemento de una lista NULL");
  pa2m_afirmar(!lista_ultimo(NULL), "No se puede obtener el ultimo elemento de una lista NULL");
  pa2m_afirmar(lista_vacia(NULL), "lista_vacia devuelve true al haber 0 elementos");
  pa2m_afirmar(lista_tamanio(NULL) == 0, "El tamanio de la lista NULL es 0");
}

  // Pruebas con el iterador externo

void crear_un_iterador_devuelve_un_iterador_con_una_lista_y_su_corriente_inicializada()
{
  lista_t *lista = lista_crear();

  int elemento1 = 1;
  int elemento2 = 2;

  lista_insertar(lista, &elemento1);
  lista_insertar(lista, &elemento2);

  lista_iterador_t *it = lista_iterador_crear(lista);

  pa2m_afirmar(it != NULL, "El iterador creado es valido");
  pa2m_afirmar(lista_iterador_elemento_actual(it) == &elemento1, "El iterador apunta al primer elemento de la lista");

  lista_iterador_destruir(it);
  lista_destruir(lista);
}

void la_navegacion_del_iterador_funciona_correctamente()
{
  lista_t *lista = lista_crear();

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;
  int elemento4 = 4;
  int elemento5 = 5;

  lista_insertar(lista, &elemento1);
  lista_insertar(lista, &elemento2);
  lista_insertar(lista, &elemento3);
  lista_insertar(lista, &elemento4);
  lista_insertar(lista, &elemento5);
  
  lista_iterador_t *it = lista_iterador_crear(lista);

  printf("Se creo un iterador en una lista con 5 elementos\n\n");

  pa2m_afirmar(lista_iterador_elemento_actual(it) == &elemento1, "El iterador se encuentra en la posicion 0");
  pa2m_afirmar(lista_iterador_tiene_siguiente(it), "Existe una posicion siguiente a la posicion 0");

  pa2m_afirmar(lista_iterador_avanzar(it), "El iterador se movio una posicion");
  pa2m_afirmar(lista_iterador_elemento_actual(it) == &elemento2, "El iterador se encuentra en la posicion 1");
  pa2m_afirmar(lista_iterador_tiene_siguiente(it), "Existe una posicion siguiente a la posicion 1");

  pa2m_afirmar(lista_iterador_avanzar(it), "El iterador se movio una posicion");
  pa2m_afirmar(lista_iterador_elemento_actual(it) == &elemento3, "El iterador se encuentra en la posicion 2");
  pa2m_afirmar(lista_iterador_tiene_siguiente(it), "Existe una posicion siguiente a la posicion 2");

  pa2m_afirmar(lista_iterador_avanzar(it), "El iterador se movio una posicion");
  pa2m_afirmar(lista_iterador_elemento_actual(it) == &elemento4, "El iterador se encuentra en la posicion 3");
  pa2m_afirmar(lista_iterador_tiene_siguiente(it), "Existe una posicion siguiente a la posicion 3");

  pa2m_afirmar(lista_iterador_avanzar(it), "El iterador se movio una posicion");
  pa2m_afirmar(lista_iterador_elemento_actual(it) == &elemento5, "El iterador se encuentra en la posicion 4 (ultima)");
  pa2m_afirmar(lista_iterador_tiene_siguiente(it), "Existe una posicion siguiente a la posicion 4 (NULL)");

  pa2m_afirmar(!lista_iterador_avanzar(it), "El iterador se movio de su ultima posicion y devolvio false");
  pa2m_afirmar(!lista_iterador_elemento_actual(it), "El iterador es == NULL");
  pa2m_afirmar(!lista_iterador_tiene_siguiente(it), "No existe una posicion siguiente");

  lista_iterador_destruir(it);
  lista_destruir(lista);
}

  // Pruebas con un iterador NULL

void pruebas_con_un_iterador_NULL()
{
  lista_iterador_t *it = lista_iterador_crear(NULL);

  pa2m_afirmar(!it, "No se puede crear un iterador a partir de una lista NULL");
  pa2m_afirmar(!lista_iterador_tiene_siguiente(NULL), "No se puede saber si un iterador NULL tiene siguiente");
  pa2m_afirmar(!lista_iterador_avanzar(NULL), "No se puede avanzar en una lista mandando un iterador NULL");
  pa2m_afirmar(!lista_iterador_elemento_actual(NULL), "El elemento actual es NULL mandando un iterador NULL");

  lista_iterador_destruir(it);
}

  // Pruebas con el iterador interno

void pruebas_del_iterador_interno()
{
  lista_t *lista = lista_crear();

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;
  int elemento4 = 4;
  int elemento5 = 5;

  int elemento0 = 0;

  lista_insertar(lista, &elemento1);
  lista_insertar(lista, &elemento2);
  lista_insertar(lista, &elemento3);
  lista_insertar(lista, &elemento4);
  lista_insertar(lista, &elemento5);

  size_t cant_iterados;

  cant_iterados = lista_con_cada_elemento(lista, comparador_interno, &elemento5);
  pa2m_afirmar(cant_iterados == elemento5, "El iterador interno pasa por todos los elementos");

  cant_iterados = lista_con_cada_elemento(lista, comparador_interno, &elemento4);
  pa2m_afirmar(cant_iterados == elemento4, "El iterador interno paso por 4 elementos");

  cant_iterados = lista_con_cada_elemento(lista, comparador_interno, &elemento3);
  pa2m_afirmar(cant_iterados == elemento3, "El iterador interno paso por 3 elementos");

  cant_iterados = lista_con_cada_elemento(lista, comparador_interno, &elemento2);
  pa2m_afirmar(cant_iterados == elemento2, "El iterador interno paso por 2 elementos");

  cant_iterados = lista_con_cada_elemento(lista, comparador_interno, &elemento1);
  pa2m_afirmar(cant_iterados == elemento1, "El iterador interno paso por 1 elementos");

  cant_iterados = lista_con_cada_elemento(lista, comparador_interno, &elemento0);
  pa2m_afirmar(cant_iterados == elemento5, "El iterador interno devuelve la cantidad de elementos\n  total de la lista cuando se manda un elemento inexistente");

  pa2m_afirmar(!lista_con_cada_elemento(NULL, comparador_interno, &elemento5), "Listar todos los elementos devuelve NULL mandando una lista NULL");

  lista_destruir(lista);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// Funciones a pruebas de los distintos TDAs

void pruebas_de_pila()
{
  pa2m_nuevo_grupo("Pruebas del TDA Pila");

  pa2m_nuevo_grupo("Pruebas de creacion de pila");
  crear_una_pila_me_devuelve_una_pila_de_tamanio_0_y_tope_nulo();

  pa2m_nuevo_grupo("Pruebas de apilamiento");
  apilar_un_elemento_incrementa_el_tamanio_de_la_pila_y_el_tope_es_el_ultimo_elemento_apilado();
  apilar_un_elemento_nulo_apila_el_elemento();

  pa2m_nuevo_grupo("Pruebas de desapilamiento");
  desapilar_un_elemento_disminuye_el_tamanio_de_la_pila_y_el_tope_es_el_elemento_anterior();
  desapilar_en_una_pila_vacia_da_error();

  pa2m_nuevo_grupo("Pruebas con una pila NULL");
  pruebas_en_una_pila_NULL();
}

void pruebas_de_cola()
{
  pa2m_nuevo_grupo("Pruebas del TDA Cola");

  pa2m_nuevo_grupo("Pruebas de creacion de cola");
  crear_una_cola_me_devuelve_una_cola_de_tamanio_0_y_frente_nulo();

  pa2m_nuevo_grupo("Pruebas de encolamiento");
  encolar_un_elemento_incrementa_el_tamanio_de_la_cola_y_el_frente_es_el_primer_elemento_encolado();
  encolar_un_elemento_nulo_encola_el_elemento();

  pa2m_nuevo_grupo("Pruebas de desencolamiento");
  desencolar_un_elemento_disminuye_el_tamanio_de_la_cola_y_el_frente_es_el_elemento_siguiente();
  desencolar_en_una_cola_vacia_da_error();

  pa2m_nuevo_grupo("Pruebas con una cola NULL");
  pruebas_en_una_cola_NULL();
}

void pruebas_de_lista()
{
  pa2m_nuevo_grupo("Pruebas del TDA Lista");

  pa2m_nuevo_grupo("Pruebas de creacion de lista");
  crear_una_lista_me_devuelve_una_lista_de_tamanio_0_y_nodos_nulos();

  pa2m_nuevo_grupo("Pruebas de enlistado");
  enlistar_un_elemento_incrementa_el_tamanio_de_la_lista_y_sus_nodos_apuntan_correctamente();
  enlistar_un_elemento_nulo_enlista_el_elemento();

  pa2m_nuevo_grupo("Pruebas de enlistado con posicion");
  enlistar_un_elemento_en_cualquier_lugar_de_la_lista_funciona_correctamente();
  enlistar_un_elemento_NULL_en_cualquier_lugar_de_la_lista_enlista_un_elemento_NULL();

  pa2m_nuevo_grupo("Pruebas de deslistado");
  deslistar_un_elemento_disminuye_el_tamanio_de_la_lista_y_los_nodos_apuntan_correctamante();
  deslistar_en_una_lista_vacia_da_error();

  pa2m_nuevo_grupo("Pruebas de deslistado con posicion");
  deslistar_un_elemento_en_cualquier_lugar_de_la_lista_funciona_correctamante();
  deslistar_en_una_lista_vacia_con_posicion_da_error();

  pa2m_nuevo_grupo("Pruebas con una lista NULL");
  pruebas_en_una_lista_NULL();

  pa2m_nuevo_grupo("Pruebas del Iterador");

  pa2m_nuevo_grupo("Pruebas de creacion del iterador externo");
  crear_un_iterador_devuelve_un_iterador_con_una_lista_y_su_corriente_inicializada();

  pa2m_nuevo_grupo("Pruebas de navegacion del iterador externo");
  la_navegacion_del_iterador_funciona_correctamente();

  pa2m_nuevo_grupo("Pruebas con un iterador NULL");
  pruebas_con_un_iterador_NULL();

  pa2m_nuevo_grupo("Pruebas del iterador interno");
  pruebas_del_iterador_interno();

}

int main() {
  
  pruebas_de_pila();
  pruebas_de_cola();
  pruebas_de_lista();

  return pa2m_mostrar_reporte();
}