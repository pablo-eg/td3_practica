/*
Realice un programa mq03.c el cual lea mensajes de la cola de mensajes creada
por mq02.c. Ejecutar ambos programas en dos consolas al mismo tiempo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <signal.h>

#define MQ_PATH "/MQ_TD30"

mqd_t mqd;

void sig_user1(int a){
  int err;

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

   int leido;
   char buff[1024];
   mqd_t mqd;
   struct mq_attr attr, attr_rcv;

   signal(SIGUSR1, sig_user1);

   printf ("Mi pid es %d\n", getpid());

   mqd = mq_open(MQ_PATH, O_RDONLY, 0666, &attr);
   if (mqd < 0)
   {
      printf ("error en mq_open()\n");
      exit(-1);
   }

   printf("Cola de mensajes creada\n");

   if (mq_getattr(mqd, &attr_rcv) == -1){
      printf ("error en mq_getattr()");
      exit(-1); }

   printf("Nro max. de mensajes en cola de mensajes: %ld\n", attr_rcv.mq_maxmsg);
   printf("Longitud max. de mensaje: %ld\n", attr_rcv.mq_msgsize);
   printf("Nros de mensajes pendientes en cola de mensajes: %ld\n", attr_rcv.mq_curmsgs);

   while(1){

      leido = 0;
      leido = mq_receive(mqd, buff, attr.mq_msgsize, 0);
      if (( leido < 0 )){
         printf ("error en mq_receive()");
         exit(-1); }

      printf("Mensaje leido: %s\n", buff);

   }

   exit(0);
}
