/******************************************************
 * Proyecto:                Práctica 1 de Sistemas Operativos II
 * 
 * Nombre de la Clase:      daemon.c
 * 
 * Autor:                   César Braojos Corroto
 * 
 * Dni:                     03949910M
 * 
 * Fecha final:             19/2/2019
 * 
 * Proposito:               Creación de los procesos PA, PB y PC, registra la finalización de cada tarea, la nota media de los estudiantes en la primera prueba y 
 *                          crea el archivo log.txt
 * 
 ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h> 

/***********************************************Metodo principal***********************************************/
int main(){
int pid;
int sid;
        
    /* Fork para crear un proceso hijo que ejecutara el Daemon*/
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);       
    
    /* Creamos un SID para el proceso hijo*/
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }
   
  
      
/***********************************************Loop infinito ***********************************************/
    while (1) {
        sleep(60);
        system("cp -r /home/cesar/Escritorio/CURSSOCOVID/SSOO2/Practica1-SSOO/estudiantes /home/cesar/Escritorio/CURSSOCOVID/SSOO2/Practica1-SSOO/copia");  
    }
}