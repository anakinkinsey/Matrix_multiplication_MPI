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
       	char* inFile1;
	char* inFile2;
        char* outFile;
        int* matrix;

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

       
    }
    

}
