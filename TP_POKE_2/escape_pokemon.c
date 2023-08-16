#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define NEGRO "\033[0;30m"
#define ROJO "\033[0;31m"
#define VERDE "\033[0;32m"
#define AMARILLO "\033[0;33m"
#define VIOLETA "\033[0;35m"
#define BLANCO "\033[0;37m"

#define INPUT 128 // El tamanio del vector de input.

void mostrar_texto(const char *mensaje, enum tipo_accion accion, void *aux)
/*
//	Esta funcion es la que le mando a
//	sala_ejectuar_interaccion().
*/
{
	if (accion == DESCUBRIR_OBJETO
	||  accion == REEMPLAZAR_OBJETO
	||  accion == ESCAPAR)
		printf(VERDE);

	else if (accion == ELIMINAR_OBJETO
	     ||  accion == ACCION_INVALIDA)
		printf(ROJO);

	else
		printf(NEGRO);

	printf("%s ", mensaje);
	if (aux)printf(BLANCO"%s", (char *)aux);

	printf("\n");
}

void imprimir_ayuda()
/*
//	Proceso que imprime
//	los comandos.
*/
{
	printf(VIOLETA"Comandos:\n"BLANCO
"Agarrar    "VERDE"[Objeto]\t   "   NEGRO" -> "BLANCO"Agrega el objeto al inventario\n"
"Describir  "VERDE"[Objeto]\t   "   NEGRO" -> "BLANCO"Imprime una descripcion del objeto\n"
"Examinar   "VERDE"[Objeto]\t   "   NEGRO" -> "BLANCO"Imprime informacion relacionada al objeto\n"
"Abrir      "VERDE"[Objeto][Objeto]"NEGRO" -> "BLANCO"Abre el ultimo objeto, en caso de haber mas de uno utiliza el primero\n"
"Conectar   "VERDE"[Objeto][Objeto]"NEGRO" -> "BLANCO"Conecta el primer objeto al segundo\n"
"Escapar    "VERDE"[Objeto]\t   "   NEGRO" -> "BLANCO"Utiliza el objeto para escapar del cuarto\n"
"Salir      "ROJO "[Objeto]\t   "   NEGRO" -> "BLANCO"Cierra el juego liberando la memoria\n\n");
}

void imprimir_menu(char **nombres, int n, char *categoria)
/*
//	Procedimiento que imprime por pantalla
//	un menu de nombres de objetos.
*/
{
	int max_len = 0;
	for (int i = 0; i < n; i++){
		int len = strlen(nombres[i]);
		if (len > max_len)
			max_len = len;
	}

	printf(AMARILLO"\n%s:\n+", categoria);
	for (int i = 0; i < max_len; i++)
		printf("-");
	printf("+\n");

	for (int i = 0; i < n; i++){
		printf(AMARILLO"|"BLANCO"%s", nombres[i]);
		int len = strlen(nombres[i]);
		for (int j = len; j < max_len; j++)
			printf(" ");
		printf(AMARILLO"|\n");
	}

	printf(AMARILLO"+");
	for (int i = 0; i < max_len; i++)
		printf("-");
	printf("+\n"BLANCO);
}

void imprimir_pantalla(sala_t *sala)
/*
//	Procedimiento que obtiene
//	los vectores con los nombres
//	para imprimirlos por pantalla.
*/
{
	int cant_conocidos = 0;
	char **conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cant_conocidos);
	imprimir_menu(conocidos, cant_conocidos, "Objetos Conocidos");
	free(conocidos);

	int cant_poseidos = 0;
	char **poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cant_poseidos);
	if (cant_poseidos > 0) imprimir_menu(poseidos, cant_poseidos, "Inventario");
	free(poseidos);

	printf("\n");
}

void pedir_input(char input[], char *argv[], char *vacio, bool jugada_valida)
/*
//	Procedimiento que pide input al
//	usuario y lo divide en palabras.
*/
{
	jugada_valida ? printf(VERDE) : printf(ROJO);
	printf("> "BLANCO);
	fgets(input, INPUT, stdin);

	int len = strlen(input);
	for (int i = 0; i < len-1; i++)
		input[i] = tolower(input[i]);
	input[len-1] = '\0';

	argv[0] = strtok(input, " ");
	argv[1] = strtok(NULL, " ");
	argv[2] = strtok(NULL, " ");

	for (int i = 0; i < 3; i++)
		if (!argv[i])
			argv[i] = vacio;
}

bool game_loop(sala_t *sala)
/*
//	El loop que itera hasta que se gane o
//	el jugador elija salir del juego.
*/
{
	bool jugada_valida = true;
	system("clear");
	printf(VERDE"'ayuda' para ver la lista de comandos\n"BLANCO);
	imprimir_pantalla(sala);
	while (!sala_escape_exitoso(sala)){
		char input[INPUT] = "";
		char *vacio = "";
		char **argv = malloc(sizeof(char *));
		if (!argv) return false;

		pedir_input(input, argv, vacio, jugada_valida);
		if (strcmp(argv[0], "salir") == 0
		&&  strcmp(argv[1], "") == 0){
			free(argv);
			return false;
		}

		jugada_valida = true;

		system("clear");
		if (sala_ejecutar_interaccion(sala, argv[0], argv[1], argv[2], mostrar_texto, NULL) == 0)
			jugada_valida = false;
		
		imprimir_pantalla(sala);

		if (strcmp(argv[0], "ayuda") == 0)
			imprimir_ayuda();

		free(argv);
	}

	return true;
}

int main(int argc, char *argv[])
{
	if (argc < 3){
		printf("(0)%s "ROJO"(1)objetos.txt (2)interacciones.txt\n"BLANCO, argv[0]);
		return -1;
	}

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
	if (sala == NULL) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}

	game_loop(sala);
	sala_destruir(sala);
	return 0;
}