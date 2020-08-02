/*
Compile y ejecute fifo02.c. Comente todas las líneas indicando qué operación
realiza cada una. ¿Qué problema observa en el programa? ¿Qué solución
propone?
*/

// se incluyen librerias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include<sys/wait.h>

// se definen constantes
#define MENSAJE "HOLA PROCESO HIJO"
#define FIFO_PATH "/tmp/MI_FIFO"

int main(){
   // se definen variables
   int err, fifo_d;
   char buff[80];
   int leido;

   // si la FIFO existe la borro
   unlink(FIFO_PATH);

   // FIFO puede ser leida, escrita y ejecutada por:
   err = mkfifo(FIFO_PATH, 0777); // el resto de los usuarios del sistema.
   if(err == -1) {
      write(STDOUT_FILENO, "\nError al crear FIFO, la FIFO ya existe", sizeof("\nError al crear FIFO, la FIFO ya existe"));
   }else {
      write(STDOUT_FILENO, "\nFIFO creado correctamente\n", sizeof("\nFIFO creado correctamente\n"));
   }

   // se crea un proceso hijo
   switch (fork()){

      case -1:
         write(STDOUT_FILENO, "\nError al crear hijo", sizeof("\nError al crear hijo"));
         return -1;
      break;

      // hijo
      case 0:

         write(STDOUT_FILENO, "\nEntrando proceso HIJO", sizeof("\nEntrando proceso HIJO"));

         sleep(5);

         // se abre la FIFO solo para lectura
         fifo_d = open(FIFO_PATH, O_RDONLY, 0);
         if(fifo_d == -1){
            write(STDOUT_FILENO, "\nHIJO: Error al abrir FIFO ", sizeof("\nHIJO: Error al abrir FIFO "));
            return -1;
         }else {
            write(STDOUT_FILENO, "\nHIJO: FIFO abierto correctamente", sizeof("\nHIJO: FIFO abierto correctamente"));
         }

         // Se lee FIFO
         leido = read(fifo_d, buff, sizeof(buff));
         if(leido == -1){
            write(STDOUT_FILENO, "\nHIJO: Error al leer en FIFO", sizeof("\nHIJO: Error al leer en FIFO"));
         }else {
            write(STDOUT_FILENO, "\nHIJO: Leido del FIFO: ", sizeof("\nHIJO: Leido del FIFO: "));
            write(STDOUT_FILENO, buff, leido-1);
            write(STDOUT_FILENO, "\n", sizeof("\n"));
         }

         // se cierra la FIFO
         close(fifo_d);

         write(STDOUT_FILENO, "\nSaliendo proceso HIJO\n", sizeof("\nSaliendo proceso HIJO\n"));
         exit(0);
      break;

      default:
         write(STDOUT_FILENO, "\nEntrando proceso PADRE", sizeof("\nEntrando proceso PADRE"));

         /*
         //El padre que debe hacer con la FIFO ?
         */

         /*
         //fifo_d = open(FIFO_PATH, O_WRONLY  | O_NONBLOCK, 0);
         fifo_d = open(FIFO_PATH, O_WRONLY, 0);
         if(fifo_d == -1){
            write(STDOUT_FILENO, "\nPADRE: Error al abrir FIFO ", sizeof("\nPADRE: Error al abrir FIFO "));
            return -1;
         }else {
            write(STDOUT_FILENO, "\nPADRE: FIFO abierto correctamente", sizeof("\nPADRE: FIFO abierto correctamente"));
         }

         // Se escribe en el FIFO
         err = write(fifo_d, MENSAJE, sizeof(MENSAJE));
         if(err == -1) {
            write(STDOUT_FILENO, "\nPADRE: Error al escribir en FIFO", sizeof("\nPADRE: Error al escribir en FIFO"));
         } else {
            write(STDOUT_FILENO, "\nPADRE: Escritos MENSAJE en FIFO", sizeof("\nPADRE: Escritos MENSAJE en FIFO"));
         }
         */

         wait(NULL);
         write (0, "\nSaliendo proceso PADRE\n", sizeof("\nSaliendo proceso PADRE\n"));

         break;
   }

   //Eliminación FIFO
   //if (unlink(FIFO_PATH) < 0) {
    //   printf("\nNo se puede borrar FIFO.\n"); }

   exit(0);
}


/*
El problema que se observa es que el hijo trata de leer en una FIFO en la que nadie escribe. Para escribir desde el proceso padre descomentar lineas 86 y 103.
*/
