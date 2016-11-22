#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MASTER 0
int main(int argc, char **argv) {
	int my_rank, p, tag = 1;
	char or_msg[20];
	char or_buf[100];
	char de_msg[100];
	char de_buf[20];
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	if (my_rank == MASTER) {
		strcpy(or_msg, "1");
		// Implementacion protegida de deadlock
	        MPI_Sendrecv(or_msg,strlen(or_msg) + 1, MPI_CHAR, 1, tag,or_buf, 20, MPI_CHAR, 1, tag, MPI_COMM_WORLD,&status);
		// Implementacion basica
		//MPI_Send(or_msg, strlen(or_msg) + 1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
		printf("El mensaje %s ha sido enviado\n",or_msg);
		//MPI_Recv(or_buf, 20, MPI_CHAR, 1, tag, MPI_COMM_WORLD, &status);
		printf("El mensaje modificado es: %s\n",or_buf);
	} else if (my_rank == 1) {
		MPI_Recv(de_buf, 20, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
		strcpy(de_msg,de_buf);
		printf("El mensaje %s ha sido recibido\n",de_msg);
		strcat(de_msg,",2");
		//printf("El mensaje modificado es: %s\n",de_msg);
		MPI_Send(de_msg, strlen(de_msg) + 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
