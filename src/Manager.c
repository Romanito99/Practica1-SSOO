/******************************************************
* Proyecto:                Práctica 1 de Sistemas Operativos II
* 
* Nombre de la Clase:      manager.c
* 
* Autor:                   César Braojos Corroto
* 
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
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>

#define ESCRITURA 1
#define LECTURA 0

    /* Declaramos la variable fichero como puntero a FILE. */
	FILE *fichero;
    /* Declaramos la variable cadena de tipo array char. */
    char *const g_parmList[] = {NULL,NULL, NULL};
    char *const g_envParms[] = {NULL};
    /*Declaramos las variables de los procesos*/
    pid_t g_pid_a;
    pid_t g_pid_b;
    pid_t g_pid_c;
    int g_estado;
    /*Declaramos los metodos*/
    void Manjeador(int signum);

/***********************************************Metodo principal***********************************************/

int main(int argc, char *argv[]){

    int tuberia_c[2];
    char readBuffer[80];
    char wr_tuberia_c[256];
    char command[256];
    char cadena[256];

    /*Recogemos la señal de interrupcion*/
    signal(SIGINT, Manjeador);
    /*Lanzamos el demonio que se va a encargar de realizar la copia de seguridad*/
    if(system("./exec/daemon")!=0){
        fprintf(stderr,"[MANAGER]Error lanzando el daemon\n");
    }
   
    /*Abrimos el fichero fichero*/
    fichero = fopen("Log.txt", "w+");
	if (fichero == NULL) {
		fprintf(stderr,"[PA] Error: No se ha podido crear el fichero fichero1.txt");
		exit(EXIT_FAILURE);
    }
    pipe(tuberia_c);
    /*Seleccionamos el canal de escritura para el proceso C*/
    sprintf(wr_tuberia_c, "%d", tuberia_c[ESCRITURA]);
    /*Creamos el proceso A*/
    switch(g_pid_a = fork()){
        case -1:
            fprintf(stderr,"[MANAGER] Error al crear el proceso hijo PA");
            exit(EXIT_FAILURE); 
        case 0:
            if(execve("./exec/Pa", g_parmList,g_envParms)==-1){
                fprintf(stderr,"[MANAGER] Error en execl PA"); 
                exit(EXIT_FAILURE); 
            }
        default:
            g_pid_a= wait(NULL);
            /*Termina el proceso A , seguidamente comienzan el proceso B y C*/
            fputs("******fichero del sistema******\n", fichero);
            fputs("Creacion de directorios finalizada\n",fichero);
            if ((g_pid_b = fork())== 0){
                //Codigo del proceso PB
                if(execve("./exec/Pb", g_parmList,g_envParms)==-1){
                    fprintf(stderr,"[MANAGER] Error en execl PB");  
                    exit(EXIT_FAILURE); 
                }
            }else if (g_pid_b==-1){
                fprintf(stderr,"[MANAGER] Error al crear el proceso hijo PB");
                exit(EXIT_FAILURE); 
            }else if((g_pid_c = fork())== 0){
                //Codigo del proceso PC
                if(execl("./exec/Pc", wr_tuberia_c,NULL)==-1){
                    fprintf(stderr,"[MANAGER] Error en execl PC");
                    exit(EXIT_FAILURE); 
                }
            }else if(g_pid_c==-1) {
               fprintf(stderr,"[MANAGER] Error al crear el proceso hijo PC");
                exit(EXIT_FAILURE); 
            }
            else{
                /*Esperamos que terminen los procesos B y C , y finalizamos completando el Log*/
                g_pid_b= wait(NULL);
                g_pid_c= wait(NULL);
                fputs("Copia de modelos de examen, finalizada.\n",fichero );
                fputs("Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.\n",fichero );
                //Leemos de la tuberia el valor que envia el proceso c//
                read(tuberia_c[LECTURA],readBuffer,sizeof(readBuffer));
                sprintf(cadena,"La nota media de la clase es: %s",readBuffer);
                fputs(cadena,fichero);
                fputs("\n******FIN DEL PROGRAMA******",fichero);
                
                
            }
        fclose(fichero);
    }
    exit(EXIT_SUCCESS); 
}
/**********************************************Metodo que controla la señal**********************************************/
void Manjeador(int signum){
    /*Interrumpimos los procesos PA, PB y PC*/
    kill(g_pid_c, SIGINT);
    kill(g_pid_b, SIGINT);
    kill(g_pid_a, SIGINT);
    printf("[MANAGER] Procesos finalizados\n"); 
    /*Creamos el proceso PD*/
    pid_t pid_d; 
    int d_status; 
    if((pid_d = fork()) == -1){
        fprintf(stderr, "[MANAGER] Error al crear el proceso PD\n");
        exit(EXIT_FAILURE); 
    }else if(pid_d == 0){
         if(execve("./exec/Pd", g_parmList,g_envParms)==-1){
                fprintf(stderr,"[MANAGER]Error en execl PD");
                exit(EXIT_FAILURE); 
            }
    }
    /*Esperamos que finalice el proceso PD*/
    waitpid(pid_d, &d_status, 0); 
    printf("[MANAGER] Proceso PD %d finalizado\n", pid_d);  
    fputs("La ejecucion del programa ha sido detenida voluntariamente.\n",fichero );
    fputs("******FIN DEL PROGRAMA******",fichero);
    printf("[MANAGER] Finalizado\n");
    fclose(fichero);
    exit(EXIT_SUCCESS);   
}
