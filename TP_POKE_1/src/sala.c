#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define READ "r"
#define MAX_LINEA 1024
#define MAX_OBJETO 10
#define ERROR -1

/*
//	Procedimiento que agranda el vector de objetos para 1 mas.
//
//	Devuelve 0 en caso de exito y -1 en caso de error.
*/ 
int agregar_objeto(struct sala *sala, int *cantidad, char linea[MAX_LINEA])
{
	struct objeto *objeto_a_agregar = objeto_crear_desde_string(linea);
	if (!objeto_a_agregar)
		return ERROR;

	struct objeto **bloque = realloc(sala->objetos, (unsigned)((*cantidad)+1) * sizeof(struct objeto));
	if(!bloque)
		return ERROR;

	bloque[*cantidad] = objeto_a_agregar;
	sala->objetos = bloque;
	(*cantidad)++;

	return 0;
}
/*
//	Procedimiento que agranda el vector de interacciones para 1 mas.
//
//	Devuelve 0 en caso de exito y -1 en caso de error.
*/ 
int agregar_interaccion(struct sala *sala, int *cantidad, char linea[MAX_LINEA])
{
	struct interaccion *interaccion_a_agregar = interaccion_crear_desde_string(linea);
	if (!interaccion_a_agregar)
		return ERROR;

	struct interaccion **bloque = realloc(sala->interacciones, (unsigned)((*cantidad)+1) * sizeof(struct interaccion));
	if(!bloque)
		return ERROR;

	bloque[*cantidad] = interaccion_a_agregar;
	sala->interacciones = bloque;
	(*cantidad)++;

	return 0;
}
/*
//	Procedimiento que carga el archivo de objetos en memoria.
//
//	Devuelve 0 en caso de exito y -1 en caso de error.
*/
int objetos_arch(FILE *archivo, struct sala *sala)
{
	char linea[MAX_LINEA];
	int leido = fscanf(archivo, "%[^\n]\n", linea);

	while(leido == 1){
		if(agregar_objeto(sala, &(sala->cantidad_objetos), linea) == ERROR){
			sala_destruir(sala);
			return ERROR;
		}
	
		leido = fscanf(archivo, "%[^\n]\n", linea);
	}

	return 0;
}
/*
//	Procedimiento que carga el archivo de interacciones en memoria.
//
//	Devuelve 0 en caso de exito y -1 en caso de error.
*/
int interacciones_arch(FILE *archivo, sala_t *sala)
{
	char linea[MAX_LINEA];
	int leido = fscanf(archivo, "%[^\n]\n", linea);

	while(leido == 1){
		if(agregar_interaccion(sala, &(sala->cantidad_interacciones), linea) == ERROR){
			sala_destruir(sala);
			return ERROR;
		}
	
		leido = fscanf(archivo, "%[^\n]\n", linea);
	}

	return 0;
}
/*
//	Procedimiento que maneja los archivos de objetos e interacciones.
//
//	Devuelve 0 en caso de exito y -1 en caso de error.
*/
int archivos(struct sala *sala, const char *objetos, const char *interacciones)
{
	FILE *arch_obj = fopen(objetos, READ);
	if(!arch_obj){
		perror("ERROR: Archivo de Objetos");
		return ERROR;
	}

	FILE *arch_int = fopen(interacciones, READ);
	if(!arch_int){
		perror("ERROR: Archivo de Interacciones");
		fclose(arch_obj);
		return ERROR;
	}

	if((objetos_arch(arch_obj, sala) == ERROR) || (interacciones_arch(arch_int, sala) == ERROR))
		return ERROR;

	fclose(arch_obj);
	fclose(arch_int);

	return 0;
}

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	if(!objetos || !interacciones)
		return NULL;

	struct sala *sala = calloc(1, sizeof(struct sala));
	if(!sala)
		return NULL;

	if(archivos(sala, objetos, interacciones) == ERROR){
		sala_destruir(sala);
		return NULL;
	}

	if(sala->cantidad_objetos == 0 || sala->cantidad_interacciones == 0){
		sala_destruir(sala);
		return NULL;
	}

	return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if(!sala && *cantidad >= 0){
		*cantidad = -1;
		return NULL;
	}

	char **objetos_nombres = malloc(sizeof(char *) * (unsigned)(sala->cantidad_objetos));
	if(!objetos_nombres){
		*cantidad = -1;
		return NULL;
	}

	for(int i = 0; i < sala->cantidad_objetos; i++){
		objetos_nombres[i] = sala->objetos[i]->nombre;
	}
	
	if(!cantidad)
		return objetos_nombres;

	(*cantidad) = sala->cantidad_objetos;

	return objetos_nombres;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	if(!sala || !verbo || !objeto1 || !objeto2)
		return false;

	bool interaccion_encontrada = false;

	for(int i = 0; i < sala->cantidad_interacciones && !interaccion_encontrada; i++){
		if(strcmp(verbo, sala->interacciones[i]->verbo) == 0
		&& strcmp(objeto1, sala->interacciones[i]->objeto) == 0
		&& strcmp(objeto2, sala->interacciones[i]->objeto_parametro) == 0){
			interaccion_encontrada = true;
		}
	}

	return interaccion_encontrada;
}
/*
//	Procedimiento que libera la memoria usada por los objetos.
*/
void objetos_destruir(struct objeto **objetos, int cantidad)
{
	for(int i = 0; i < cantidad; i++){
		free(objetos[i]);
	}

	free(objetos);
}
/*
//	Procedimiento que libera la memoria usada por las interacciones.
*/
void interacciones_destruir(struct interaccion **interacciones, int cantidad)
{
	for(int i = 0; i < cantidad; i++){
		free(interacciones[i]);
	}

	free(interacciones);
}

void sala_destruir(sala_t *sala)
{
	if(!sala)
		return;

	objetos_destruir(sala->objetos, sala->cantidad_objetos);
	interacciones_destruir(sala->interacciones, sala->cantidad_interacciones);
	free(sala);
}
