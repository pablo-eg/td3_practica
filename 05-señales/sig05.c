/*
Escriba un programa sig05.c que imprima su PID y ejecute un bucle infinito. Además,
programe un manejador para la señal SIGKILL que imprima el texto “me rehuso a
terminar” cada vez que reciba dicha señal:
write(STDOUT_FILENO,"\nMe rehuso a terminar\n",sizeof("\nMe rehuso a
terminar\n"));

Ejecute el programa, lea el PID del proceso y desde otra consola ejecute,

kill -SIGKILL PID

¿Qué sucede?
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
   signal(SIGKILL, manejador_senial);

   printf("Proceso PID = %d\n", getpid());

   while(1);

   exit(0);
}

/*
El programa termina, ya que tanto la señal SIGKILL como SIGSTOP no pueden ser manejadas
*/
