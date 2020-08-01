/*
Compile y ejecute pipe02.c. Comente todas las líneas indicando que operación
realiza cada una. ¿Qué problema observa en el programa? ¿Qué solución
propone?
*/

// se incluyen librerias
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

// se definen constantes
#define DATA "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

int main (){
   // se definen variables
   int ipc[2], proc;
   int leido, success;
   char buff[BUFF_SIZE] = {0};

   // se crea la tuberia ipc y se pregunta si se creó con éxito
   if (pipe(ipc) == -1)
      exit(-1);

   // se crea un proceso hijo y por lo tanto se duplican los extremos de lectura y escritura
   switch (fork()){

      // hijo
      case 0:
         // se cierra el extremo de escritura
         close(ipc[1]);
         // se copia el string DATA en el buffer
         strncpy(buff, DATA, sizeof(DATA));
         // se intenta escribir en la tuberia, como se encuentra cerrada termina con error
         write(ipc[1], buff, sizeof(DATA));
         // termina
         exit(0);

      // padre
      default:
         printf("Leyendo tuberia... \n");
         // intenta leer la tuberia, pero como el hijo no escribió nada, se bloquea
         leido = read(ipc[0], buff, sizeof(buff));
         // si ocurrió un error lo escribe en STDOUT_FILENO
         if(leido < 1){
            write (STDOUT_FILENO, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
         }else {
          // si puedo leer lo guarda en STDOUT_FILENO y luego lo muestra por pantalla
            write (STDOUT_FILENO, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
            write (STDOUT_FILENO, buff, leido-1);
            printf(", por el proceso padre, pid %d \n", getpid());
         }
         wait(NULL);

         exit(0);
   }
}
