#include "src/hash.h"
#include "src/estructuras.h"
#include "pa2m.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define AZUL "\033[0;34m"
#define NEGRO "\033[0;30m"

bool devolver_true(const char *clave, void *valor, void *aux)
{
	return true;
}

bool buscar_al_impostor(const char *clave, void *valor, void *aux)
{
	if (strcmp(valor, aux) == 0)
		return false;
	return true;
}

void print_hash(hash_t *hash)
{
        for (int i = 0; i < hash->capacidad; i++){
                nodo_t *it = hash->tabla[i];
                if (i < 10) printf(" ");
                printf(VERDE"%i: ", i);
                while (it){
                        printf(AZUL"%s"AMARILLO"/"BLANCO"%s", it->clave, (char*)it->valor);
                        it = it->siguiente;
                        if (it) printf(NEGRO" -> ");
                }
                printf("\n");
        }
	printf("\n"BLANCO);
}

void se_crea_la_tabla_de_forma_correcta()
{
	hash_t *hash10 = hash_crear(10);
	pa2m_afirmar(hash10->tabla != NULL, "Se creo una tabla exitosamente");
	pa2m_afirmar(hash10->capacidad == 10, "La tabla tiene capacidad para 10 elementos");
	pa2m_afirmar(hash_cantidad(hash10) == 0, "La tabla esta vacia");
	hash_destruir(hash10);

	hash_t *hash2 = hash_crear(2);
	pa2m_afirmar(hash2->capacidad == 3, "Se crea una tabla con capacidad == 3 pasando capacidad < 3");
	hash_destruir(hash2);
}

void se_insertan_elementos_de_forma_correcta()
{
	hash_t *hash = hash_crear(5);

	pa2m_afirmar(hash_insertar(hash, "gonzalo", "valor", NULL) == hash, "Se inserto un primer elemento");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El tamanio de la tabla es 1");

	pa2m_afirmar(hash_insertar(hash, "sebastian", "valor", NULL) == hash, "Se inserto un segundo elemento");
	pa2m_afirmar(hash_cantidad(hash) == 2, "El tamanio de la tabla es 2");

	pa2m_afirmar(hash_insertar(hash, "ricardo", "valor", NULL) == hash, "Se inserto un tercer elemento");
	pa2m_afirmar(hash_cantidad(hash) == 3, "El tamanio de la tabla es 3");
	
	pa2m_afirmar(hash_insertar(hash, "mauro", "hola", NULL) == hash, "Se inserto un cuarto elemento");
	pa2m_afirmar(hash_cantidad(hash) == 4, "El tamanio de la tabla es 4");
	
	void *anterior = NULL;
	pa2m_afirmar(hash_insertar(hash, "mauro", "valor", &anterior) == hash, "Se actualizo el ultimo elemento");
	pa2m_afirmar(hash_cantidad(hash) == 4, "El tamanio de la tabla sigue siendo 4");
	pa2m_afirmar(strcmp(anterior, "hola") == 0, "El valor del elemento anterior es el correcto");

	pa2m_afirmar(hash_insertar(hash, "camilo", "valor", NULL) == hash, "Se inserto un quinto elemento");
	pa2m_afirmar(hash_cantidad(hash) == 5, "El tamanio de la tabla es 5");

	pa2m_afirmar(hash_insertar(hash, "ramiro", NULL, NULL) == hash, "Se puede insertar un valor NULL");
	pa2m_afirmar(hash_cantidad(hash) == 6, "El tamanio de la tabla es 6");

	pa2m_afirmar(hash->capacidad == 10, "La tabla crecio y ahora es capaz de 10 elementos");

	hash_destruir(hash);

	hash_t *alpha_hash = hash_crear(0);
	for (int i = 0; i < 256; i++){
		char s[2] = {(char)i, '\0'};
		hash_insertar(alpha_hash, s, "v", NULL);

	}

	pa2m_afirmar(hash_cantidad(alpha_hash) == 256, "Se insertaron 256 elementos cada uno en una nueva posicion de la tabla");
	hash_destruir(alpha_hash);

	hash_t *omega_hash = hash_crear(0);
	int i = 0;
	int j = 256;
	while (i < 256){
		char s[3] = {(char)i++, (char)j--, '\0'};
		hash_insertar(omega_hash, s, "v", NULL);
	}

	pa2m_afirmar(hash_cantidad(omega_hash) == 256, "Se insertaron 256 elementos en una misma posicion de la tabla");
	hash_destruir(omega_hash);
}

