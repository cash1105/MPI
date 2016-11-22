#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define  MASTER 0

int main (int argc, char *argv[])
{
int   numtasks, taskid, len, claimed, provided;
   
char hostname[MPI_MAX_PROCESSOR_NAME];

MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);

MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
   
MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
   
MPI_Query_thread(&claimed);
   
MPI_Get_processor_name(hostname, &len);
   
printf ("Hello from task %d on %s!\n", taskid, hostname);
printf("Query thred level= %d Init_thread level= %d\n Rank: %d\n Number of Process: %d\n", claimed,  provided, taskid, numtasks);
if (taskid == MASTER)
   printf("I'm the Master : Number of MPI tasks is: %d\n",numtasks);
if(taskid%2 == 0)
   printf("Procesador:%s", hostname );
MPI_Finalize();
