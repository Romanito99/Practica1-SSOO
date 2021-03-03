#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <signal.h>

 /* Declaramos la variable fichero como puntero a FILE. */
	FILE *fichero;
	/* Declaramos los metodos . */
	void Copiar(char *cadena);
	void manejador(int signum);
	/* Declaramos la variable reslutado como puntero. */
	
int main(){
	signal(SIGINT, manejador);
	char cadena[256]; 
	/* Abrimos "fichero1.txt" en modo texto y guardamos su direccion en el puntero. */
	fichero = fopen("estudiantes_p1.text", "rt");

	if (fichero == NULL) {
		printf("[PB] Error: No se ha podido crear el fichero fichero1.txt");
		exit(EXIT_FAILURE);
    
	} else {
		while( fgets(cadena, 15 , fichero)){
			Copiar(cadena);
        }
		/* Cerramos "fichero1.txt". */
		fclose(fichero);
		exit(EXIT_SUCCESS);
    }
}

void manejador(int signum){
	printf("[Pb] Proceso finalizaddo\n");
	exit(0);
}

void Copiar(char *cadena){
	char command[256];
	char linea[8];
	const char s[2] = " ";
   	char *Dni;
	char *Examen;	
	Dni = strtok(cadena, s);
		if( Dni != NULL ) {
      		Examen= strtok(NULL, s);
   		}
	sprintf(command,"cp MODELOSEXAMEN/MODELO%s.pdf estudiantes/%s",Examen,Dni);
	if(system(command)!=0){
		printf("[PB]Error al copiar el archivo\n");
	}
}
