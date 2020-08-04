/*
 * Ejercicio 4 del TP Hilos
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int suma=0;

void *hilo1 (void * nro)
{
   int numero, temp;

   numero = *(int*)nro;
   temp = suma;
   //usleep(300);
   pthread_yield();
   temp = temp + 1 ;
   suma = temp;

   printf("Ejecutando hilo %d\n", numero);
   pthread_exit(NULL);
}

int main()
{
   pthread_t hilo[100];
   int rc, t, arre[100];

   for(t=0; t< 100 ; t++){
      printf("Creando el hilo %d\n", t);
      arre[t] = t;
      rc = pthread_create(&hilo[t], NULL, hilo1 , (void *)(&arre[t]) );
      if (rc){
         printf("ERROR; pthread_create() = %d\n", rc);
         exit(-1);
      }
   }

   int i;
   for (i=0; i<100;i++) {
       while(pthread_join(hilo[i], NULL));
   }

   printf("Valor de globlal = %d\n", suma);

   exit(0);
}

/*
Abra en un editor el programar hilos04.c. ¿Cuál es el propósito del programa?.
Compile el programa y ejecútelo varias veces. ¿Con qué valor finaliza la variable
global suma?
El proposito es crear 100 hilos y que cada hilo sume una unidad a la variable suma y termine.
El valor de suma termina la mayoria de las veces en 100, pero aveces termina en 99 o 98.

- Ahora, descomente la línea 18 y vuelva a compilar. Ejecute varias veces el
programa. ¿Con qué valor finaliza la variable global suma? ¿Presenta el mismo
valor que en caso anterior? Si se observan cambios, ¿a qué se deben?.
Termina con valores muy distintos que van aproximadamente de 10 a 30. Esto se debe a que el planificador le saca el uso de la CPU a los hilos en medio de una zona crítica, es decir, justo en el momento en que se hace la modicación de la variable compartida entre los procesos.

- Realice la misma operación que en el punto anterior comentando la línea 18 y
descomentando la línea 19.
En este caso obtemos valores que van de 35 a 95. Otra vez no obtemos el valor esperado, ya que los hilos seden la CPU en medio de una zona crítica-

Estos problemas los podemos solucionar con mutex o semáforos.
*/
