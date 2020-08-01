/*
Escriba un programa sig08.c que realice las siguientes tareas:

  a. Cree un proceso hijo que haga una espera activa de dos segundos y finalice con la
  funcion exit(0).

  b. Luego de crear el proceso hijo, el padre debe ejecutar una espera activa por mas de
  10 segundos. Luego de la finalización del proceso hijo, verifique con pstree si este está
  en estado zombie.

  c. Establezca en el proceso padre un manejador para la señal SIGCHLD. En el
  manejador de esta señal se debe leer el estado de finalizacion del hijo con la función
  wait(&status). De esta forma el proceso hijo no queda en estado zombie. Además
  se debe mostrar lo devuelto por la función wait y el valor de status.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void manejador_hijo(int a);

int main ()
{
  pid_t pid;
  int exit_argumento;
  printf("Ingrese el numero de salida de exit: ");
  scanf("%d", &exit_argumento);

  pid = fork();

  if (pid == 0)
  {
    printf("\nSoy el hijo. PID: %d\n", getpid());
    sleep(5);
    exit(exit_argumento);
  }

  if (pid > 0)
  {
    signal(SIGCHLD, manejador_hijo);
    printf("\n");
  }

  sleep(10);
  fflush(NULL);
  printf("\n\nTerminando proceso padre...\n" );
  exit(0);
}

void manejador_hijo(int a){
  int status;

  wait(&status);

  printf("Eliminando hijo zombi...\n\n");

  if(WIFEXITED(status)){
    printf("status: %d\n", WEXITSTATUS(status));
  }
  else{
    printf("Error con status\n");
  }
}
