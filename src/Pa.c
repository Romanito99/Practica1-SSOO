/******************************************************
 * Proyecto:                Práctica 1 de Sistemas Operativos II
 * 
 * Nombre de la Clase:      Pa.c
 * 
 * Autor:                   César Braojos Corroto
 * 
 * 
 * 
 * Proposito:               Creación de los procesos PA, PB y PC, registra la finalización de cada tarea, la nota media de los estudiantes en la primera prueba y 
 *                          crea el archivo log.txt
 * 
 ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <signal.h>

 	/* Declaramos la variable fichero como puntero a FILE. */
	FILE *fichero;

	
	/* Declaramos los metodos */
	void Manejador(int signum);
	void Creardirectorios(char *cadena);
/***********************************************Metodo principal***********************************************/
int main(){
	signal(SIGINT, Manejador);
	char cadena[256];
	
	/* Abrimos "fichero1.txt" en modo texto y
	 * guardamos su direccion en el puntero. */
	
	fichero = fopen("utils/estudiantes_p1.text", "rt");

	if (fichero == NULL) {
		printf("[PA] Error: No se ha podido crear el fichero fichero1.txt");
		exit(EXIT_FAILURE);
    
	} else {
		/* Se obtiene el primer caracter del fichero
		 * y se almacena en la variable caracter. */
		while( fgets(cadena, 15 , fichero)){
			Creardirectorios(cadena);
        }
		/* Cerramos "fichero1.txt". */
		fclose(fichero);
		exit(EXIT_SUCCESS);
    }

}
/**********************************************Metodo para crear una carpeta con cada dni**********************************************/
void Creardirectorios(char *cadena){
	char linea[8];
   	char command[256];
	const char s[2] = " ";
   	char *p_dni;
	
			
			p_dni = strtok(cadena, s);
			sprintf(command,"mkdir estudiantes/%s",p_dni);
			if(system(command)!=0){
				printf("[PA] Esta carpeta ya existe , no podemos crearla\n");
			}


}
/**********************************************Metodo para finalizar el proceso en caso de que se interrumpa**********************************************/
void Manejador(int signum){
	printf("[PA] Proceso finalizaddo\n");
	exit(0);
}
