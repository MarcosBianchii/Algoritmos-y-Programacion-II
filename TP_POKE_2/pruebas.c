#include "pa2mm.h"

#include "src/lista.h"
#include "src/hash.h"
#include "src/abb.h"
#include "src/sala_estrucura.h"

#include "src/estructuras.h"
#include "src/interaccion.h"
#include "src/objeto.h"
#include "src/sala.h"

#include "string.h"
#include <stdbool.h>

void pruebasCrearObjeto()
{
	pa2m_afirmar(objeto_crear_desde_string(NULL) == NULL,
		     "No puedo crear un objeto a partir de un string NULL");
	pa2m_afirmar(objeto_crear_desde_string("") == NULL,
		     "No puedo crear un objeto a partir de un string vacío");
	pa2m_afirmar(objeto_crear_desde_string("a;b") == NULL,
		     "\"a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;b") == NULL,
		     "\"a;;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;b") == NULL,
		     "\";a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;b;c") == NULL,
		     "\"a;b;c\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;true") == NULL,
		     "\"a;;true\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;false") == NULL,
		     "\";a;false\" no es un string objeto válido");

	struct objeto *objeto1 = objeto_crear_desde_string("nombre;desc;true");
	pa2m_afirmar(objeto1, "\"nombre;desc;true\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto1->nombre, "nombre") == 0, "El nombre del objeto es \"nombre\"");
	pa2m_afirmar(strcmp(objeto1->descripcion, "desc") == 0,
		     "La descripcion del objeto es \"desc\"");
	pa2m_afirmar(objeto1->es_asible == true, "El objeto es asible");

	struct objeto *objeto2 = objeto_crear_desde_string("A;Be;false\n");
	pa2m_afirmar(objeto2, "\"A;Be;false\\n\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto2->nombre, "A") == 0, "El nombre del objeto es \"A\"");
	pa2m_afirmar(strcmp(objeto2->descripcion, "Be") == 0,
		     "La descripcion del objeto es \"Be\"");
	pa2m_afirmar(objeto2->es_asible == false, "El objeto no es asible");

	free(objeto1);
	free(objeto2);
}

void pruebasCrearInteracciones()
{
	pa2m_afirmar(interaccion_crear_desde_string(NULL) == NULL,
		     "No puedo crear una interacción a partir de un string NULL");
	pa2m_afirmar(interaccion_crear_desde_string("") == NULL,
		     "No puedo crear una interacción a partir de un string vacío");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c:d:e") == NULL,
		     "\"a;b;c:d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d") == NULL,
		     "\"a;b;c;d\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d:e") == NULL,
		     "\"a;b;c;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;d:e") == NULL,
		     "\"a;b;_;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;de:f:g") == NULL,
		     "\"a;b;_;de:f:g\" no es un string interacción válido");

	struct interaccion *inter1 = interaccion_crear_desde_string("a;b;c;d:e:f");
	pa2m_afirmar(inter1, "\"a;b;c;d:e:f\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter1->objeto, "a") == 0, "El nombre del objeto es \"a\"");
	pa2m_afirmar(strcmp(inter1->verbo, "b") == 0, "El verbo es \"b\"");
	pa2m_afirmar(strcmp(inter1->objeto_parametro, "c") == 0, "El segundo objeto es \"c\"");
	pa2m_afirmar(inter1->accion.tipo == DESCUBRIR_OBJETO,
		     "El tipo de acción es DESCUBRIR_OBJETO");
	pa2m_afirmar(strcmp(inter1->accion.objeto, "e") == 0, "El objeto de la acción es \"e\"");
	pa2m_afirmar(strcmp(inter1->accion.mensaje, "f") == 0, "El mensaje de la acción es \"f\"");

	struct interaccion *inter2 = interaccion_crear_desde_string("OB;VER;_;m:_:MSG");
	pa2m_afirmar(inter1, "\"OB;VER;_;m:_:MSG\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter2->objeto, "OB") == 0, "El nombre del objeto es \"OB\"");
	pa2m_afirmar(strcmp(inter2->verbo, "VER") == 0, "El verbo es \"VER\"");
	pa2m_afirmar(strcmp(inter2->objeto_parametro, "") == 0, "El segundo objeto es vacío");
	pa2m_afirmar(inter2->accion.tipo == MOSTRAR_MENSAJE,
		     "El tipo de acción es MOSTRAR_MENSAJE");
	pa2m_afirmar(strcmp(inter2->accion.objeto, "") == 0, "El objeto de la acción es vacío");
	pa2m_afirmar(strcmp(inter2->accion.mensaje, "MSG") == 0,
		     "El mensaje de la acción es \"MSG\"");

	free(inter1);
	free(inter2);
}

