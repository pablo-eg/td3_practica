/*
Tome proc02.c y ponga las funciones de las líneas 14 y 15 dentro de un bucle que
se repita 3 veces. Imprima también el valor de la variable de control del bucle
(variable i). Analice y deduzca cuántos hijos son creados. Justifique su respuesta.
¿Qué sucede con el valor de i?
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i;

	for (i = 0; i < 3; ++i)
	{
		pid = fork();
		printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\nvariable i = %d\n\n", getpid(), getppid(), pid, i);
	}

	// Ejecute pstree en otra consola
	sleep(30);

	exit(EXIT_SUCCESS);
}


/*
Lo que sucede es lo siguiente:

|-gnome-terminal-(14274)-+-bash(14283)---prc07(17975)-+-prc07(17976)-+-prc07(17977)---prc07(17982
                                                     |              `-prc07(17979)
                                                     |-prc07(17978)---prc07(17981)
                                                     `-prc07(17980)

Donde el proceso con PID = 17975 es el padre.
Vemos que el padre en total crea 3 hijos. El primer hijo crea, a su vez, 2 hijos y el primer hijo de este crea otro
hijo.

Esto se debe a que a medida que se van creando los hijos la variable del bucle de control "i" se va heredando con su
valor actual.
*/
