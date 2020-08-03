/*
Compile y ejecute el programa mq05.c comente todas las líneas indicando que
operación realiza cada una.
• ¿Qué sucede cuándo el programa recibe la señal SIGUSR1?.
• ¿Qué sucede cuándo el programa recibe la señal SIGINT?
• ¿Qué sucede cuándo el programa escribe más de 5 mensajes?
• Escriba un programa mq05a.c el cual si recibe una señal SIGINT lea un
mensaje, de la cola de mensajes creada por el programa mq05.c.
*/

// se incluyen librerias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <signal.h>

// se definen constantes
#define MENSAJE "DATA PARA PROCESO"
#define MQ_PATH "/MQ_TD3"

// se definen muchas variables globales
   int err, leido;
   char buff[1024];
   mqd_t mqd = 0;
   struct mq_attr attr, attr_rcv;
   struct sigevent sev;
   int retval;

// función handler de la señal SIGINT
void escribe_mensaje(int a){

   write(STDOUT_FILENO, "\nenviar mensaje\n", sizeof("\nenviar mensaje\n"));

   // escribe en la cola el contenido de MENSAJE
   err = mq_send(mqd, MENSAJE, strlen(MENSAJE)+1, 1);  //strlen nos da la longitud de una cadena
   if(err == -1){
        write(STDOUT_FILENO, "\nerror en mq_send()\n", sizeof("\nerror en mq_send()\n"));  }
   else {
        write(STDOUT_FILENO, "\nMensaje enviado\n", sizeof("\nMensaje enviado\n"));   }

}

// función handler de la señal SIGUSR1
void finaliza_proceso(int a){
   // cierra la cola
   err = mq_close(mqd);
   if (( err < 0 )){
      write(STDOUT_FILENO, "\nerror en mq_close()\n", sizeof("\nerror en mq_close()\n"));
      exit(0);   }

   write(STDOUT_FILENO, "\nCola de mensajes cerrada\n", sizeof("\nCola de mensajes cerrada\n"));
   // elimina la cola
   err = mq_unlink(MQ_PATH);
   if(err == -1){
      write(STDOUT_FILENO, "\nerror en mq_unlink()\n", sizeof("\nerror en mq_unlink()\n"));
      exit(0);  }

   write(STDOUT_FILENO, "\nCola de mensajes eliminada\n", sizeof("\nCola de mensajes eliminada\n"));

   write(STDOUT_FILENO, "\nTerminando proceso...\n", sizeof("\nTerminando proceso...\n"));

   exit(0);
}


int main() {
   // se le asigna a la señal SIGINT la función escribe_mensaje
   signal(SIGINT, escribe_mensaje);    //Ctrl + C
   // se le asigna a la señal SIGUSR1 la función finaliza_proceso
   signal(SIGUSR1, finaliza_proceso);  //termina
   // se muestra el PID del proceso
   printf("Soy el proceso: %d \n ",getpid());
   // si la cola existe, se elimina
   mq_unlink(MQ_PATH);
   // se indica que el tamaño máximo de cada mensaje será igual al tamaño de buff
   attr.mq_msgsize = sizeof(buff);
   // máxima cantidad de mensajes
   attr.mq_maxmsg = 5;

   // se abre o se crea la cola para lectura y escritura con permisos 666 y los atributos anteriormente definidos
   mqd = mq_open(MQ_PATH, O_RDWR | O_CREAT , 0666, &attr);
   if (mqd < 0) {
      printf ("error en mq_open()");
      exit(-1);  }

   printf("Cola de mensajes creada\n");

  // se muestran los atributos de la cola creada
  if (mq_getattr(mqd, &attr_rcv) == -1) {
      printf ("error en mq_getattr()");
      exit(-1); }
   printf("Nro max. de mensajes en cola de mensajes: %ld\n", attr_rcv.mq_maxmsg);
   printf("Longitud max. de mensaje: %ld\n", attr_rcv.mq_msgsize);
   printf("Nros de mensajes pendientes en cola de mensajes: %ld\n", attr_rcv.mq_curmsgs);

   // loop infinito
   while(1){


   }

   exit(0);
}
