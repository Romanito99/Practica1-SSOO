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
	FILE *log;

pid_t pid_a;
pid_t pid_b;
pid_t pid_c;
int estado;
char *const parmList[]= {NULL,NULL, NULL};
char *const envParms[]= {NULL};

void manejador(int signum);
 
int main(int argc, char *argv[]){
    int tuberiaC[2];
    char readBuffer[80];
    char wr_tuberiaC[256];
    char command[256];
    char cadena[256];
    system("mkdir estudiantes" );
    pipe(tuberiaC);
    sprintf(wr_tuberiaC, "%d", tuberiaC[ESCRITURA]);
    signal(SIGINT, manejador);
    log = fopen("log.txt", "w+");
	if (log == NULL) {
		printf("[PA] Error: No se ha podido crear el fichero fichero1.txt");
		exit(EXIT_FAILURE);
    }
    
    switch(pid_a = fork()){
        case -1:
            fprintf(stderr,"[MANAGER] Error al crear el proceso hijo: %s\n",strerror(errno));
            
        case 0:
            if(execve("./Pa", parmList,envParms)==-1){
                fprintf(stderr,"[MANAGER] Error en execl: %s\n",strerror(errno)); 
            }
        default:
            pid_a= wait(NULL);
            fputs("******Log del sistema******\n", log);
            fputs("Creacion de directorios finalizada\n",log);
            if ((pid_b = fork())== 0){
                //Codigo del proceso PB
                if(execve("./Pb", parmList,envParms)==-1){
                    fprintf(stderr,"[MANAGER] Error en execl: %s\n",strerror(errno));   
                }
            }else if (pid_b==-1){
                perror("[MANAGER] Error con el proceso PB");
                exit(1);
            }else if((pid_c = fork())== 0){
                //Codigo del proceso PC
                if(execl("./Pc", wr_tuberiaC)==-1){
                    fprintf(stderr,"[MANAGER] Error en execl: %s\n",strerror(errno));
                }
            }else if(pid_c==-1) {
                perror("[MANAGER] Error con el proceso PC");
                exit(1);
            }
            else{
                pid_b= wait(NULL);
                pid_c= wait(NULL);
                fputs("Copia de modelos de examen, finalizada.\n",log );
                fputs("Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.\n",log );
                read(tuberiaC[LECTURA],readBuffer,sizeof(readBuffer));
                sprintf(cadena,"La nota media de la clase es: %s",readBuffer);
                fputs(cadena,log);
                fputs("\n******FIN DEL PROGRAMA******",log);
                exit(0);
            }
        fclose(log);
    }
    return 0;
}
void manejador(int signum){
    /*Interrumpimos los procesos PA, PB y PC*/
    kill(pid_c, SIGINT);
    kill(pid_b, SIGINT);
    kill(pid_a, SIGINT);
    printf("[MANAGER] Procesos finalizados\n"); 

    /*Creamos el proceso PD*/
    pid_t pid_d; 
    int d_status; 
    if((pid_d = fork()) == -1){
        fprintf(stderr, "[MANAGER] Error al crear el proceso PD\n");
        exit(EXIT_FAILURE); 
    }else if(pid_d == 0){
         if(execve("./Pd", parmList,envParms)==-1){
                fprintf(stderr,"error en execl: %s\n",strerror(errno));
                
            }
    }

    /*Esperamos que finalice el proceso PD*/
    waitpid(pid_d, &d_status, 0); 
    printf("[MANAGER] Proceso PD %d finalizado\n", pid_d);  
    fputs("echo La ejecucion del programa ha sido detenida voluntariamente.",log );
    fputs("echo ******FIN DEL PROGRAMA******",log);
    printf("[MANAGER] Finalizado\n"); 
    exit(EXIT_SUCCESS);   
}