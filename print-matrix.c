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

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("The proper usage is 'print-matrix -i infile.dat");
        exit(0);
    }
    else
    {
        int opt;
        int n, m;
        char* in;
        int* matrix;

       while((opt = getopt(argc, argv, "i:")) != -1)
	{
		switch(opt)
		{	
			case'i':
				in = optarg;
			break;
			case '?':
				printf("Incorrect Input \nCorrect Usage: ");
				printf("./make-matrix -m ## -n ## -l ## -u ## -o output_file\n");
				printf("Where m = # of rows, n = # of columns");
				exit(0);
			break;
			
		}
	}
        read_matrix(in, &m, &n, &matrix);

        print_matrix(m, n, matrix);
    }
    

}
