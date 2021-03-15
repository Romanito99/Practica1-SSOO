/******************************************************
 * Proyecto:                Práctica 1 de Sistemas Operativos II
 * 
 * Nombre de la Clase:      Pd.c
 * 
 * Autor:                   César Braojos Corroto
 * 
 * Dni:                     03949910M
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

 /* Declaramos la variable fichero como puntero a FILE. */
	FILE *fichero;
	/* Declaramos la variable cadena de tipo array char. */
	/* Declaramos la variable reslutado como puntero. */

/***********************************************Metodo principal***********************************************/
int main(){
        char command[256];
        sprintf(command,"rm -rf estudiantes");
		if (system(command)!=0){
			printf("error al borrar el archvo\n");
		}
	exit(0);
    
}