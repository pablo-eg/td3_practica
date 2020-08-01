/*
Modifique el programa sig05.c del ejercicio anterior para que el manejador sea para la
señal SIGUSR1. Ejecute el programa, lea el PID del proceso y desde otra consola
ejecute,

kill -SIGUSR1 PID

¿Qué observa?.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


void manejador_senial(int a){
    write(0,"\nMe rehuso a terminar\n",sizeof("\nMe rehuso a terminar\n"));
}


int main ()
{
   signal(SIGUSR1, manejador_senial);

   printf("Proceso PID = %d\n", getpid());

   while(1);

   exit(0);
}



/*
En este caso si vemos por pantalla "Me rehuso a terminar"
*/