void se_quitan_elementos_de_forma_correcta()
{
	hash_t *hash = hash_crear(10);
	
	hash_insertar(hash, "Alex", "Leon", NULL);
	hash_insertar(hash, "Gloria", "Hipopotamo", NULL);
	hash_insertar(hash, "Marty", "Zebra", NULL);
	hash_insertar(hash, "Melman", "Jirafa", NULL);
	hash_insertar(hash, "Julien", "Lemur", NULL);

	pa2m_afirmar(strcmp(hash_quitar(hash, "Gloria"), "Hipopotamo") == 0, "Se quito el elemento correctamente");
	pa2m_afirmar(hash_cantidad(hash) == 4, "El tamanio de la tabla es 4");

	pa2m_afirmar(!hash_quitar(hash, "Maurice"), "No se puede quitar un elemento que no existe");
	pa2m_afirmar(hash_cantidad(hash) == 4, "El tamanio de la tabla sigue siendo 4");

	pa2m_afirmar(strcmp(hash_quitar(hash, "Marty"), "Zebra") == 0, "Se quito el elemento correctamente");
	pa2m_afirmar(hash_cantidad(hash) == 3, "El tamanio de la tabla es 3");

	hash_destruir(hash);
}

void se_obtiene_elementos_de_forma_correcta()
{
	hash_t *hash = hash_crear(10);

	hash_insertar(hash, "matias", "valor", NULL);
	hash_insertar(hash, "lucas", "valor", NULL);
	hash_insertar(hash, "esteban", "valor", NULL);
	hash_insertar(hash, "gonzalo", "valor", NULL);

	pa2m_afirmar(strcmp(hash_obtener(hash, "matias"), "valor") == 0, "Se obtuvo el valor correcto");
	pa2m_afirmar(strcmp(hash_obtener(hash, "lucas"), "valor") == 0, "Se obtuvo el valor correcto");
	pa2m_afirmar(!hash_obtener(hash, "ricardo"), "No se encontro un valor inexistente");

	hash_destruir(hash);
}

void se_contienen_los_elementos_buscados()
{
	hash_t *hash = hash_crear(10);

	hash_insertar(hash, "matias", "valor", NULL);
	hash_insertar(hash, "lucas", "valor", NULL);
	hash_insertar(hash, "esteban", "valor", NULL);
	hash_insertar(hash, "gonzalo", "valor", NULL);

	pa2m_afirmar(hash_contiene(hash, "matias"), "Se contiene el elemento buscado");
	pa2m_afirmar(hash_contiene(hash, "lucas"), "Se contiene el elemento buscado");
	pa2m_afirmar(!hash_contiene(hash, "rodolfo"), "No se contiene un elemento inexistente");

	hash_destruir(hash);
}

void se_obtiene_la_cantidad_de_elementos_de_forma_correcta()
{
	hash_t *hash = hash_crear(10);

	hash_insertar(hash, "matias", "valor", NULL);
	hash_insertar(hash, "lucas", "valor", NULL);

	pa2m_afirmar(hash_cantidad(hash) == 2, "Se contaron 2 elementos");
	
	hash_insertar(hash, "esteban", "valor", NULL);
	pa2m_afirmar(hash_cantidad(hash) == 3, "Se contaron 3 elementos");

	hash_insertar(hash, "gonzalo", "valor", NULL);
	pa2m_afirmar(hash_cantidad(hash) == 4, "Se contaron 4 elementos");

	hash_quitar(hash, "matias");
	pa2m_afirmar(hash_cantidad(hash) == 3, "Se contaron 3 elementos");

	hash_quitar(hash, "lucas");
	pa2m_afirmar(hash_cantidad(hash) == 2, "Se contaron 2 elementos");

	hash_destruir(hash);
}

