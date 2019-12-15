/**
 * 473 Final Project
 * Anakin Kinsey & Cory Rothenberger
 * 10/27/2019
 * Fall 2019
**/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"
#include "MyMPI.h"
#include "timer.h"

int main(int argc, char **argv)
{
	int rank,size;
	int opt = 0, An, Am, Bn, Bm, numRows, numElements, i, r_partner, l_partner, currentRow;
	char *inFile1, *inFile2, *outFile;
	double **A, *Astorage;
	double **B, *Bstorage;
	double *local_rows, *bigC;
	double startTime, endTime, comp_start, comp_end;
	MPI_Status status;
	
	//MPI_Comm comm;
	//FILE* outputFile = fopen(outFile, "wb");
	//free(outFile);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	GET_TIME(startTime);
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
	for(i = 0; i < numRows * numElements; i++)
	{
		local_rows[i] = 0;
	}
	GET_TIME(comp_start);
	if(size > 1){
		r_partner = (rank + 1)%size;
		l_partner = ((rank-1)+size) % size;
		
		for(i = 0; i < size; i++)
		{
			//printf("Beginning phase %d\n", i);
			//printf("Current row for %d is %d", rank, currentRow);
			//printf("Brow is to %d: ", currentRow);
			parallel_multiply(Astorage, Bstorage, local_rows, numRows, numElements, currentRow, rank);
			
			// for(j = 0; j < (numRows * numElements); j++)
			// {
			// 	printf("%d process on phase %d %f\n", rank, i, local_rows[j]);
			// }
			// printf("\n");

			//MPI_Sendrecv_replace(Bstorage, numRows * numElements, MPI_DOUBLE, l_partner, 99, r_partner, 99,MPI_COMM_WORLD, &status);
			MPI_Sendrecv(Bstorage, numRows * numElements, MPI_DOUBLE, l_partner, 99, Bstorage, BLOCK_SIZE(r_partner, size, Am)*numElements, MPI_DOUBLE, r_partner, 99, MPI_COMM_WORLD, &status);
			currentRow = (currentRow + numRows)%Am;//if that heifer wraps
			
		}
	}
	else
	{
		//printf("Only for single threaded\n");
		parallel_multiply(Astorage, Bstorage, local_rows, numRows, numElements, currentRow, rank);
	}
	GET_TIME(comp_end);
	
	// for(i = 0; i < (numRows * numElements); i++)
	// {
	//  			printf("%f\n", local_rows[i]);
	// }
	// printf("\n");
	if(rank == 0)
	{
		bigC = (double*)malloc(Am * Bn * sizeof(double));
		MPI_Gather(local_rows, (numRows * numElements), MPI_DOUBLE, bigC, (numRows*numElements), MPI_DOUBLE, 0, MPI_COMM_WORLD);
	}
	else{
		MPI_Gather(local_rows, (numRows * numElements), MPI_DOUBLE, NULL, (numRows*numElements), MPI_DOUBLE, 0, MPI_COMM_WORLD);
	}
	if(rank == 0)
	{
		write_matrix(outFile, Am, Bn, bigC);
	}
	// if(rank == 0)
	// {
	// 	double *temp = (double*)malloc(numRows * numElements * sizeof(double));
	// 	FILE* outputFile = fopen(outFile, "a");
	// 	fwrite(&Am, sizeof(int), 1, outputFile);
    // 	fwrite(&Bn, sizeof(int), 1, outputFile);
    // 	fwrite(local_rows, sizeof(double), numRows*numElements, outputFile);
	// 	for(i = 1; i < size; i++)
	// 	{
	// 		MPI_Recv(temp, (numRows*numElements), MPI_DOUBLE, i, 99, MPI_COMM_WORLD, &status);
	// 		printf("size %d: ", size);
	// 		for(i = 0; i < numElements*numRows;i++)
	// 		{
	// 			printf("%.2f ", temp[i]);
	// 		}
	// 		printf("\n");
	// 	 	fwrite(temp, sizeof(double), numRows*numElements, outputFile);
	// 	 }
	// }
	// else
	// {
	// 	MPI_Ssend(local_rows, (numElements*numRows), MPI_DOUBLE, 0, 99, MPI_COMM_WORLD);
	// }

	MPI_Barrier(MPI_COMM_WORLD);//syncs project
	GET_TIME(endTime);
	if(rank == 0)
	{
		printf("Comp time: %.4f seconds\n", comp_end - comp_start);
		printf("IO time: %.4f seconds\n", (endTime - startTime) - (comp_end-comp_start));
		printf("Total time: %.4f seconds\n\n", endTime - startTime);
		printf("MegaFlops(Comp time): %f\n", (((double)Am * (double)An * (double)Bn)/(comp_end - comp_start))/1000000); //casting to double in the case when you go over 2^31 when determining n^3
		printf("MegaFlops(Total time): %f\n", (((double)Am * (double)An * (double)Bn)/(endTime - startTime))/1000000);
	}
	MPI_Finalize();
	
	return(0);
}
