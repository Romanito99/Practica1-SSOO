#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h> 

int main(){
int pid;
int sid;
        
    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
        we can exit the parent process. */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* Change the file mode mask */
    umask(0);       
    
    /* Open any logs here */
    
    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        /* Log any failures here */
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory */
    if ((chdir("/")) < 0) {
        /* Log any failure here */
        exit(EXIT_FAILURE);
    }
      
    /* The Big Loop */
    while (1) {
        system("cp -r /home/cesar/Escritorio/CURSSOCOVID/SSOO2/Practica1-SSOO/estudiantes /home/cesar/Escritorio/CURSSOCOVID/SSOO2/Practica1-SSOO/copia");
        sleep(60); /* wait 30 seconds */
    }
}