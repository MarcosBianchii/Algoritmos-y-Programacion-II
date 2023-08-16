#include "estructuras.h"
#include "objeto.h"
#include "interaccion.h"
#include "sala.h"

#include "lista.h"
#include "hash.h"
#include "abb.h"
#include "sala_estrucura.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define READ "r"
#define MAX_LINEA 1024
#define ERROR -1
#define EXITO 0

static int agregar_objeto(sala_t *sala, char *linea)
/*
//	Procedimiento que carga un
//	nuevo objeto en el hash.
//
//	Devuelve 0 en caso de exito y -1 en caso de error.
*/ 
{
	struct objeto *objeto = objeto_crear_desde_string(linea);
	if (!objeto) return ERROR;

	if (hash_cantidad(sala->objetos) == 0){
		sala->primer_objeto = objeto;
		abb_insertar(sala->conocidos, objeto);
	}

	hash_insertar(sala->objetos, objeto->nombre, objeto, NULL);
	return EXITO;
}

static int agregar_interaccion(sala_t *sala, char *linea)
/*
//	Procedimiento que carga una
//	nueva interaccion en la lista.
//
//	Devuelve 0 en caso de exito y -1 en caso de error.
*/ 
{
	struct interaccion *nueva_inter = interaccion_crear_desde_string(linea);
	if (!nueva_inter) return ERROR;

	lista_insertar(sala->interacciones, nueva_inter);
	return EXITO;
}

static int agregar_estrucura(FILE *archivo, sala_t *sala,
			     int (*agregador)(sala_t *, char *))
/*
//	Procedimiento que crea las estructuras
//	de objetos/interacciones.
//
//	Devuelve 0 en caso de exito y -1 en
//	caso de error.
*/
{
	char linea[MAX_LINEA];
	int leido = fscanf(archivo, "%[^\n]\n", linea);

	while (leido == 1){
		if (agregador(sala, linea) == ERROR){
			sala_destruir(sala);
			return ERROR;
		}
	
		leido = fscanf(archivo, "%[^\n]\n", linea);
	}

	return EXITO;
}

static int archivos(sala_t *sala, const char *objetos,
				  const char *interacciones)
/*
//	Procedimiento que maneja los archivos
//	de objetos e interacciones.
//
//	Devuelve 0 en caso de exito
//	y -1 en caso de error.
*/
{
	FILE *arch_obj = fopen(objetos, READ);
	if (!arch_obj) return ERROR;

	FILE *arch_int = fopen(interacciones, READ);
	if (!arch_int){
		fclose(arch_obj);
		return ERROR;
	}

	if ((agregar_estrucura(arch_obj, sala, agregar_objeto) == ERROR)
	|| (agregar_estrucura(arch_int, sala, agregar_interaccion) == ERROR))
		return ERROR;

	fclose(arch_obj);
	fclose(arch_int);

	return EXITO;
}

static int comparador_abb(void *a_, void *b_)
/*
//	El comparador que uso para los abbs.
*/
{
	struct objeto *a = a_;
	struct objeto *b = b_;

	return strcmp(a->nombre, b->nombre);
}

sala_t *sala_crear_desde_archivos(const char *objetos,
				  const char *interacciones)
{
	if (!objetos || !interacciones) return NULL;

	sala_t *sala = calloc(1, sizeof(sala_t));
	if (!sala) return NULL;

	sala->objetos = hash_crear(15);
	sala->interacciones = lista_crear();
	sala->conocidos = abb_crear(comparador_abb);
	sala->poseidos = abb_crear(comparador_abb);

	if (!sala->objetos || !sala->interacciones
	||  !sala->conocidos || !sala->poseidos){
		sala_destruir(sala);
		return NULL;
	}

	if (archivos(sala, objetos, interacciones) == ERROR){
		sala_destruir(sala);
		return NULL;
	}

	if (hash_cantidad(sala->objetos) == 0
	||  lista_vacia(sala->interacciones)){
		sala_destruir(sala);
		return NULL;
	}

	return sala;
}

/*
//	Este struct lo necesito porque la funcion
//	que recibe hash_con_cada_clave() recibe
//	solo un puntero auxiliar. El problema es
//	que no se pasarle el vector y su largo de
//	otra manera que no sea esta o usando una
//	variable global.
*/
typedef struct vector_indice {
	char **nombres;
	int len;
} array_t;

static bool crear_vector_nombres(const char *clave, void *valor, void *aux)
/*
//	Procedimiento que carga un vector de nombres con el
//	nombre pasado por parametro, es la funcion que recibe
//	el iterador del hash.
*/
{
	struct objeto *objeto = valor;
	array_t *array = aux;

	array->nombres[array->len++] = objeto->nombre;

	return true;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if (cantidad) *cantidad = -1;
	if (!sala) return NULL;

	array_t *array = malloc(sizeof(array_t));
	if (!array) return NULL;

	array->len = 0;
	array->nombres = malloc(sizeof(char *) * hash_cantidad(sala->objetos));
	if (!array->nombres) return NULL;

	hash_con_cada_clave(sala->objetos, crear_vector_nombres, array);

	char **nombres = array->nombres;
	if (cantidad) *cantidad = array->len;
	free(array);

	return nombres;
}

