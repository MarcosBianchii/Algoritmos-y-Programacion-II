#include "estructuras.h"
#include "interaccion.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DESCUBRIR 'd'
#define REEMPLAZAR 'r'
#define ELIMINAR 'e'
#define MOSTRAR 'm'
#define ESCAPE 'g'

struct interaccion *interaccion_crear_desde_string(const char *string)
{
	if(!string || strcmp(string, "") == 0) return NULL;

	struct interaccion *inter = malloc(sizeof(struct interaccion));
	if(!inter) return NULL;

	char tipo_accion = '0';
	int leidos = sscanf(string, "%[^;];%[^;];%[^;];%c:%[^:]:%[^\n]\n",
		     inter->objeto, inter->verbo, inter->objeto_parametro,
		     &tipo_accion, inter->accion.objeto, inter->accion.mensaje);

	if(leidos != 6){
		free(inter);
		return NULL;
	}

	if(strcmp(inter->objeto_parametro, "_") == 0)
		strcpy(inter->objeto_parametro, "");
	if(strcmp(inter->accion.objeto, "_") == 0)
		strcpy(inter->accion.objeto, "");
	
	if(tipo_accion == DESCUBRIR)
		inter->accion.tipo = DESCUBRIR_OBJETO;
	else if(tipo_accion == REEMPLAZAR)
		inter->accion.tipo = REEMPLAZAR_OBJETO;
	else if(tipo_accion == ELIMINAR)
		inter->accion.tipo = ELIMINAR_OBJETO;
	else if(tipo_accion == MOSTRAR)
		inter->accion.tipo = MOSTRAR_MENSAJE;
	else if(tipo_accion == ESCAPE)
		inter->accion.tipo = ESCAPAR;

	return inter;
}