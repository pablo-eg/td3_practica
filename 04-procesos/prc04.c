/*
La función fork() devuelve el pid del proceso hijo cuando lo ejecuta el padre; y
devuelve 0 (cero) cuando lo ejecuta el proceso hijo. ¿Qué estructura de bifurcación
de C le parece más conveniente para implementar que padre e hijo ejecuten
diferente código (if, while, for, case)? Modifique prc02.c con la estructura de
bifurcación seleccionada. Compile y ejecute el programa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i;

	pid = fork();

  if( pid == 0 )
  {
    printf("Soy el hijo con PID = %d\n", getpid());
  }
  else
  {
    printf("Soy el padre con PID = %d\n", getpid());
  }

	// Ejecute pstree en otra consola
	sleep(30);

	exit(0);
}
