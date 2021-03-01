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
    system("mkdir estudiantes" );
    pipe(tuberiaC);
    sprintf(wr_tuberiaC, "%d", tuberiaC[ESCRITURA]);
    signal(SIGINT, manejador);
    switch(pid_a = fork()){
        case -1:
            fprintf(stderr,"Error al crear el proceso hijo: %s\n",strerror(errno));
            
        case 0:
            if(execve("./Pa", parmList,envParms)==-1){
                fprintf(stderr,"error en execl: %s\n",strerror(errno));
                
            }
        default:
        pid_a= wait(NULL);
        
		system("echo  ******Log del sistema****** > log.txt");
        system("echo  Creacion de directorios finalizada >> log.txt");
        
        if ((pid_b = fork())== 0){
            //Codigo del proceso PB
            
            if(execve("./Pb", parmList,envParms)==-1){
                fprintf(stderr,"error en execl: %s\n",strerror(errno));
                
            }
        }else if (pid_b==-1){
            perror("Error con el proceso PB");
            exit(1);

        }else if((pid_c = fork())== 0){
            //Codigo del proceso PC
            if(execl("./Pc", wr_tuberiaC)==-1){
                fprintf(stderr,"error en execl: %s\n",strerror(errno));
                            }
        }else if(pid_c==-1) {
            perror("Error con el proceso PC");
            exit(1);
        }
        else{
            pid_b= wait(NULL);
            pid_c= wait(NULL);
            system("echo Copia de modelos de examen, finalizada. >> log.txt" );
            system("echo Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada. >> log.txt" );

            read(tuberiaC[LECTURA],readBuffer,sizeof(readBuffer));
            sprintf(command,"echo La nota media de la clase es: %s >> log.txt",readBuffer);
			system(command);
            system("echo ******FIN DEL PROGRAMA****** >> log.txt");
            
            
            
            exit(0);
        }
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
    } else if(pid_d == 0){
         if(execve("./Pd", parmList,envParms)==-1){
                fprintf(stderr,"error en execl: %s\n",strerror(errno));
                
            }
    }

    /*Esperamos que finalice el proceso PD*/

    waitpid(pid_d, &d_status, 0); 
    printf("[MANAGER] Proceso PD %d finalizado\n", pid_d);  
    
    printf("[MANAGER] Finalizado\n"); 

    exit(EXIT_FAILURE);

}