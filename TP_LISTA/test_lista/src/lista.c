#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

lista_t *lista_crear()
{
	return calloc(1, sizeof(lista_t));
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return NULL;

	nodo_t *nodo_nuevo = calloc(1, sizeof(nodo_t));
	if (!nodo_nuevo)
		return NULL;

	nodo_nuevo->elemento = elemento;

	if (lista->cantidad == 0)
		lista->nodo_inicio = nodo_nuevo;
	else
		lista->nodo_fin->siguiente = nodo_nuevo;

	lista->nodo_fin = nodo_nuevo;	
	lista->cantidad++;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (!lista)
		return NULL;
	if (posicion >= lista->cantidad)
		return lista_insertar(lista, elemento);

	nodo_t *nodo_nuevo = malloc(sizeof(nodo_t));
	if (!nodo_nuevo)
		return NULL;
	
	nodo_nuevo->elemento = elemento;

	if (posicion == 0){
		nodo_nuevo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_nuevo;
	
		lista->cantidad++;
		return lista;
	}
	
	nodo_t *nodo_iterador = lista->nodo_inicio;
	size_t contador = 0;

	while(contador < (posicion - 1)){
		nodo_iterador = nodo_iterador->siguiente;
		contador++;
	}

	nodo_nuevo->siguiente = nodo_iterador->siguiente;
	nodo_iterador->siguiente = nodo_nuevo;
	lista->cantidad++;

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (!lista)
		return NULL;
	if (lista_vacia(lista))
		return NULL;

	if (lista->cantidad == 1){
		void *elemento_deslistado = lista->nodo_inicio->elemento;

		free(lista->nodo_fin);

		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		lista->cantidad--;

		return elemento_deslistado;
	}

	nodo_t *nodo_iterador = lista->nodo_inicio;
	size_t contador = 0;

	while(contador < (lista->cantidad - 2)){
		nodo_iterador = nodo_iterador->siguiente;
		contador++;
	}

	void *elemento_deslistado = lista->nodo_fin->elemento;

	free(lista->nodo_fin);

	lista->nodo_fin = nodo_iterador;
	lista->nodo_fin->siguiente = NULL;
	lista->cantidad--;

	return elemento_deslistado;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista)
		return NULL;
	if (lista_vacia(lista))
		return NULL;

	if (posicion >= (lista->cantidad - 1))
		return lista_quitar(lista);

	if (posicion == 0){
		void *elemento_deslistado = lista->nodo_inicio->elemento;
		nodo_t *aux = lista->nodo_inicio;
		lista->nodo_inicio = aux->siguiente;
		
		free(aux);

		lista->cantidad--;

		return elemento_deslistado;
	}
	
	nodo_t *nodo_iterador = lista->nodo_inicio;
	size_t contador = 0;

	while(contador < (posicion - 1)){
		nodo_iterador = nodo_iterador->siguiente;
		contador++;
	}

	void *elemento_deslistado = nodo_iterador->siguiente->elemento;
	nodo_t *aux = nodo_iterador->siguiente->siguiente;

	free(nodo_iterador->siguiente);

	nodo_iterador->siguiente = aux;
	lista->cantidad--;
	
	return elemento_deslistado;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista)
		return NULL;
	if (posicion >= lista->cantidad)
		return NULL;
	
	nodo_t *nodo_iterador = lista->nodo_inicio;
	size_t contador = 0;

	while(contador < posicion){
		nodo_iterador = nodo_iterador->siguiente;
		contador++;
	}

	return nodo_iterador->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (!lista || !comparador)
		return NULL;

	nodo_t *nodo_iterador = lista->nodo_inicio;

	while(nodo_iterador){
		if (comparador(nodo_iterador->elemento, contexto) == 0)
			return nodo_iterador->elemento;
		
		nodo_iterador = nodo_iterador->siguiente;
	}

	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if (!lista)
		return NULL;
	if (!(lista->nodo_inicio))
		return NULL;

	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (!lista)
		return NULL;
	if (!(lista->nodo_fin))
		return NULL;

	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{
	if (!lista)
		return true;

	return (lista->cantidad == 0);
}

size_t lista_tamanio(lista_t *lista)
{
	if (!lista)
		return 0;
	
	return lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	if (!lista)
		return;
	
	while(lista->nodo_inicio){
		nodo_t *aux = lista->nodo_inicio->siguiente;
		free(lista->nodo_inicio);
		lista->nodo_inicio = aux;
	}

	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista)
		return;
	if (!funcion){
		lista_destruir(lista);
		return;
	}

	while(lista->nodo_inicio){
		nodo_t *aux = lista->nodo_inicio->siguiente;
		funcion(lista->nodo_inicio->elemento);
		free(lista->nodo_inicio);
		lista->nodo_inicio = aux;
	}

	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;

	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if (!iterador)
		return NULL;
	
	iterador->lista = lista;
	iterador->corriente = iterador->lista->nodo_inicio;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (!iterador)
		return false;
	if (!(iterador->corriente))
		return false;

	return true;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!iterador)
		return false;
	if (!(iterador->corriente))
		return false;

	iterador->corriente = iterador->corriente->siguiente;

	if (!(iterador->corriente))
		return false;
	
	return true;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (!iterador)
		return NULL;
	if (!(iterador->corriente))
		return NULL;

	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (!iterador)
		return;

	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!lista || !funcion || !contexto)
		return 0;

	nodo_t *nodo_iterador = lista->nodo_inicio;
	size_t leidos = 0;

	for(bool corte = true; corte && nodo_iterador; leidos++){
		corte = funcion(nodo_iterador->elemento, contexto);
		nodo_iterador = nodo_iterador->siguiente;
	}

	return leidos;
}