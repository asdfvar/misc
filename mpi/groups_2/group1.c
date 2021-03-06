#include <mpi.h>
#include <stdio.h>
#include "group_tags.h"

int main(int argc, char **argv) 
{ 
   MPI_Comm   myComm;       /* intra-communicator of local sub-group */ 
   MPI_Comm   myFirstComm;  /* inter-communicator */ 
   int group_number = 1; 
   int rank; 


   MPI_Init(&argc, &argv); 
   MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
printf("%s:%d:rank %d\n", __FILE__, __LINE__, rank);

   /* Build intra-communicator for local sub-group */ 
   MPI_Comm_split(MPI_COMM_WORLD, group_number, rank, &myComm); 


   /* Build inter-communicators.  Tags are hard-coded. */ 
   /* Group 1 communicates with group 0 */ 
   MPI_Intercomm_create( myComm, 0, MPI_COMM_WORLD, 0, 1, &myFirstComm); 


   /* Do work ... */ 
   float numbers[3] = {10, 12, 13};
   MPI_Send( numbers, 3, MPI_FLOAT, 0, TAG_0, myFirstComm );

   printf("%s: hello\n", __FILE__);

   // close down stuff
   MPI_Comm_free(&myFirstComm); 
   MPI_Finalize(); 

   return 0;
} 
