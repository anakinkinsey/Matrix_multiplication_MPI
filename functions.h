void make_matrix(int m, int n, int l, int u, double** matrix);
void write_matrix(char* file_name, int m, int n, double* matrix);
void print_matrix(int m, int n, double* matrix);
void read_matrix(char* file_name, int* m, int* n, double** matrix);
void matrix_multiply(int m, int n, int x, int y, double* matrix1, double* matrix2, double ** matrix_out);
void parallel_multiply(double *A, double *B, double *local_rows, int numRows, int numElements, int, int);