/*
	Cory Rothenberger & Anakin Kinsey
	CSCI 473
	Team Project 
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"
#include "MyMPI.h"

int main(int argc, char **argv)
{
	int rank,size;
	int opt = 0, An, Am, Bn, Bm, numRows, numElements, i, r_partner, l_partner, currentRow;
	char *inFile1, *inFile2, *outFile;
	double **A, *Astorage;
	double **B, *Bstorage;
	double *local_rows;
	MPI_Status status;


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	 if(argc < 7)
    	{
		if (rank == 0)
		{
			printf("The proper usage is 'mpirun -np <int> ./mm-parallel -A inputFile1 -B inputFile2 -C outputFile\n");
		}
		MPI_Finalize();
		exit(0);
    	}
	while((opt = getopt(argc, argv, "A:B:C:")) != -1)
	{
		switch(opt)
		{
			case 'A':
		            	inFile1 = optarg;
		            break;
			case 'B':
		            	inFile2 = optarg;
		            break;
			case 'C':
		            	outFile = optarg;
		            break;
			case '?':
				if (rank == 0)
				{
					printf("The proper usage is 'mpirun -np <int> ./mm-parallel -A inputFile1 -B inputFile2 -C outputFile\n");
				}
				MPI_Finalize();
				exit(0);
			break;
		}
	}
	
	//For A
	read_row_striped_matrix(inFile1, (void***)&A, (void**)&Astorage, MPI_DOUBLE, &Am, &An, MPI_COMM_WORLD);
	//print_row_striped_matrix((void**)A, MPI_DOUBLE, Am, An, MPI_COMM_WORLD);

	//For B
	read_row_striped_matrix(inFile2, (void***)&B, (void**)&Bstorage, MPI_DOUBLE, &Bm, &Bn, MPI_COMM_WORLD);
	if(rank == 0)
	{
		//print_row_striped_matrix((void**)B, MPI_DOUBLE, Bm,Bn, MPI_COMM_WORLD);
		//printf("%f", Bstorage[2]);
	}
	numElements = Bn;
	numRows = BLOCK_SIZE(rank, size, Am);
	currentRow = BLOCK_LOW(rank, size, Am);
	//printf("Process %d: %d", rank, numRows);
	local_rows = (double *)malloc(numRows * numElements * sizeof(double));
	r_partner = (rank + 1)%size;
	l_partner = ((rank-1)+size) % size;
	for(i = 0; i < size; i++)
	{
		
		parallel_multiply(Astorage, Bstorage, &local_rows, numRows, numElements, currentRow);
		
		//MPI_Sendrecv_replace(Bstorage, numRows * numElements, MPI_DOUBLE, l_partner, 99, r_partner, 99,MPI_COMM_WORLD, &status);
		MPI_Sendrecv(Bstorage, numRows * numElements, MPI_DOUBLE, l_partner, 99, Bstorage, BLOCK_SIZE(r_partner, size, Am)*numElements, MPI_DOUBLE, r_partner, 99, MPI_COMM_WORLD, &status);
		currentRow = (currentRow + numRows)%Am;
	}


		for(i = 0; i < (numRows * numElements); i++)
    	{
       		printf("%f\n", local_rows[i]);
    	}

	

	MPI_Finalize();
	
	return(0);
}
