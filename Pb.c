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
	system(command);
	}
int main(){
	char cadena[256]; 
	/* Abrimos "fichero1.txt" en modo texto y
	 * guardamos su direccion en el puntero. */
	fichero = fopen("estudiantes_p1.text", "rt");

	if (fichero == NULL) {
		printf("Error: No se ha podido crear el fichero fichero1.txt");
		exit(EXIT_FAILURE);
    
	} else {
		while( fgets(cadena, 15 , fichero)){
			Copiar(cadena);
        }
		/* Cerramos "fichero1.txt". */
		fclose(fichero);
		exit(0);
    }


}
