
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  int limite = 10;
  int rank;
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (size != 2) {
    fprintf(stderr, "World size must be two for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int count = 0;
  int rank_2 = (rank + 1) % 2;
  while (count < limite) {
    if (rank == count % 2) {
      ////////77
      count++;
      MPI_Send(&count, 1, MPI_INT, rank_2, 0, MPI_COMM_WORLD);
      printf("%d contador se incrementa %d a %d\n",rank, count, rank);
    } 
    else {
      MPI_Recv(&count, 1, MPI_INT, rank_2, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      printf("%d se recibe el contador %d de %d\n",rank, count, rank_2);
    }
  }
  MPI_Finalize();
}
