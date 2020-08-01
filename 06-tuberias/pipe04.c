/*
Compile y ejecute pipe04.c. Comente todas las líneas indicando que operación
realiza cada una. ¿Qué problema observa en el programa? ¿Qué solución
propone? Ejecute echo $? para evaluar si el programa terminó bien o con
problemas
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
#define DATA "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

// se define un manejador para la señal SIGPIPE
void pipe_sign_handler(int a){

   write (STDOUT_FILENO, "\n Problema con pipeline.\n ", sizeof("\n Problema con pipeline.\n"));
   exit(-1);
}

int main (){
   // se definen variables
   int ipc[2], proc;
   int leido, success;
   char buff[BUFF_SIZE] = {0};

   // se asigna a la señal SIGPIPE un manejador pipe_sign_handler
   signal(SIGPIPE, pipe_sign_handler);

   // se crea la tuberia ipc y se pregunta si se creó con éxito
   if (pipe(ipc) == -1)
      exit(-1);

   // se cierra la lectura
   close(ipc[0]);

   // se crea un proceso hijo
   switch (fork()){

      // hijo
      case 0:
         // se cierra la escritura, se intenta leer, en caso de exito se muestra por pantalla
         close(ipc[1]);
         printf("Leyendo tuberia... \n");
         leido = read(ipc[0], buff, sizeof(buff));
         if(leido < 1){
            write(STDOUT_FILENO, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
         }else {
            write(STDOUT_FILENO, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
            write(STDOUT_FILENO, buff, leido-1);
            printf(", por el proceso hijo, pid %d \n", getpid());
         }
         exit(0);

      // padre
      default:
         // se intenta escribir en la tuberia
         //close(ipc[0]);
         strncpy(buff, DATA, sizeof(DATA));
         write(ipc[1], buff, sizeof(DATA));

         wait(NULL);

         exit(0);
   }
}


/*
Al ejecutar echo $? devuelve 255. Vemos que el programa trermina mal. Esto es debido a que se cierra la lectura antes de crea el hijo.

Para solucionar esto se debe cerrar la lectura en el padre, luego de crear el hijo. Es decir, comentar linea 42 y descomentar linea 65. 
*/
