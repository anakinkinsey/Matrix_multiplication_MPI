#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "MyMPI.h"

int main(int argc, char** argv) {
	
	int rank,size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int m,n;
	int opt;
	char* in;
	double **A, *Astorage;

	
	if(argc < 3)
    	{
		if(rank == 0)
		{
			printf("Incorrect Input \nCorrect Usage: ");
			printf("mpirun -np ## ./demo -i file_name\n");
		}
		MPI_Finalize();
		exit(0);
    	}
	else
	{
		while((opt = getopt(argc, argv, "i:")) != -1)
		{
			switch(opt)
			{
				case'i':
					in = optarg;
				break;
				case '?':
					if (rank == 0)
					{
						printf("Incorrect Input \nCorrect Usage: ");
						printf("mpirun -np ## ./demo -i file_name\n");
					}
					MPI_Finalize();
					exit(0);
				break;
			}
		}
	}
	
	read_row_striped_matrix(in, (void***)&A, (void**)&Astorage, MPI_DOUBLE, &m, &n, MPI_COMM_WORLD);

	print_row_striped_matrix((void**)A, MPI_DOUBLE, m,n, MPI_COMM_WORLD);
	
	
	
    MPI_Finalize();
	return 0;
}
