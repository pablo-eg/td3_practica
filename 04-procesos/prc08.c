/*
Tome el programa del Ej. 4 y fuerce a que el proceso hijo haga una espera activa
de 30 segundos con la función sleep(). El proceso padre debe terminar antes que
el proceso hijo. ¿Qué sucede con el proceso hijo?. Ejecute "pstree -p" e
identifique si persisten los procesos en cuestión. Observe los números de pid.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <sys/wait.h>
#include <unistd.h>       // Define fork, getpid y getppid


int main (){

	pid_t pid;
	int i;

	pid = fork();

	if (pid == 0) //hijo
	{
		printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);
		sleep(15);
		printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);
	}

	else //padre
	{
		printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);
	}

	exit(0);

}


/*
Vemos que el proceso hijo queda en estado "huerfano" y pasa a ser un proceso hijo del proceso
systemd(1) y no del bash
*/
