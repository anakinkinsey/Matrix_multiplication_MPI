#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void make_matrix(int m, int n, int l, int u, int** matrix)
{
    *matrix = (int*)malloc(sizeof(int)*(n*m));
    int i;
    //srand(time(0));
    srand(time(0));
    for(i = 0; i < (m*n); i++)
    {
        (*matrix)[i] = rand() % ((u + 1) - l) + l;
    }



}

void write_matrix(char* file_name, int m, int n, int* matrix)
{
    FILE* file = fopen(file_name, "w");
    fwrite(&m, sizeof(int), 1, file);
    fwrite(&n, sizeof(int), 1, file);
    fwrite(matrix, sizeof(int), (n*m), file);

}

void print_matrix(int m, int n, int* matrix)
{
    int i;
    for(i = 0; i < m*n; i++)
    {
        if((i-1)%n == 0)
        {
            (printf("\n"));
        }
        else
        {
            printf("%d", matrix[i]);
        }
        
    }

}

void read_matrix(char* file_name, int* m, int* n, int** matrix)
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
    *matrix = (int*)malloc(sizeof(int)*((*n)*(*m)));
    fread(*matrix, sizeof(int), ((*n)*(*m)), file);



}