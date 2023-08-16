#include "estructuras.h"
#include "interaccion.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DESCUBRIR 'd'
#define REEMPLAZAR 'r'
#define ELIMINAR 'e'
#define MOSTRAR 'm'

#define INICIALIZADO 0

struct interaccion *interaccion_crear_desde_string(const char *string)
{
	if(!string || strcmp(string, "") == 0)
		return NULL;
	
	struct interaccion *inter = calloc(1, sizeof(struct interaccion));
	if(!inter)
		return NULL;

	char tipo_accion = INICIALIZADO;

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
	if(tipo_accion == REEMPLAZAR)
		inter->accion.tipo = REEMPLAZAR_OBJETO;
	if(tipo_accion == ELIMINAR)
		inter->accion.tipo = ELIMINAR_OBJETO;
	if(tipo_accion == MOSTRAR)
		inter->accion.tipo = MOSTRAR_MENSAJE;

	return inter;
}