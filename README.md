# Practica1-SSOO

Autor: César Braojos Corroto

Fecha: 15-Marzo-2021

**Práctica 1 –Llamadas al sistema y señales**

**COMPILACION DEL PROGRAMA: make** 

Ejecutara los siguientes comandos.

    mkdir estudiantes CopiaDeSeguridad exec
    gcc -lpthread -lrt src/Manager.c -o exec/Manager
    gcc  src/Pa.c -o exec/Pa
    gcc  src/Pb.c -o exec/Pb
    gcc  src/Pc.c -o exec/Pc
    gcc  src/Pd.c -o exec/Pd
    gcc  src/daemon.c -o exec/daemon
    ./exec/Manager
    
**LIMPIEZA CARPETA: make clean**

Ejecutara los siguientes comandos.

    rm -rf estudiantes
    rm -rf exec/
    rm Log.txt

Finalmente por las caracteristicas del programa he añadido una opcion para ver los deamon que se estan ejecutando en tu ordenador , y asi poder parar el daemon de mi practica 

**DAEMON: make daemon**
  
Ejecutara el siguiente comando.

    rm -rf CopiaDeSeguridad
    ps -e | grep daemon
  
Despues de esto con el comando kill podremos terminar la ejecucion de nuestro daemon. 
Por ejemplo: 
  
    kill -9 3623
