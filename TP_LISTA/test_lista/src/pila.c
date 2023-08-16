#include "pila.h"
#include "lista.h"

struct _pila_t {
        nodo_t *nodo_fin;
        size_t cantidad;
};

pila_t *pila_crear()
{
	return calloc(1, sizeof(pila_t));
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	if (!pila)
		return NULL;

	nodo_t *nodo_nuevo = malloc(sizeof(nodo_t));
	if (!nodo_nuevo)
		return NULL;

	nodo_nuevo->elemento = elemento;
	nodo_nuevo->siguiente = pila->nodo_fin;
	pila->nodo_fin = nodo_nuevo;
	pila->cantidad++;

	return pila;
}

void *pila_desapilar(pila_t *pila)
{
	if (!pila)
		return NULL;

	if (pila_vacia(pila))
		return NULL;

	nodo_t *nuevo_nodo_fin = pila->nodo_fin->siguiente;
	void *elemento_desapilado = pila->nodo_fin->elemento;

	free(pila->nodo_fin);

	pila->nodo_fin = nuevo_nodo_fin;
	pila->cantidad--;
	
	return elemento_desapilado;
}

void *pila_tope(pila_t *pila)
{
	if (!pila)
		return NULL;
	if (!(pila->nodo_fin))
		return NULL;
	
	return pila->nodo_fin->elemento;
}

size_t pila_tamanio(pila_t *pila)
{
	if (!pila)
		return 0;

	return pila->cantidad;
}

bool pila_vacia(pila_t *pila)
{
	if (!pila)
		return true;
	
	return (pila->cantidad == 0);
}

void pila_destruir(pila_t *pila)
{
	if (!pila)
		return;
	
	while(pila->nodo_fin){
		nodo_t *aux = pila->nodo_fin->siguiente;
		free(pila->nodo_fin);
		pila->nodo_fin = aux;
	}

	free(pila);
}