/*
 * Ejercicio 3 del TP Hilos
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t hilo[2];

void * hilo0()
{
  pthread_detach(pthread_self());
  printf ("Yo soy el hilo 0 \n");
  sleep(2);
  pthread_exit (NULL);
}

void * hilo1()
{
  printf ("Yo soy el hilo 1 \n");
  printf("Esperando al hilo %lx \n", hilo[0]);

  pthread_join(hilo[0],NULL);
  printf("Terminando hilo 1 \n");
  pthread_exit (NULL);
}

int main()
{
  int rc;

  //Crear hilo 0
  rc = pthread_create (&hilo[0], NULL, hilo0, NULL);
  if (rc)
    {
      printf ("ERROR; pthread_create() = %d\n", rc);
      exit (-1);
    }
  printf ("El main creando el hilo hola0, nro %lx\n",hilo[0]);

  //Crear hilo 1
  rc = pthread_create (&hilo[1], NULL, hilo1, NULL);
  if (rc)
    {
      printf ("ERROR; pthread_create() = %d\n", rc);
      exit (-1);
    }
  printf ("El main creando el hilo hola1, nro %lx\n",hilo[1]);

  pthread_join(hilo[1],NULL);
  printf ("Se ejecutaron todos los hilos\n");

  //pthread_exit(NULL);
  exit(0);
}

/*
Compile y ejecute el programa hilos03.c ¿Cuál es el objetivo del programa?.
Observe la salida por consola.
Aparte del main se crean 2 hilos, el main espera que termines el hilo1 y este espera a que termine el hilo0,

- Ahora, descomente la línea 14 y vuelva a compilar. ¿Qué observa por consola?
¿Por qué se ha modificado el comportamiento del programa?
Vemos que el hilo1 ya no espera al hilo0 ya que con pthread_detach(pthread_self()) se libera el hilo0.

- Ahora, comente la línea 55 y descomente la línea 56 y vuelva a compilar. Qué
observa por consola? ¿Por qué se ha modificado el comportamiento del programa?
El proceso termina sin esperar que termine el hilo0. Esto se debe a que la llamada a exit() hace que todos los hilos del proceso terminen.
*/