static char **obtener_vector_nombres(abb_t *arbol, int *cantidad)
/*
//	Procedimiento que crea y carga un vector con los
//	nombres de los objetos.
//
//	Solo sirve para los abbs.
*/
{
	size_t tamanio = abb_tamanio(arbol);
	char **nombres = malloc(sizeof(char *) * tamanio);
	abb_recorrer(arbol, PREORDEN, (void *)nombres, tamanio);
	if (cantidad) *cantidad = (int)tamanio;

	return nombres;
}

char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
	if (!sala) return NULL;
	if (cantidad) *cantidad = -1;

	return obtener_vector_nombres(sala->conocidos, cantidad);
}

char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
	if (!sala) return NULL;
	if (cantidad) *cantidad = -1;

	return obtener_vector_nombres(sala->poseidos, cantidad);
}


bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if (!sala || strcmp(nombre_objeto, "") == 0)
		return false;

	struct objeto *objeto = hash_obtener(sala->objetos, nombre_objeto);
	if (!objeto) return false;

	if (abb_buscar(sala->conocidos, objeto->nombre) && objeto->es_asible
	&& !abb_buscar(sala->poseidos, objeto->nombre)){
		abb_quitar(sala->conocidos, objeto);
		abb_insertar(sala->poseidos, objeto);
		return true;
	}

	return false;
}

char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto)
{
	if (!sala || strcmp(nombre_objeto, "") == 0)
		return NULL;

	struct objeto *objeto = hash_obtener(sala->objetos, nombre_objeto);
	if (!objeto) return NULL;

	if (abb_buscar(sala->conocidos, objeto)
	||  abb_buscar(sala->poseidos, objeto))
		return objeto->descripcion;

	return NULL;
}

static bool conocer_objeto(sala_t *sala, char *nombre_objeto)
/*
//	Procedimiento que hace conocido el objeto
//	con el nombre pasado por parametro.
*/
{
	struct objeto *objeto = hash_obtener(sala->objetos, nombre_objeto);
	if (!objeto) return false;

	if (!abb_buscar(sala->poseidos, objeto)
	&&  !abb_buscar(sala->conocidos, objeto)){
		abb_insertar(sala->conocidos, objeto);
		return true;
	}

	return false;
}

static bool es_esta_interaccion(const char *verbo, const char *objeto1,
				const char *objeto2, struct interaccion *inter)
/*
//	Funcion que verifica que la interaccion pasada por parametro
//	tenga este verbo, objeto y objeto_parametro.
*/
{
	if (strcmp(verbo, inter->verbo) == 0
	&& strcmp(objeto1, inter->objeto) == 0
	&& strcmp(objeto2, inter->objeto_parametro) == 0)
		return true;
	
	return false;
}

static int descubir_objeto(sala_t *sala, struct interaccion *inter,
			   void (*mostrar_mensaje)(const char *mensaje,
						   enum tipo_accion,
						   void *aux),
			   void *aux)
/*
//	Procedimiento que hace conocido un objeto
//	e imprime su mensaje.
*/
{

	if ((abb_buscar(sala->poseidos, inter->objeto)
	||  strcmp(sala->primer_objeto->nombre, inter->objeto) == 0)
	&& !abb_buscar(sala->conocidos, inter->accion.objeto)
	&& !abb_buscar(sala->poseidos, inter->accion.objeto)
	&&  hash_obtener(sala->objetos, inter->accion.objeto)){

		conocer_objeto(sala, inter->accion.objeto);
		mostrar_mensaje(inter->accion.mensaje, DESCUBRIR_OBJETO, aux);
		return 1;
	}

	return 0;
}

static int eliminar_objeto(sala_t *sala, struct interaccion *inter,
			   void (*mostrar_mensaje)(const char *mensaje,
						   enum tipo_accion,
						   void *aux),
			   void *aux)
/*
//	Procedimiento que elimina un objeto de
//	todas las estructuras.
*/
{
	if (abb_buscar(sala->poseidos, inter->objeto)){
		abb_quitar(sala->poseidos, inter->objeto);
		free(hash_quitar(sala->objetos, inter->objeto));
		mostrar_mensaje(inter->accion.mensaje, ELIMINAR_OBJETO, aux);
		return 1;
	}

	return 0;
}

static int reemplazar_objeto(sala_t *sala, struct interaccion *inter,
			     void (*mostrar_mensaje)(const char *mensaje,
						     enum tipo_accion,
						     void *aux),
			     void *aux)
/*
//	Procedimiento que reemplaza un
//	objeto_parametro por accion.objeto.
*/
{
	if (abb_buscar(sala->poseidos, inter->objeto)){
		abb_quitar(sala->conocidos, inter->objeto_parametro);
		free(hash_quitar(sala->objetos, inter->objeto_parametro));
		abb_insertar(sala->conocidos, inter->accion.objeto);
		mostrar_mensaje(inter->accion.mensaje, REEMPLAZAR_OBJETO, aux);
		return 1;
	}

	return 0;
}

