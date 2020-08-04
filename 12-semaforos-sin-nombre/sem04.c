/* Ejercicio 4 del TP de semaforos sin nombre */

/* productor-consumidor con semaforos */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUFFER          10	// Buffer
#define DATOS_A_PRODUCIR    20  // DATOS A PRODUCIR POR CADA PRODUCTOR

static int buffer[MAX_BUFFER] = {0};   // Buffer comun

pthread_t th1, th2, th3;      	// Hilos
sem_t sem_dato,sem_lugar;   // Semaforos
int pos = 0;
int dato = 0;
//---------------- PRODUCTOR ---------------------------

void Productor(void *nro) {
int i, s, numero;
int sem_val1, sem_val2;

	//pos = 0;
	//dato = 1000;                     // Producir dato
  numero= *(int*)nro;

	for(i=0; i<DATOS_A_PRODUCIR; i++) {
		s = sem_wait(&sem_lugar);            // Decrementa sem_lugar o esperar si igual a 0
		if (s != 0) {
			printf("ERROR; sem_wait() = %d\n", s);
			exit(-1);	      }

		sleep(1);

    if (dato <= DATOS_A_PRODUCIR){
      dato++;
  		buffer[pos] = dato;
  		pos = (pos + 1);
  		if (pos >= MAX_BUFFER) {
  			pos=0;   }
    }
    else{
      break;
    }


    printf("Productor %d dato: %d\n", numero, dato);

		s=sem_post(&sem_dato);      // Incrementa sem_dato
		if (s != 0) {
			printf("ERROR sem_post()\n");
			exit(-1);     }
	}

	printf("Termina Productor %d con %d datos producidos\n", numero, i);
	pthread_exit(0);

}

//---------------- CONSUMIDOR ---------------------------
void Consumidor(void){
int dato, i, pos, s;
int sem_val1, sem_val2;

	pos=0;

	for(i=0; i < DATOS_A_PRODUCIR; i++ ) {
		s=sem_wait(&sem_dato);            // Decrementa sem_dato o esperar si igual a 0
		if (s != 0) {
			printf("ERROR; sem_wait() = %d\n", s);
			exit(-1);      }

		sleep(1);

		dato = buffer[pos];
		pos = (pos + 1) ;
		if (pos>= MAX_BUFFER) {
			pos=0;   }

		s=sem_post(&sem_lugar);   // Incrementa sem_lugar
		if (s != 0) {
		 	printf("ERROR sem_post()\n");
	      	exit(-1);     }

		printf("\nConsumidor dato: %d \n\n", dato);

	}

	printf("Termina Consumidor: %d\n",i);
	pthread_exit(0);
}

//-------------------------------------------------------

int main() {

int s, t;
int produc[2] = {1,2};
	printf("Se crean semaforos\n");

//------ Crear semaforos

	s=sem_init(&sem_lugar, 0, MAX_BUFFER);
	if (s != 0) {
		printf("ERROR sem_init()\n");
		exit(-1);     }

	s=sem_init(&sem_dato, 0, 0);
	if (s != 0) {
		printf("ERROR sem_init()\n");
		exit(-1);     }

//------ Crear hilos

	printf("Se crean hilos\n");
  pthread_create(&th1, NULL, (void *)&Productor, (void *)&produc[0]);
	pthread_create(&th3, NULL, (void *)&Productor, (void *)&produc[1]);
	pthread_create(&th2, NULL, (void *)&Consumidor, NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
  pthread_join(th3, NULL);

	s=sem_destroy(&sem_dato);
	if (s != 0) {
		printf("ERROR sem_unlink()\n");
		exit(-1);  }

	s=sem_destroy(&sem_lugar);
	if (s != 0) {
		printf("ERROR sem_unlink()\n");
		exit(-1);  }

	printf("Termina main() \n");

	pthread_exit(0);
}

//------------------------------------------------------------//

/*
El programa sem04.c implementa el problema del productor-consumidor.
- Abra el programa con un editor y observe cómo está implementado el uso de
semáforos para resolver este problema.
- Agregue otro hilo Productor. ¿Qué solución propone para evitar problemas de
concurrencias?. Modifique el código y verifique la solución propuesta.
*/
