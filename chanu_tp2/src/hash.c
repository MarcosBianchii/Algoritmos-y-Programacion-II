#include "hash.h"
#include "hash_estructura.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static size_t hashify(const char *clave)
/*
//	Funcion de hash que recibe una
//	clave y devuelve un entero que
//	representa un indice en la tabla.
*/
{
	int hash = 5381;

	while (*clave){
		int c = *clave++;
		hash = ((hash << 5) + hash) + c;
	}
	
	return (size_t)hash;
}

hash_t *hash_crear(size_t capacidad)
{
	if (capacidad < 3) capacidad = 3;

	hash_t *hash = calloc(1, sizeof(hash_t));
	if (!hash) return NULL;
	hash->capacidad = capacidad;
	
	hash->tabla = calloc(capacidad, sizeof(nodo_t *));
	if (!hash->tabla){
		free(hash);
		return NULL;
	}

	return hash;
}

static nodo_t *traspasar_nodo(nodo_t **tabla, nodo_t *it, size_t pos)
/*
//	Procedimiento que traspasa un nodo de una tabla a la otra.
//
//	No puede recibir punteros NULL.
*/
{
	nodo_t *sig = it->siguiente;

	it->siguiente = tabla[pos];
	tabla[pos] = it;

	return sig;
}

static void rehash(hash_t *hash)
/*
//	Procedimiento que
//	rehashea la tabla.
//
//	El puntero no
//	puede ser NULL.
*/
{
	nodo_t **tabla_aux = hash->tabla;
	hash->capacidad *= 2;
	hash->tabla = calloc(hash->capacidad, sizeof(nodo_t *));

	for (int i = 0; i < hash->capacidad/2; i++){
		nodo_t *it = tabla_aux[i]; 
		while (it){
			size_t pos = hashify(it->clave) % hash->capacidad;
			it = traspasar_nodo(hash->tabla, it, pos);
		}
	}

	free(tabla_aux);
}

static nodo_t *nodo_crear(hash_t *hash, const char *clave, void *elemento)
/*
//	Procedimiento que crea un nodo y le asigna un elemento y copia
//	de su clave, si no se pudo crear el nodo, devuelve NULL.
//
//	No puede recibir punteros NULL.
*/
{
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (!nodo) return NULL;

	nodo->clave = malloc(strlen(clave)+1);
	if (!nodo->clave) return NULL;
	strcpy(nodo->clave, clave);

	nodo->valor = elemento;
	nodo->siguiente = NULL;

	hash->ocupados++;

	return nodo;
}

static void nodo_a_lista(hash_t *hash, nodo_t *it, const char *clave,
			    void *elemento, void **anterior)
/*
//	Procedimiento que agrega un nodo a una lista de nodos,
//	si encuentra una clave identica la reemplaza y guarda
//	su valor en *anterior.
//
//	No puede recibir punteros NULL exceptuando elemento.
*/
{
	while (it){
		if (strcmp(it->clave, clave) == 0){
			if (anterior) *anterior = it->valor;
			it->valor = elemento;
			return;
		}
		if (!it->siguiente){
			nodo_t *nodo = nodo_crear(hash, clave, elemento);
			if (nodo) it->siguiente = nodo;
			return;
		}

		it = it->siguiente;
	}
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash) return NULL;
	if (anterior) *anterior = NULL;
	if (!clave) return NULL;

	float carga = (float)hash->ocupados / (float)hash->capacidad;
	if (carga >= COTA_MIN) rehash(hash);

	size_t pos = hashify(clave) % hash->capacidad;

	if (!hash->tabla[pos]){
		nodo_t *nodo = nodo_crear(hash, clave, elemento);
		if (!nodo) return NULL;
		hash->tabla[pos] = nodo;
	}
	else nodo_a_lista(hash, hash->tabla[pos], clave, elemento, anterior);

	return hash;
}

static void *nodo_quitar(hash_t *hash, nodo_t *it, nodo_t *anterior, size_t pos)
/*
//	Procedimiento que quita un nodo	de una lista de nodos.
//
//	No puede recibir punteros NULL.
*/
{
	void *elemento = it->valor;
	if (!anterior)
		hash->tabla[pos] = it->siguiente;
	else anterior->siguiente = it->siguiente;

	free(it->clave);
	free(it);

	hash->ocupados--;

	return elemento;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash || !clave) return NULL;

	size_t pos = hashify(clave) % hash->capacidad;

	nodo_t *it = hash->tabla[pos];
	nodo_t *aux = NULL;
	while (it){
		if (strcmp(it->clave, clave) == 0)
			return nodo_quitar(hash, it, aux, pos);

		aux = it;
		it = it->siguiente;
	}

	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash || !clave) return NULL;

	size_t pos = hashify(clave) % hash->capacidad;

	nodo_t *it = hash->tabla[pos];
	while (it){
		if (strcmp(it->clave, clave) == 0)
			return it->valor;
		it = it->siguiente;
	}

	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash || !clave) return false;

	return hash_obtener(hash, clave);
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash) return 0;

	return hash->ocupados;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

static nodo_t *nodo_destruir(nodo_t *nodo, void (*destructor)(void *))
/*
//	Procedimiento que libera la memoria reservada
//	por un nodo y su clave.
//
//	El puntero a nodo no puede ser NULL.
*/
{
	nodo_t *siguiente = nodo->siguiente;
	if (destructor)
		destructor(nodo->valor);
	free(nodo->clave);
	free(nodo);
	
	return siguiente;
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash) return;

	for (int i = 0; i < hash->capacidad; i++){
		nodo_t *it = hash->tabla[i];
		while (it)
			it = nodo_destruir(it, destructor);
	}

	free(hash->tabla);
	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	if (!hash || !f) return 0;

	size_t iteradas = 0;
	for (int i = 0; i < hash->capacidad; i++){
		nodo_t *it = hash->tabla[i];
		while (it){
			iteradas++;
			if (!f(it->clave, it->valor, aux))
				return iteradas;
			it = it->siguiente;
		}
	}

	return iteradas;
}