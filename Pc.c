#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <signal.h>

 /* Declaramos la variable fichero como puntero a FILE. */
	FILE *fichero;
	/* Declaramos la variable cadena de tipo array char. */
	void manejador(int signum);
	int Copiar(char *cadena,float media)

	/* Declaramos la variable reslutado como puntero. */

 void main(int argc, char *argv[]){
	signal(SIGINT, manejador);
    char readBuffer[80];
	char cadena[256];
	char msg[256];
	float media=0; 
	/* Abrimos "fichero1.txt" en modo texto y
	 * guardamos su direccion en el puntero. */
	fichero = fopen("estudiantes_p1.text", "rt");

	if (fichero == NULL) {
		printf("[PC] Error: No se ha podido crear el fichero fichero1.txt");
		exit(EXIT_FAILURE);
    
	} else {
		while( fgets(cadena, 15 , fichero)){
			media=Copiar(cadena,media);
        }
		/* Cerramos "fichero1.txt". */
		media=media/15; 
		fclose(fichero);
		sprintf(msg,"La nota del examen es %f",media);
		write(atoi(argv[0]), msg,strlen(msg)+1);
		exit(EXIT_SUCCESS);
    }
}

void manejador(int signum){
	printf("[PC] Proceso finalizaddo\n");
	exit(0);
}

int Copiar(char *cadena,float media){
	char command[256];
	
	char linea[8];
	const char s[2] = " ";
   	char *Dni;
	char *Examen;	
	char *Nota;
	int nota;
		Dni = strtok(cadena, s);
		if( Dni != NULL ) {
		Examen= strtok(NULL, s);
		}
		if( Examen != NULL ) {
		nota= atoi(strtok(NULL, s));
		}
		media+=nota;	
		nota=10-nota;
		sprintf(command,"echo La nota que debes obtener en este nuevo examen para superar la prueba es %d >   estudiantes/%s/nota.txt",nota ,Dni);

		if (system(command)!=0){
			printf("[PC] Error escribiendo el archivo\n");
		}
	return media;
}