/*Escriba un programa seg04.c que cree tres procesos hijos que ejecuten un bucle
infinito. Luego de una espera activa, el proceso padre debe finalizar cada uno de los
procesos enviando a cada uno de ellos la señal SIGKILL. Para ello utilice la función
kill().*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define CantHijos 3

int main ()
{
  pid_t pid[3];
  int i;

  for( i=0; i<CantHijos; i++ )
  {
    pid[i] = fork();

    if( pid[i] == 0 ) //hijo
    {
      while(1);
    }
  }

  printf("Los PIDs de mis hijos son:\n");

  for( i=0; i<CantHijos; i++ )
  {
  printf("PID%d: %d\n", i+1, pid[i]);
  }

  printf("\nSoy el proceso Padre y cada 5 segundo mataré a uno de mis hijos.\n\n");

  for( i=0; i<CantHijos; i++ )
  {
    sleep(5);
    kill(pid[i], SIGKILL);
    printf("Maté a mi hijo %d\n", pid[i]);
  }

  exit(0);
}
