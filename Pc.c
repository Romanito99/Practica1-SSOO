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
		system(command);
		return media;
	}
int main(int argc, char *argv[]){
    char readBuffer[80];
	char cadena[256];
	float media=0; 
	/* Abrimos "fichero1.txt" en modo texto y
	 * guardamos su direccion en el puntero. */
	fichero = fopen("estudiantes_p1.text", "rt");

	if (fichero == NULL) {
		printf("Error: No se ha podido crear el fichero fichero1.txt");
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
		exit(0);
    }
}