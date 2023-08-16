#include "objeto.h"
#include "estructuras.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ASIBLE 15

#define INICIALIZADO "inicializado"

struct objeto *objeto_crear_desde_string(const char *string)
{
	if(!string || strcmp(string, "") == 0)
		return NULL;

	struct objeto *objeto = calloc(1, sizeof(struct objeto));
	if(!objeto)
		return NULL;

	char es_asible[MAX_ASIBLE] = INICIALIZADO;

	int leidos = sscanf(string, "%[^;];%[^;];%[^\n]\n",
			objeto->nombre, objeto->descripcion, es_asible);

	if(!strcmp(es_asible, "false") == 0 && !strcmp(es_asible, "true") == 0){
		free(objeto);
		return NULL;
	}

	if(leidos != 3){
		free(objeto);
		return NULL;
	}

	if(strcmp(es_asible, "true") == 0)
		objeto->es_asible = true;
	if(strcmp(es_asible, "false") == 0)
		objeto->es_asible = false;

	return objeto;
}