void pruebas_crear_sala()
{
	pa2m_afirmar(sala_crear_desde_archivos("/ASD/ASD/", "dasD/sa2asdd") == NULL,
		     "No puedo crear la sala a partír de archivos inexistentes");

	pa2m_afirmar(sala_crear_desde_archivos("", "chanu/int.csv") == NULL,
		     "No puedo crear la sala sin objetos");

	pa2m_afirmar(sala_crear_desde_archivos("chanu/obj.dat", "chanu/vacio.txt") == NULL,
		     "No puedo crear la sala sin interacciones");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala != NULL, "Puedo crear la sala a partir de archivos no vacíos");
	pa2m_afirmar(hash_cantidad(sala->objetos) == 9, "Se leyeron 9 objetos");	       // cambie sala->cantidad_objetos por hash_cantidad(sala->objetos)
	pa2m_afirmar(lista_tamanio(sala->interacciones) == 13, "Se leyeron 13 interacciones"); // cambie sala->cantidad_interacciones por lista_tamanio(sala->interacciones) y le sume algunas interacciones para las pruebas de sala_ejecutar_interaccion()

	sala_destruir(sala);
}

void pruebas_nombre_objetos()
{
	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos(NULL, &cantidad) == NULL,
		     "No puedo obtener los nombres de objetos de una sala NULL");
	pa2m_afirmar(cantidad == -1, "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	char **objetos = sala_obtener_nombre_objetos(sala, NULL);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad no NULL");
	pa2m_afirmar(cantidad == 9, "La cantidad de elementos del vector coincide con lo esperado");

	const char *esperados[] = { "habitacion",    "mesa",  "interruptor", "pokebola", "cajon",
				    "cajon-abierto", "llave", "anillo",	     "puerta" };

	int comparaciones_exitosas = 0;

	for (int i = 0; i < cantidad; i++)
		if (strcmp(objetos2[i], esperados[i]) == 0)
			comparaciones_exitosas++;

	// pa2m_afirmar(comparaciones_exitosas == cantidad,
	// 	     "Todos los nombres de objeto son los esperados");

	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}

void pruebas_interacciones()
{
	pa2m_afirmar(sala_es_interaccion_valida(NULL, "hacer", NULL, NULL) == false,
		     "No es válido pedir interacciones de una sala NULL");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala_es_interaccion_valida(sala, NULL, "", "") == false, "No es válida una intearcción con verbo NULL");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "hacer", NULL, "") == false, "No es válida una intearcción con objeto NULL");

	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "habitacion", "") == true, "Puedo examinar la habitación");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "usar", "llave", "cajon") == true, "Puedo usar la llave en el cajón");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "pokebola", "") == true, "Puedo abrir la pokebola");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "cajon-abierto", "") == true, "Puedo examinar el cajón abierto");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "romper", "todo", "") == false, "No puedo romper todo");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "mesa", "") == false, "No puedo abrir la mesa");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "techo", "") == false, "No puedo examinar el techo");

	sala_destruir(sala);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// Pruebas del TP 2

void pruebas_vector_conocidos()
{

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos_conocidos(NULL, &cantidad) == NULL, "No puedo crear un vector de nombres conocidos con una sala NULL");
	pa2m_afirmar(cantidad == -1, "La cantidad de elementos es la adecuada");

	char **vector = sala_obtener_nombre_objetos_conocidos(sala, NULL);
	pa2m_afirmar(vector != NULL, "Puedo crear el vector de conocidos pasando cantidad NULL");
	free(vector);

	char **vector1 = sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
	pa2m_afirmar(vector != NULL, "Puedo crear el vector de conocidos pasando cantidad no NULL");
	
	bool esperados = true;
	for (int i = 0; i < cantidad; i++)
		if (!abb_buscar(sala->conocidos, vector1[i]))
			esperados = false;
	
	pa2m_afirmar(esperados, "Estan todos los nombres del vector dentro del abb");	

	free(vector1);
	sala_destruir(sala);
}

void pruebas_vector_poseidos()
{
	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos_poseidos(NULL, &cantidad) == NULL, "No puedo crear un vector de nombres poseidos con una sala NULL");
	pa2m_afirmar(cantidad == -1, "La cantidad de elementos es la adecuada");

	char **vector = sala_obtener_nombre_objetos_poseidos(sala, NULL);
	pa2m_afirmar(vector != NULL, "Puedo crear el vector de poseidos pasando cantidad NULL");
	free(vector);

	char **vector1 = sala_obtener_nombre_objetos_poseidos(sala, &cantidad);
	pa2m_afirmar(vector != NULL, "Puedo crear el vector de poseidos pasando cantidad no NULL");
	
	bool esperados = true;
	for (int i = 0; i < cantidad; i++)
		if (!abb_buscar(sala->poseidos, vector1[i]))
			esperados = false;
	
	pa2m_afirmar(esperados, "Estan todos los nombres del vector dentro del abb");	

	free(vector1);
	sala_destruir(sala);
}

