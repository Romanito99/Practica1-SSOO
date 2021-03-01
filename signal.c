#include <signal.h>
#include <unistd.h>
#include <stdio.h>
 
void manejador(int);
 
int main(int argc, char *argv[])
{
  
  /*Captura de senal SIGINT --> CTRL+C interrupcion de programa*/
  signal(SIGINT, manejador);
  
  printf("Proceso %d a la espera de captura de senal.\n", getpid());  
  /*Esperamos a que el usuario pulse CTRL+C para que se envie la senal*/
  pause(); 
  printf("Continua la ejecucion tras el tratamiento de senal.\n");

  return 0;
}
 
void manejador(int sig)
{
  signal(sig, manejador);
  printf("Senal %d recibida.\n", sig);
}
