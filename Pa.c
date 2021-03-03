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
	

	/* Declaramos la variable reslutado como puntero. */
	char *resultado;
	/* Declaramos los metodos */
	void manejador(int signum);
	void Creardirectorios(char *cadena);

int main(){
	signal(SIGINT, manejador);
	char cadena[256];
	
	/* Abrimos "fichero1.txt" en modo texto y
	 * guardamos su direccion en el puntero. */
	
	fichero = fopen("estudiantes_p1.text", "rt");

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

void Creardirectorios(char *cadena){
	char linea[8];
   	char command[256];
	const char s[2] = " ";
   	char *Dni;
	
			
			Dni = strtok(cadena, s);
			sprintf(command,"mkdir estudiantes/%s",Dni);
			
			if(system(command)!=0){
				printf("[PA] Esta carpeta ya existe , no podemos crearla\n");
			}


}


void manejador(int signum){
	printf("[PA] Proceso finalizaddo\n");
	exit(0);
}