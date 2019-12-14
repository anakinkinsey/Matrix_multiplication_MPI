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
#include "timer.h"

int main(int argc, char *argv[])
{
    if(argc < 7)
    {
        printf("The proper usage is './mm-serial -A inputFile -B inputFile -C outputFile\n");
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
	//clock_t startMath, endMath, startIO, endIO, tt1, tt2;
	double mathTime, totalTime, mflops1, mflops2;
	double startTime, endTime, comp_start, comp_end;

	GET_TIME(startTime);
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
                    printf("The proper usage is './mm-serial -A inputFile -B inputFile -C outputFile\n");
        	exit(0);
                    break;
            
            }
        }
	
	
	read_matrix(inFile1,&firstMR,&firstMC, &matrixA);
	read_matrix(inFile2,&secondMR,&secondMC, &matrixB);
	

	
	if(firstMC != secondMR)
	{
		printf("The dimensions %d x %d and %d x %d are not compatible\n", firstMR, firstMC, secondMR, secondMC);
		exit(0);
	}
	GET_TIME(comp_start);
	matrix_multiply(firstMR, firstMC, secondMR, secondMC, matrixA, matrixB, &matrixC);
	GET_TIME(comp_end);
	
	write_matrix( outFile, firstMR, secondMC, matrixC);
		
	GET_TIME(endTime);


	
	totalTime = endTime - startTime;
	mathTime = comp_end - comp_start;
	
	mflops1 = ((firstMR * firstMC * secondMC)/mathTime)/1000000;
	mflops2 = ((firstMR * firstMC * secondMC)/totalTime)/1000000;

	printf("Comp time: %.4f seconds\n", mathTime);
	printf("IO time: %.4f seconds\n", totalTime - mathTime);
	printf("Total time: %.4f seconds\n\n", totalTime);
	printf("MegaFlops(Comp time): %f\n", mflops1);
	printf("MegaFlops(Total time): %f\n", mflops2);

	free(matrixA);
	free(matrixB);
	free(matrixC);

	return 0;
       
    }
    

}
