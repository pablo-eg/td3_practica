/* Ejercicio 2 del TP de semaforos sin nombre */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

//------- variables globales

int t, total, contador, s;
sem_t sem;

//------------------------------------------------------------

void *HILO(void *nro){
int local, j, numero;

	numero = *(int*)nro;

  s = sem_wait(&sem);
	for(j=0; j < contador; j++){
		local = total;
		local = local + 10;
		total = local;	   }
  //s = sem_post(&sem);
	printf("Hilo %d, total = %d\n", numero,total);
  s = sem_post(&sem);

	pthread_exit(NULL);
}

//------------------------------------------------------------

int main()	{
int rc, n_hilos;
int arre[10];

	total = 0;
	contador = 100000;
	n_hilos = 10;

	pthread_t hilo[n_hilos];

  // se inicializa el semáforo sem
  s=sem_init(&sem, 0, 1);
  if (s != 0) {
    printf("ERROR sem_init()\n");
    exit(-1);     }

	for(t=0; t < n_hilos; t++){

		arre[t] = t;

		rc = pthread_create(&hilo[t], NULL, HILO , (void *)&arre[t]  );
		if (rc){
			printf("ERROR; pthread_create() = %d\n", rc);
			exit(-1);      }
	}

//-------------------------------------

	for(t=0; t < n_hilos; t++){
		pthread_join(hilo[t],NULL);
	}

	printf("total = %d\n",total);

	pthread_exit(NULL);
}

/*
Analice, compile y ejecute el programa sem02.c ¿Cuál es el objetivo del
programa?. Observe la salida por consola.
El objetivo del programa el crear 10 hilos y que cada hilo incremente la variable compartida total, 100 veces (incrementos de 10 en un loop de 10).

- ¿Qué valor debería tener la variable total al finalizar el programa?
100 * 10 = 1000

- Cambien el valor de inicialización de la variable contador de 10 a 100000 y
ejecute varias veces el programa. ¿Qué valor debería tener la variable total al
finalizar el programa?. ¿Qué problema observa?
Ahora total debería tener un valor final de 10 * 100.000 * 10 = 10.000.000, pero obtenemos siempre un valor menor.

- Implemente semáforos para solucionar el problema.
*/
