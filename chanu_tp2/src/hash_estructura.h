#ifndef __ESTRUCTURAS_H__
#define __ESTRUCTURAS_H__

typedef struct nodo {
	char *clave;
	void *valor;
	struct nodo *siguiente;
} nodo_t;

struct hash {
	nodo_t **tabla;
	size_t ocupados;
	size_t capacidad;
};

#define COTA_MIN 0.75 // Cota minima para rehashear

#endif // __ESTRUCTURAS_H__