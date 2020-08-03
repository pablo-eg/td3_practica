/*
Compile y ejecute el programa mq02.c. ¿Cuál es el objetivo del programa?. ¿Qué
problema observa en el programa?. Puede terminar el programa enviándole la
señal SIGUSR1.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <signal.h>

#define MENSAJE "DATA PARA PROCESO"
#define MQ_PATH "/MQ_TD30"

int err, leido;
char buff[1024];
mqd_t mqd;
struct mq_attr attr, attr_rcv;

void sig_user1(int a){

   err = mq_close(mqd);
   if (( err < 0 )){
      write(STDOUT_FILENO, "\nerror en mq_close()\n", sizeof("\nerror en mq_close()\n"));
      exit(-1);   }

   write(STDOUT_FILENO, "\nCola de mensajes cerrada\n", sizeof("\nCola de mensajes cerrada\n"));


   err = mq_unlink(MQ_PATH);
   if(err == -1){
        write(STDOUT_FILENO, ")\nerror en mq_unlink())\n", sizeof(")\nerror en mq_unlink())\n"));
      exit(-1);    }

   write(STDOUT_FILENO, ")\nCola de mensajes eliminada\n", sizeof(")\nCola de mensajes eliminada\n"));

   write(STDOUT_FILENO, "\nTerminando proceso...\n", sizeof("\nTerminando proceso...\n"));

   exit(0);
}

int main() {

   signal(SIGUSR1, sig_user1);

   printf ("Mi pid es %d\n", getpid());


   attr.mq_msgsize = sizeof(buff);
   attr.mq_maxmsg = 5;

   mqd = mq_open(MQ_PATH, O_RDWR | O_CREAT, 0666, &attr);
   if (mqd < 0)
   {
      printf ("error en mq_open()\n");
      exit(-1);
    }

   printf("Cola de mensajes creada\n");

   while(1) {

      err = mq_send(mqd, MENSAJE, strlen(MENSAJE)+1, 1);  //strlen nos da la longitud de una cadena
      if(err == -1){
         printf ("error en mq_send()");
         exit(-1);}

      printf("Mensaje enviado (%d)\n", err);

      sleep(1);

   }


   exit(0);
}


/*
El problema del programa es que intenta enviar un mensaje por la cola, pero se abre como solo lectura.
Esto se puede solucionar reemplazando la linea 57 por:

mqd = mq_open(MQ_PATH, O_RDWR | O_CREAT, 0666, &attr);
*/
