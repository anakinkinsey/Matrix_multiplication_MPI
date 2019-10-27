/**
 * 473 Final Project
 * Anakin Kinsey & Cory Rothenberger
 * 10/27/2019
 * Fall 2019
**/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
#include <getopt.h>

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
        char* file_name;
        int* matrix;

        while(opt = getopt(argc, argv, "i:") != -1) {
            switch (opt)
            {
                case 'i':
                    file_name = optarg;
                    break;
                case '?':
                    printf("The proper usage is 'print-matrix -i infile.dat");
                    exit(0);
                    break;
            
            }
        }

        read_matrix(file_name, &m, &n, &matrix);
        print_matrix(m, n, matrix);
    }
    

}