static int escapar(sala_t *sala, struct interaccion *inter,
		   void (*mostrar_mensaje)(const char *mensaje,
					   enum tipo_accion,
					   void *aux),
		   void *aux)
/*
//	Procedimiento que cambia el estado
//	del juego a ganaddo.
*/
{
	if (abb_buscar(sala->conocidos, inter->objeto)
	||  abb_buscar(sala->poseidos, inter->objeto)){
		sala->escapo = true;
		mostrar_mensaje(inter->accion.mensaje, ESCAPAR, aux);
		return 1;
	}

	return 0;
}

static int mostrar_por_pantalla(sala_t *sala, struct interaccion *inter,
				void (*mostrar_mensaje)(const char *mensaje,
							enum tipo_accion,
							void *aux),
				void *aux)
/*
//	Procedimiento que muestra el mensaje
//	de una interaccion por pantalla.
*/
{
	if (abb_buscar(sala->conocidos, inter->objeto)){
		mostrar_mensaje(inter->accion.mensaje, MOSTRAR_MENSAJE, aux);
		return 1;
	}

	return 0;
}

static int ejecutar_interaccion(sala_t *sala, struct interaccion *inter,
				void (*mostrar_mensaje)(const char *mensaje,
			 				enum tipo_accion accion,
			 				void *aux),
				void *aux)
/*
//	Procedimiento que ejecuta una interaccion valida.
*/
{
	enum tipo_accion tipo = inter->accion.tipo;
	if (tipo == DESCUBRIR_OBJETO)
		return descubir_objeto(sala, inter, mostrar_mensaje, aux);

	else if (tipo == ELIMINAR_OBJETO)
		return eliminar_objeto(sala, inter, mostrar_mensaje, aux);

	else if (tipo == REEMPLAZAR_OBJETO)
		return reemplazar_objeto(sala, inter, mostrar_mensaje, aux);

	else if (tipo == ESCAPAR)
		return escapar(sala, inter, mostrar_mensaje, aux);

	else if (tipo == MOSTRAR_MENSAJE)
		return mostrar_por_pantalla(sala, inter, mostrar_mensaje, aux);

	return 0;
}

static int ejecutar_mis_comandos(sala_t *sala, const char *verbo, const char *objeto1,
				 void (*mostrar_mensaje)(const char *mensaje,
			   				 enum tipo_accion accion,
							 void *aux),
				 void *aux)
/*
//	Procedimiento que ejecuta los comandos que no tengan
//	que ver con las interacciones entre objetos.
*/
{
	if (strcmp(verbo, "agarrar") == 0){
		if(sala_agarrar_objeto(sala, (char *)objeto1)){
			mostrar_mensaje("Nuevo Objeto:", DESCUBRIR_OBJETO, (char *)objeto1);
			return 1;
		}
	}

	else if (strcmp(verbo, "describir") == 0){
		struct objeto *objeto = hash_obtener(sala->objetos, (char *)objeto1);
		if (!objeto) return 0;
		
		if (abb_buscar(sala->conocidos, objeto)
		||  abb_buscar(sala->poseidos, objeto)){
			mostrar_mensaje(sala_describir_objeto(sala, objeto->nombre), MOSTRAR_MENSAJE, aux);
			return 1;
		}
	}

	return 0;
}

int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,
			      const char *objeto1, const char *objeto2,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux)
{
	if (!sala || !verbo || !objeto1 || !objeto2)
		return 0;

	if (strcmp(verbo, "ayuda") == 0)
		return 1;

	if (ejecutar_mis_comandos(sala, verbo, objeto1, mostrar_mensaje, aux) == 1)
		return 1;

	int contador = 0;
	lista_iterador_t *it = lista_iterador_crear(sala->interacciones);
	for (;lista_iterador_tiene_siguiente(it);
	      lista_iterador_avanzar(it)){

		struct interaccion *inter = lista_iterador_elemento_actual(it);
		if (es_esta_interaccion(verbo, objeto1, objeto2, inter)){
			contador += ejecutar_interaccion(sala, inter, mostrar_mensaje, aux);
			if (contador == 0){
				lista_iterador_destruir(it);
				return 0;
			}
		}
	}

	lista_iterador_destruir(it);
	return contador;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo,
				const char *objeto1, const char *objeto2)
{
	if (!sala || !verbo || !objeto1 || !objeto2) return false;

	lista_iterador_t *it = lista_iterador_crear(sala->interacciones);
	for (;lista_iterador_tiene_siguiente(it);
	      lista_iterador_avanzar(it)){
		
		struct interaccion *inter = lista_iterador_elemento_actual(it);
		if (es_esta_interaccion(verbo, objeto1, objeto2, inter)){
			free(it);
			return true;
		}
	}

	free(it);
	return false;
}

bool sala_escape_exitoso(sala_t *sala)
{
	return sala->escapo;
}

void sala_destruir(sala_t *sala)
{
	if (!sala) return;

	hash_destruir_todo(sala->objetos, free);
	lista_destruir_todo(sala->interacciones, free);
	abb_destruir(sala->conocidos);
	abb_destruir(sala->poseidos);
	free(sala);
}