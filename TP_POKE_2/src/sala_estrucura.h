#ifndef __SALA_ESTRUCURA_H__
#define __SALA_ESTRUCURA_H__

// typedef struct nodo_obj {
// 	struct objeto *objeto;
// 	bool conocido;
// 	bool poseido;
// } nodo_obj_t;

struct sala {
	hash_t *objetos;
	lista_t *interacciones;

	abb_t *conocidos;
	abb_t *poseidos;

	bool escapo;
};

#endif // __SALA_ESTRUCURA_H__