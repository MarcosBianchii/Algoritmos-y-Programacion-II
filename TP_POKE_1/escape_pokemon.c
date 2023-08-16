#include "src/sala.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALIDO "Válido"
#define INVALIDO "Inválido"
#define MAX_VALIDEZ 10
#define ERROR -1

int main(int argc, char *argv[])
{
	if(argc != 3){

		printf("(0)./escape_pokemon (1)objetos.txt (2)interacciones.txt\n");
		return ERROR;
	}

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
	if(!sala){

		printf("Error al crear la sala de escape\n");
		return ERROR;
	}

// OBJETOS

	int cantidad_objetos = 0;

	char **objetos_nombres = sala_obtener_nombre_objetos(sala, &cantidad_objetos);

// INTERACCIONES

	char examinar_habitacion[MAX_VALIDEZ] = INVALIDO;
	char abrir_pokebola[MAX_VALIDEZ] = INVALIDO;
	char usar_llave_cajon[MAX_VALIDEZ] = INVALIDO;
	char quemar_mesa[MAX_VALIDEZ] = INVALIDO;

	if(sala_es_interaccion_valida(sala, "examinar", "habitacion", ""))
		strcpy(examinar_habitacion, VALIDO);

	if(sala_es_interaccion_valida(sala, "abrir", "pokebola", ""))
		strcpy(abrir_pokebola, VALIDO);

	if(sala_es_interaccion_valida(sala, "usar", "llave", "cajon"))
		strcpy(usar_llave_cajon, VALIDO);

	if(sala_es_interaccion_valida(sala, "quemar", "mesa", ""))
		strcpy(quemar_mesa, VALIDO);

// IMPRIMIR POR PANTALLA

	printf("Objetos...\n");

	for(int i = 0; i < cantidad_objetos; i++){

		printf("%i: %s\n", i, objetos_nombres[i]);
	}

	printf("\nInteracciones...\n");

	printf("\
1. Examinar habitacion: %s\n\
2. Abrir pokebola: %s\n\
3. Usar llave cajon: %s\n\
4. Quemar mesa: %s\n",
examinar_habitacion, abrir_pokebola,
usar_llave_cajon, quemar_mesa);

// FREE

	free(objetos_nombres);
	sala_destruir(sala);

	return 0;
}
