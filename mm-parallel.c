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
	int opt = 0;
	char* inFile1, inFile2, outFile;

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
	

	
	MPI_Finalize();
	
	return(0);
}
