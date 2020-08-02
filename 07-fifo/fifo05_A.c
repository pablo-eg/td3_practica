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

#define MENSAJE "Mensaje top Secret para proceso B"
#define FIFO_PATH "/tmp/MI_FIFO"

int main(){
  int fifo_d, err;

  unlink(FIFO_PATH);

  printf("Creando FIFO...\n");
  err = mkfifo(FIFO_PATH, 0777);
  if(err == -1)
  {
     printf("Error, la FIFO ya existe.\n");
  }
  else
  {
     printf("Creada correctamente...ejecute el proceso lector en otra terminal\n");
  }

  fifo_d = open(FIFO_PATH, O_WRONLY, 0);
  if(fifo_d < 1)
  {
    printf("Error al abrir la FIFO...terminando\n");
    exit(-1);
  }

  write(fifo_d, MENSAJE, sizeof(MENSAJE));

  printf("Mensaje escrito en la FIFO\n");

  close(fifo_d);
  exit(0);
}
