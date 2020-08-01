/*
Modifique el programa prc05.c de tal manera de que además de imprimir el valor
de la variable x, imprima la dirección en memoria de esta variable (&x). Ejecute el
programa y explique la salida del mismo.
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int y = 100;


int main ()
{
	int x = 100;

	printf("Soy el proceso: %d \n",getpid());

	switch (fork())
	{
		case -1:   // No pudo crear el proceso
			printf ("Error. No se crea proceso hijo");
			break;

		case 0:   //proceso hijo
			printf ("Soy el proceso hijo, pid: %d , x = %d, &x = %p\n", getpid(), --x, &x);
			exit(5);
			break;

		default:  //proceso padre
			sleep(1);
			printf ("Soy el proceso padre, pid: %d , x = %d, &x = %p\n", getpid(), ++x, &x);
	}


  exit(0);

}


/*
Salida al ejecutar ./prc06 :

Soy el proceso: 17768
Soy el proceso hijo, pid: 17769 , x = 99, &x = 0x7ffd97059f34
Soy el proceso padre, pid: 17768 , x = 101, &x = 0x7ffd97059f34

Vemos que ambas direcciones de memorias son iguales. Esto se debe a que fork()
realiza una compia exacta del contexto del proceso padre. Eebe tenerse en cuenta
que dicha direccion no es absoluta sino realativa a cada proceso.
*/
