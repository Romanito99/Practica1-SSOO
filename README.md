# Practica1-SSOO

Autor: César Braojos Corroto

Fecha: 15-Marzo-2021

**Práctica 1 –Llamadas al sistema y señales**

**COMPILACION DEL PROGRAMA:**

    $~make

Esto se encargar de ejcutar los comandos para preparar la ejecucion y lo ejecutara.
    
**LIMPIEZA CARPETA: **

    $~make clean
    
Esto se encargar de eliminar las carpetas y archivos creados en la ejecución.


Finalmente por las caracteristicas del programa he añadido una opcion para ver los deamon que se estan ejecutando en tu ordenador , y asi poder parar el daemon de mi practica 

**DAEMON:**

    $~make daemon
  
 Esto se encarga de eliminar la copia de segurida que obtenemos y de mostrar os daemon en ejcucion.
 
 Despues de esto con el comando kill podremos terminar la ejecucion de nuestro daemon. 
 Por ejemplo: 
  
    $~kill -9 3623
