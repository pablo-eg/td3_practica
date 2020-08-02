/*
Cree dos procesos no relacionados (que no sean padre e hijo) que se comuniquen
usando una memoria FIFO, de la siguiente forma:
- El proceso A crea y abre la FIFO para escribir, y escribe el mensaje “Mensaje
para proceso B” y termina.
- El proceso B abre la FIFO para leer, y lee el mensaje y lo muestra.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_PATH "/tmp/MI_FIFO"

int main(){
  int fifo_d;
  char mensaje[100];
  int err;

  printf("Abriendo FIFO...");
  fifo_d = open(FIFO_PATH, O_RDONLY, 0);
  if(fifo_d < 0)
  {
    printf("Error al abrir la FIFO...terminando\n");
    exit(-1);
  }

  printf("abierta\n\n");
  err = read (fifo_d, mensaje, sizeof(mensaje));
  if(err<0){
    printf("Error al leer la FIFO...terminando\n");
    exit(-1);
  }

  printf("Recibí de FIFO: %s\n\nEliminando FIFO...\n", mensaje);

  unlink(FIFO_PATH);

  exit(0);
}