void f(const char *c, enum tipo_accion a, void *aux)
{
}

void f1(const char *c, enum tipo_accion a, void *aux)
{
	if (!aux) return;

	int *contador = aux;
	(*contador)++;
}

void pruebas_ejecutar_interaccion()
{
	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "", "", "", f, NULL) == 0, "Devuelve 0 cuando recibe todo vacio");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", f, NULL) > 0, "Puedo examinar la habitacion");

	int cant_conocidos = 0;
	char **conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cant_conocidos);
	pa2m_afirmar(cant_conocidos == 3, "Se conocen 3 objetos");
	free(conocidos);
	
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "mesa", "", f, NULL) > 0, "Puedo examinar la mesa");

	int cant_poseidos = 0;
	char **poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cant_poseidos);
	pa2m_afirmar(cant_poseidos == 0, "La cantidad de poseidos es la correcta");
	free(poseidos);

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "agarrar", "pokebola", "", f, NULL), "Puedo agarrar la pokebola");
	int cant_poseidos1 = 0;
	char **poseidos1 = sala_obtener_nombre_objetos_poseidos(sala, &cant_poseidos1);
	pa2m_afirmar(cant_poseidos1 == cant_poseidos+1, "La cantidad de objetos poseidos incremento en 1");
	free(poseidos1);

	int contador = 0;
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "describir", "pokebola", "", f1, &contador) == 1, "Puedo describir un objeto");
	pa2m_afirmar(contador == 1, "Se llamo a la funcion pasada por parametro 1 vez");

	int contador1 = 0;
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "describir", "dinosaurio", "", f1, &contador1) == 0, "No puedo describir un objeto inexistente");
	pa2m_afirmar(contador1 == 0, "No se llamo a la funcion pasada por parametro");

	int contador2 = 0;
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "pokebola", "", f1, &contador2) == 2, "Puedo abrir un objeto");
	pa2m_afirmar(contador2 == 2, "Se llamo a la funcion pasada por parametro 2 veces");

	int contador3 = 0;
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "dinosaurio", "", f1, &contador3) == 0, "No puedo abrir un objeto inexistete");
	pa2m_afirmar(contador3 == 0, "No se llamo a la funcion pasada por parametro");

	int contador4 = 0;
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "eliminar", "pokebola", "", f1, &contador4) == 1, "Puedo eliminar un objeto");
	pa2m_afirmar(contador4 == 1, "Se llamo a la funcion pasada por parametro 1 vez");

	int contador5 = 0;
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "eliminar", "dinosaurio", "", f1, &contador5) == 0, "No puedo eliminar un objeto inexistete");
	pa2m_afirmar(contador5 == 0, "No se llamo a la funcion pasada por parametro");

	sala_ejecutar_interaccion(sala, "agarrar", "llave", "", f, NULL);

	int contador6 = 0;
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "usar", "llave", "cajon", f1, &contador6) == 2, "Puedo usar la llave en el cajon");
	pa2m_afirmar(contador6 == 2, "Se llamo a la funcion pasada por parametro 2 veces");

	int contador7 = 0;
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "entrar", "cajon-abierto", "", f1, &contador7) == 1, "Puedo escapar por el cajon-abierto");
	pa2m_afirmar(contador7 == 1, "Se llamo a la funcion pasada por parametro 1 vez");
	pa2m_afirmar(sala_escape_exitoso(sala), "El estado del juego es ganado");

	sala_destruir(sala);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creación de objetos");
	pruebasCrearObjeto();

	pa2m_nuevo_grupo("Pruebas de creación de interacciones");
	pruebasCrearInteracciones();

	pa2m_nuevo_grupo("Pruebas de creación de sala");
	pruebas_crear_sala();

	pa2m_nuevo_grupo("Pruebas del vector de nombres");
	pruebas_nombre_objetos();

	pa2m_nuevo_grupo("Pruebas de interacciones");
	pruebas_interacciones();

	pa2m_nuevo_grupo("Pruebas del TP 2");

	pa2m_nuevo_grupo("Pruebas de vectores conocidos y poseidos");
	pruebas_vector_conocidos();
	pruebas_vector_poseidos();

	pa2m_nuevo_grupo("Pruebas de sala_ejecutar_interaccion");
	pruebas_ejecutar_interaccion();

	return pa2m_mostrar_reporte();
}