void se_destruye_la_tabla_de_forma_correcta()
{
	hash_t *hash = hash_crear(10);

	char *elemento0 = malloc(sizeof(char)*10); strcpy(elemento0, "elemento0");
	char *elemento1 = malloc(sizeof(char)*10); strcpy(elemento1, "elemento1");
	char *elemento2 = malloc(sizeof(char)*10); strcpy(elemento2, "elemento2");

	hash_insertar(hash, "matias", elemento0, NULL);
	hash_insertar(hash, "lucas", elemento1, NULL);
	hash_insertar(hash, "esteban", elemento2, NULL);

	printf("Aca pruebo la funcion de destruccion...\n\
Creo 3 elementos con malloc, no deberia perder memoria\n");

	hash_destruir_todo(hash, free);
}

void se_itera_la_tabla_de_forma_correcta()
{
	hash_t *hash = hash_crear(10);

	hash_insertar(hash, "lucas", "crewmate", NULL);
	hash_insertar(hash, "esteban", "crewmate", NULL);
	hash_insertar(hash, "gonzalo", "crewmate", NULL);
	hash_insertar(hash, "manuel", "crewmate", NULL);
	hash_insertar(hash, "tito", "impostor", NULL);
	hash_insertar(hash, "carlos", "crewmate", NULL);
	hash_insertar(hash, "ricardo", "crewmate", NULL);

	print_hash(hash);

	pa2m_afirmar(hash_con_cada_clave(hash, devolver_true, NULL) == hash_cantidad(hash), "Se iteraron todos los elementos");
	pa2m_afirmar(hash_con_cada_clave(hash, buscar_al_impostor, "impostor") == 2, "Se itero hasta encontrar al impostor"); // el 2 lo saque usando la funcion de mas arriba

	hash_destruir(hash);
}

void pruebas_NULL()
{
	hash_t *hash = hash_crear(10);

	pa2m_afirmar(!hash_insertar(NULL, "franco", "valor", NULL), "No se puede insertar un elemento en un hash NULL");
	pa2m_afirmar(!hash_insertar(hash, NULL, "valor", NULL), "No se puede insertar una clave NULL");

	pa2m_afirmar(!hash_quitar(NULL, "franco"), "No se puede quitar un elemento en un hash NULL");
	pa2m_afirmar(!hash_quitar(hash, NULL), "No se puede quitar una clave NULL");

	pa2m_afirmar(!hash_obtener(NULL, "franco"), "No se puede obtener un elemento en un hash NULL");
	pa2m_afirmar(!hash_obtener(hash, NULL), "No se puede obtener una clave NULL");

	pa2m_afirmar(!hash_contiene(NULL, "franco"), "No se puede contener un elemento en un hash NULL");
	pa2m_afirmar(!hash_contiene(hash, NULL), "No se puede contener una clave NULL");

	pa2m_afirmar(!hash_cantidad(NULL), "No se puede contar un hash NULL");

	pa2m_afirmar(!hash_con_cada_clave(NULL, devolver_true, NULL), "No se puede iterar un hash NULL");
	pa2m_afirmar(!hash_con_cada_clave(hash, NULL, NULL), "No se puede iterar con una funcion NULL");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de Hash");

	pa2m_nuevo_grupo("Pruebas de hash_crear");
	se_crea_la_tabla_de_forma_correcta();

	pa2m_nuevo_grupo("Pruebas de hash_insertar");
	se_insertan_elementos_de_forma_correcta();

	pa2m_nuevo_grupo("Pruebas de hash_quitar");
	se_quitan_elementos_de_forma_correcta();

	pa2m_nuevo_grupo("Pruebas de hash_obtener");
	se_obtiene_elementos_de_forma_correcta();

	pa2m_nuevo_grupo("Pruebas de hash_contiene");
	se_contienen_los_elementos_buscados();

	pa2m_nuevo_grupo("Pruebas de hash_cantidad");
	se_obtiene_la_cantidad_de_elementos_de_forma_correcta();

	pa2m_nuevo_grupo("Pruebas de hash_destruir_todo");
	se_destruye_la_tabla_de_forma_correcta();

	pa2m_nuevo_grupo("Pruebas de hash_con_cada_clave");
	se_itera_la_tabla_de_forma_correcta();

	pa2m_nuevo_grupo("Pruebas con hash NULL");
	pruebas_NULL();

	return pa2m_mostrar_reporte();
}