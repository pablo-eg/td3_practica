/*
Compile y ejecute pipe03.c. Comente todas las líneas indicando que operación
realiza cada una. ¿Qué problema observa en el programa? ¿Qué solución
propone?
*/

// se incluyen librerias
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>

// se definen constantes
#define FRASE_A "INFORMACION IMPORTANTE"
#define FRASE_B "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

// se define un manejador para la señal SIGPIPE
void pipe_sign_handler(int a){

   write (STDOUT_FILENO, "\n Problema con pipeline.\n ", sizeof("\n Problema con pipeline.\n"));
}

int main (){
   // se definen variables
   int ipc[2], proc;
   int leido, success;
   char buff[BUFF_SIZE] = {0};

   // se asigna a la señal SIGPIPE un manejador pipe_sign_handler
   signal(SIGPIPE, pipe_sign_handler);

   // se crea la tuberia ipc
   pipe(ipc);

   // se crea un proceso hijo
   switch (fork()){

      // hijo
      case 0:
      // se cierra el extremo de lectura
      close(ipc[0]);
      // se copia el string FRASE_A en el buffer
      strncpy(buff, FRASE_A, sizeof(FRASE_A));
      // se escribe el buffer en la tuberia
      write(ipc[1], buff, sizeof(FRASE_A));
      // termina el hijo
      exit(0);
      break;

      // padre
      default:
      // crea otro hijo
      switch (fork()){

         case 0:
            // idem hijo anterior
            close(ipc[0]);
            strncpy(buff, FRASE_B, sizeof(FRASE_B));
            write(ipc[1], buff,    sizeof(FRASE_B));
            exit(0);
         break;
         // padre
         default:
            // se cierra el extremo de escritura
            close(ipc[1]);
            int i;
            for(i=0; i<2; i++){
               // se lee lo escrito por los hijos y se muestra por pantalla
               leido = read(ipc[0], buff, sizeof(buff));
               if(leido < 1){
                  write (STDOUT_FILENO, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
               }else {
                  write (STDOUT_FILENO, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
                  write (STDOUT_FILENO, buff, leido-1);
                  printf(", por el proceso padre, pid %d \n", getpid());
               }
            }

            close(ipc[0]);
            wait(NULL);
            wait(NULL);
            exit(0);
         break;
      }
   }
}



/*
El problema que se observa es que el proceso padre, al leer de la tuberia, no puede diferencia a que hijo corresponde el string de bytes.

Se puede solucionar usando una tuberia para cada hijo.
*/
