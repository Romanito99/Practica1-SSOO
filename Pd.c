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

int main(){
        char command[256];
        sprintf(command,"rm -rf estudiantes");
		if (system(command)!=0){
			printf("error al borrar el archvo\n");
		}
	exit(0);
    
}