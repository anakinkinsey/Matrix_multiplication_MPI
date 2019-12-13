/**
 * 473 Final Project
 * Anakin Kinsey & Cory Rothenberger
 * 10/27/2019
 * Fall 2019
**/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void make_matrix(int m, int n, int l, int u, double** matrix)
{
    *matrix = (double*)malloc(sizeof(double)*(n*m));
    int i;
    srand(time(0));
    for(i = 0; i < (m*n); i++)
    {
    	double num = RAND_MAX/(u-l);
        (*matrix)[i] = l + (rand()/num);
    }



}

void write_matrix(char* file_name, int m, int n, double* matrix)
{
    FILE* file = fopen(file_name, "w");
    fwrite(&m, sizeof(int), 1, file);
    fwrite(&n, sizeof(int), 1, file);
    fwrite(matrix, sizeof(double), (n*m), file);
	fclose(file);

}

void print_matrix(int m, int n, double* matrix)
{
    int i;
    for(i = 0; i < m*n; i++)
    {
            printf("%0.4f ", matrix[i]);
        	if((i+1)%n == 0)
        	{
            		printf("\n");
        	}
    }

}

void read_matrix(char* file_name, int* m, int* n, double** matrix)
{
    FILE* file;
    file = fopen(file_name, "rb");

    if(file == NULL)
    {
        printf("File does not exist");
        exit(0);
    }
    fread(m, sizeof(int), 1, file);
    fread(n, sizeof(int), 1, file);
    *matrix = (double*)malloc(sizeof(double)*((*n)*(*m)));
    fread(*matrix, sizeof(double), ((*n)*(*m)), file);

	fclose(file);

}

void matrix_multiply(int m, int n, int x, int y, double* matrix1, double* matrix2, double** matrix_out)
{
    *matrix_out = (double*)malloc(sizeof(double) * (m*y));
    int row, column, row_traverser;
    double total;
    //int row_array[m];
    //int column_array[n];  
    for(row = 0; row < m; row++)
    {
        for(column = 0; column < y; column++)
        {
            total = 0;
            for(row_traverser = 0; row_traverser < n; row_traverser++)
            {
                total += matrix1[row * n + row_traverser] * (double)matrix2[row_traverser * y + column];
            }
            (*matrix_out)[row * y + column] = total;
        } 
    }
}
//*A: Astorage
//*B: Bstorage
//iter: currentRow for the process
//numElements: numElements in the row
//numRows: number of Rows
void parallel_multiply(double *A, double *B, double *local_rows, int numRows, int numElements, int Brow, int rank)
{
   int i, j, k, howDeep = numRows;
    //printf("Brow is %d\n", Brow);
 
    for(i = 0; i < (numRows); i++)
    {
        //printf("Brow is to %d: ", Brow);
        for(j = (Brow) + (i*numElements); j < ((Brow) + (i*numElements) + howDeep); j++)
        {
            //printf("Brow is to %d: ", Brow);
           
            for(k = (j%numRows)*numElements; k < (((j%numRows)*numElements) + numElements); k++)
            {
               //printf("temp is %d\n", temp);
                //printf("Process %d on working with %d Grabbing %.2f, and %.2f    ", rank, Brow, A[j], B[k]);
                
                local_rows[(i * numElements) + k%numElements] += (B[k]) * A[j];
                //printf("%d\n", ((i * numElements) + k%numElements));
            }
        }
    }

   //*local_rows = temp; 
   //printf("%f\n", A[iter]);
    //printf("]\n");
    

   //for(i = 0; i < (Bm * Bn); i++)
   //{
   //    printf("%f", *local_rows[i]);
   //}
}




