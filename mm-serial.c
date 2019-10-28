/*
	Cory Rothenberger & Anakin Kinsey
	CSCI 473
	October 27th
	Team Project
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
#include <getopt.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if(argc < 7)
    {
        printf("The proper usage is './mm-serial -A inputFile -B inputFile -C outputFile");
        exit(0);
    }
    else
    {
        int opt;
	int firstMR = 0,firstMC = 0,secondMR = 0,secondMC = 0;
       	char* inFile1;
	char* inFile2;
        char* outFile;
        double* matrixA;
	double* matrixB;
	double* matrixC;
	clock_t startMath, endMath, startIO, endIO, tt1, tt2;
	double mathTime, ioTime, totalTime, mflops1, mflops2;

	tt1 = clock();
        while((opt = getopt(argc, argv, "A:B:C:")) != -1)
	{
            switch (opt)
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
                    printf("The proper usage is './mm-serial -A inputFile -B inputFile -C outputFile");
        	exit(0);
                    break;
            
            }
        }
	
	startIO = clock();
	read_matrix(inFile1,&firstMR,&firstMC, &matrixA);
	read_matrix(inFile2,&secondMR,&secondMC, &matrixB);
	endIO = clock();

	ioTime = ((double) (endIO - startIO)) / CLOCKS_PER_SEC;
	if(firstMC != secondMR)
	{
		printf("The dimensions %d x %d and %d x %d are not compatible\n", firstMR, firstMC, secondMR, secondMC);
		exit(0);
	}

	startMath = clock();
	matrix_multiply(firstMR, firstMC, secondMR, secondMC, matrixA, matrixB, &matrixC);
	endMath = clock();
	
	startIO = clock();
	write_matrix( outFile, firstMR, secondMC, matrixC);
	endIO = clock();	

	tt2 = clock();

	ioTime += ((double) (endIO - startIO)) / CLOCKS_PER_SEC;
	totalTime = ((double) (tt2 - tt1)) / CLOCKS_PER_SEC;
	mathTime =((double) (endMath - startMath)) / CLOCKS_PER_SEC;
	
	mflops1 = ((8 * (firstMR * secondMC))/mathTime)/1000000;
	mflops2 = ((8 * (firstMR * secondMC))/totalTime)/1000000;

	printf("Time doing matrix multiplication: %f \n", mathTime);
	printf("Time doing file IO: %f \n", ioTime);
	printf("Time taken overall: %f \n", totalTime);	
	printf("m_flops_1: %f \n", mflops1);	
	printf("m_flops_2: %f \n", mflops2);

	free(matrixA);
	free(matrixB);
	free(matrixC);

	return 0;
       
    }
    

}
