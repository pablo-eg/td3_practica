/*
 * Ejercicio 2 del TP Hilos
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int t = 0 ;
int arre[5]={0};

void *hola(void * nro) {
   sleep(2);
   printf("Hola, soy el hilo %d\n", * (int*) nro);
   pthread_exit(NULL);
}

int main() {
pthread_t hilo[5];
int rc;

  for(t=0; t < 5 ; t++){

     printf("Main creando el hilo nro %d\n", t);
     arre[t] = t;

     //rc = pthread_create(&hilo[t], NULL, hola , (void *)(&t)  );
     rc = pthread_create(&hilo[t], NULL, hola , (void *) (&arre[t]) );
     //sleep(2);
     if (rc != 0){
         printf("ERROR; pthread_create() = %d\n", rc);
         exit(-1);        }
   }

   pthread_exit(NULL);

   printf("Esto no aparece!!!\n");

}

/*
Compile y ejecute el programa hilos02.c.

- Analice el código. ¿Qué se debería ver por consola y qué es lo que se observa?
Por consola no siempre vemos la misma salida, ya que primero se crean los 5 hilos y luego hacen una espera activa por 2 segundos. Cuando la espera finaliza, los hilos se ejecutan según el orden que elija el planificador.
Si en cambio, la espera la hacemos luego de crear cada hilo (descoementar linea 31 y comentar 15), la salida siempre será la misma.

- ¿Por qué no se ejecutará el printf de la línea 39?
Porque el main, que es un hilo más, termina en la lina 37.

- Descomente la línea 30 y comente la 29 y vuelva a compilar. ¿Qué observa por
consola? ¿Por qué se ha modificado el comportamiento del programa?
Se observa los siguiente:

Main creando el hilo nro 0
Main creando el hilo nro 1
Main creando el hilo nro 2
Main creando el hilo nro 3
Main creando el hilo nro 4
Hola, soy el hilo 5
Hola, soy el hilo 5
Hola, soy el hilo 5
Hola, soy el hilo 5
Hola, soy el hilo 5

Vemos que el valor que se muestra es siempre 5. Esto se debe a que el argumento del hilo se pasa por referencia y al hacer una espera de 2 segundos antes de mostrar el valor de t por pantalla, el for del main termina y por lo tanto t = 5. Si comentamos la linea 15, veriamos algo como lo que se muestra a continuación, pero la salida dependerá de la corrida.

Main creando el hilo nro 0
Main creando el hilo nro 1
Hola, soy el hilo 1
Main creando el hilo nro 2
Main creando el hilo nro 3
Hola, soy el hilo 3
Hola, soy el hilo 3
Main creando el hilo nro 4
Hola, soy el hilo 4
Hola, soy el hilo 5
*/
