#include "cola.h"
#include "lista.h"

struct _cola_t {
	nodo_t *nodo_fin;
	nodo_t *nodo_inicio;
	size_t cantidad;
};

cola_t *cola_crear()
{
	return calloc(1, sizeof(cola_t));
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	if (!cola)
		return NULL;

	nodo_t *nodo_nuevo = calloc(1, sizeof(nodo_t));
	if(!nodo_nuevo)
		return NULL;

	nodo_nuevo->elemento = elemento;

	if (cola->cantidad == 0)
		cola->nodo_inicio = nodo_nuevo;
	else
		cola->nodo_fin->siguiente = nodo_nuevo;
	
	cola->nodo_fin = nodo_nuevo;
	cola->cantidad++;

	return cola;
}

void *cola_desencolar(cola_t *cola)
{
	if (!cola)
		return NULL;
	if (cola_vacia(cola))
		return NULL;
	
	nodo_t *nuevo_nodo_inicio = cola->nodo_inicio->siguiente;
	void *elemento_desencolado = cola->nodo_inicio->elemento;

	free(cola->nodo_inicio);

	cola->nodo_inicio = nuevo_nodo_inicio;
	cola->cantidad--;

	return elemento_desencolado;
}

void *cola_frente(cola_t *cola)
{
	if (!cola)
		return NULL;
	if (!(cola->nodo_inicio))
		return NULL;

	return cola->nodo_inicio->elemento;
}

size_t cola_tamanio(cola_t *cola)
{
	if (!cola)
		return 0;

	return cola->cantidad;	
}

bool cola_vacia(cola_t *cola)
{
	if (!cola)
		return true;

	return (cola->cantidad == 0);
}

void cola_destruir(cola_t *cola)
{
	if (!cola)
		return;
	
	while(cola->nodo_inicio){
		nodo_t *aux = cola->nodo_inicio->siguiente;
		free(cola->nodo_inicio);
		cola->nodo_inicio = aux;
	}

	free(cola);
}