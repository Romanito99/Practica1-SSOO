/******************************************************
 * Proyecto:                Práctica 1 de Sistemas Operativos II
 * 
 * Nombre de la Clase:      Pc.c
 * 
 * Autor:                   César Braojos Corroto
 * 
 * p_dni:                     03949910M
 * 
 * Fecha final:             19/2/2019
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
	void manejador(int signum);
	int Escribir_fichero(char *cadena,float media);

/***********************************************Metodo principal***********************************************/
 void main(int argc, char *argv[]){
	signal(SIGINT, manejador);
    char readBuffer[80];
	char cadena[256];
	char msg[256];
	float media=0; 
	/* Abrimos "fichero1.txt" en modo texto y
	 * guardamos su direccion en el puntero. */
	fichero = fopen("utils/estudiantes_p1.text", "rt");

	if (fichero == NULL) {
		printf("[PC] Error: No se ha podido crear el fichero fichero1.txt");
		exit(EXIT_FAILURE);
    
	} else {
		while( fgets(cadena, 15 , fichero)){
			media=Escribir_fichero(cadena,media);
        }
		/* Cerramos "fichero1.txt". */
		media=media/15; 
		fclose(fichero);
		sprintf(msg,"La nota del examen es %0.2f",media);
		write(atoi(argv[0]), msg,strlen(msg)+1);
		exit(EXIT_SUCCESS);
    }
}
/***********************************************Metodo para finalizar el proceso en caso de que se interrumpa***********************************************/
void manejador(int signum){
	printf("[PC] Proceso finalizaddo\n");
	exit(0);
}
/***********************************************Metodo para escribir el fichero de notas***********************************************/ 
int Escribir_fichero(char *cadena,float media){
	char command[256];
	
	char linea[8];
	const char s[2] = " ";
   	char *p_dni;
	char *p_examen;	
	int nota;
		p_dni = strtok(cadena, s);
		if( p_dni != NULL ) {
		p_examen= strtok(NULL, s);
		}
		if( p_examen != NULL ) {
		nota= atoi(strtok(NULL, s));
		}
		media+=nota;	
		nota=10-nota;
		sprintf(command,"echo La nota que debes obtener en este nuevo examen para superar la prueba es %d >   estudiantes/%s/nota.txt",nota ,p_dni);

		if (system(command)!=0){
			printf("[PC] Error escribiendo el archivo\n");
		}
	return media;
}