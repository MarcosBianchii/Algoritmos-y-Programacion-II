#include "abb.h"

#include <stddef.h>
#include <stdlib.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if (!comparador)
		return NULL;

	abb_t *arbol = calloc(1, sizeof(abb_t));
	arbol->comparador = comparador;
	return arbol;
}
/*
//	Procedimiento que agrega una hoja al arbol y guarda el elemento pasado
//	por parametro en ella.
//
//	Solo puede ser NULL el puntero a elemento.
*/
static nodo_abb_t *insertar_hoja(abb_t *arbol, nodo_abb_t *raiz, void *elemento)
{
	if (!raiz){
		nodo_abb_t *nueva_hoja = calloc(1, sizeof(nodo_abb_t));
		if (!nueva_hoja)
			return NULL;
		nueva_hoja->elemento = elemento;
		(arbol->tamanio)++;
		return nueva_hoja;
	}

	if (arbol->comparador(raiz->elemento, elemento) >= 0)
		raiz->izquierda = insertar_hoja(arbol, raiz->izquierda, elemento);
	else raiz->derecha = insertar_hoja(arbol, raiz->derecha, elemento);
	return raiz;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;
	
	nodo_abb_t *raiz = insertar_hoja(arbol, arbol->nodo_raiz, elemento);
	if (!raiz)
		return NULL;
	
	arbol->nodo_raiz = raiz;
	return arbol;	
}
/*
//	Procedimiento que devuelve un puntero al predecesor y
//	"engancha" su hijo izquierdo en caso de existir.
//
//	Recibe punteros no NULL.
*/
static nodo_abb_t *obtener_predecesor(nodo_abb_t *raiz, nodo_abb_t **nodo)
{
	if (!(raiz->derecha)){
		*nodo = raiz;
		return raiz->izquierda;
	}
	raiz->derecha = obtener_predecesor(raiz->derecha, nodo);
	return raiz;
}
/*
//	Procedimiento que elimina un elemento del arbol.
//
//	Solo puede ser NULL el puntero a elemento.
*/
static nodo_abb_t *quitar_nodo(abb_t *arbol, nodo_abb_t *raiz,
			       void *elemento, void **borrado)
{
	if (!raiz)
		return NULL;
	int comparacion = arbol->comparador(raiz->elemento, elemento);
	if (comparacion > 0)
		raiz->izquierda = quitar_nodo(arbol, raiz->izquierda, elemento, borrado);
	else if (comparacion < 0)
		raiz->derecha = quitar_nodo(arbol, raiz->derecha, elemento, borrado);
	else {
		*borrado = raiz->elemento;
		nodo_abb_t *izq = raiz->izquierda;
		nodo_abb_t *der = raiz->derecha;
		(arbol->tamanio)--;
		if (izq && der){
			nodo_abb_t *nodo = NULL;
			raiz->izquierda = obtener_predecesor(izq, &nodo);
			raiz->elemento = nodo->elemento;
			free(nodo);
			return raiz;
		}
		free(raiz);
		if (!izq)
			return der;
		return izq;
	}
	return raiz;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;

	void *borrado = NULL;
	arbol->nodo_raiz = quitar_nodo(arbol, arbol->nodo_raiz, elemento, &borrado);
	return borrado;
}
/*
//	Procedimiento que buscar en el arbol hasta encontrar un elemnto
//	igual al pasado por parametro.
//
//	Solo puede ser NULL el puntero a elemento.
*/
static void *buscar_elemento(abb_t *arbol, nodo_abb_t *raiz, void *elemento)
{
	if (!raiz)
		return NULL;

	int comparacion = arbol->comparador(raiz->elemento, elemento);
	if (comparacion > 0)
		return buscar_elemento(arbol, raiz->izquierda, elemento);
	if (comparacion < 0)
		return buscar_elemento(arbol, raiz->derecha, elemento);
	else return raiz->elemento;
	return NULL;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;
	if (abb_vacio(arbol))
		return NULL;
	return buscar_elemento(arbol, arbol->nodo_raiz, elemento);
}

bool abb_vacio(abb_t *arbol)
{
	if (!arbol)
		return true;
	if (arbol->tamanio > 0)
		return false;
	return true;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (!arbol)
		return 0;
	return arbol->tamanio;
}
/*
//	Procedimiento que itera sobre el arbol y lo recorre en el
//	orden que recibe por parametro.
//
//	Guarda en una variable la cantidad de iteraciones.
*/
static void recorrer_abb_con_funcion(nodo_abb_t *raiz, abb_recorrido recorrido,
				     bool (*funcion)(void *, void *), void *aux,
				     size_t *iterados, bool *exit)
{
	if (!raiz)
		return;
	
	if (*exit) return;
	if (recorrido == PREORDEN){
		(*iterados)++;
		if (!funcion(raiz->elemento, aux)){
			*exit = true;
			return;
		}
	}
	recorrer_abb_con_funcion(raiz->izquierda, recorrido, funcion, aux, iterados, exit);
	if (*exit) return;
	if (recorrido == INORDEN){
		(*iterados)++;
		if (!funcion(raiz->elemento, aux)){
			*exit = true;
			return;
		}
	}
	recorrer_abb_con_funcion(raiz->derecha, recorrido, funcion, aux, iterados, exit);
	if (*exit) return;
	if (recorrido == POSTORDEN){
		(*iterados)++;
		if (!funcion(raiz->elemento, aux)){
			*exit = true;
			return;
		}
	}
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!arbol || !funcion) 
		return 0;
	
	size_t iterados = 0;
	bool exit = false;
	recorrer_abb_con_funcion(arbol->nodo_raiz, recorrido, funcion, aux, &iterados, &exit);
	return iterados;
}
/*
//	Procedimiento que itera sobre el arbol y lo recorre en el
//	orden que recibe por parametro.
//
//	No recibe punteros NULL.
*/
static void iterar_arbol(nodo_abb_t *raiz, abb_recorrido recorrido,
			 void **array, size_t tamanio, size_t *iterados)
{
	if (!raiz)
		return;
	if (tamanio == *iterados) return;
	if (recorrido == PREORDEN){
		array[*iterados] = raiz->elemento;
		(*iterados)++;
	}
	iterar_arbol(raiz->izquierda, recorrido, array, tamanio, iterados);
	if (tamanio == *iterados) return;
	if (recorrido == INORDEN){
		array[*iterados] = raiz->elemento;
		(*iterados)++;
	}
	iterar_arbol(raiz->derecha, recorrido, array, tamanio, iterados);
	if (tamanio == *iterados) return;
	if (recorrido == POSTORDEN){
		array[*iterados] = raiz->elemento;
		(*iterados)++;
	}
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (!arbol || !array || tamanio_array == 0)
		return 0;

	size_t iterados = 0;
	iterar_arbol(arbol->nodo_raiz, recorrido, array, tamanio_array, &iterados);
	return iterados;
}
/*
//	Destruye el arbol.
//
//	De ser NULL el destructor solo libera los nodos.
*/
static void arbol_destruir(nodo_abb_t *raiz, void (*destructor)(void *))
{
	if (!raiz)
		return;

	arbol_destruir(raiz->izquierda, destructor);
	arbol_destruir(raiz->derecha, destructor);
	if (destructor)
		destructor(raiz->elemento);
	free(raiz);
}

void abb_destruir(abb_t *arbol)
{
	abb_destruir_todo(arbol, NULL);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol)
		return;

	arbol_destruir(arbol->nodo_raiz, destructor);
	free(arbol);
}