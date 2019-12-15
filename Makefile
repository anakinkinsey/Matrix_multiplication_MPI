CFLAGS = -g -Wall -Wstrict-prototypes
OBJECTS = functions.o make-matrix print-matrix mm-serial MyMPI.o mm-parallel
CC = gcc
MCC = mpicc

all: $(OBJECTS)

make-matrix: make-matrix.c functions.o
	@echo "	Make Matrix Command ./make-matrix -m ## -n ## -l ## -u ## -o output_file"
	$(CC) $(CFLAGS) make-matrix.c functions.o -o make-matrix -lm

print-matrix: print-matrix.c functions.o
	@echo "	Print Matrix Command: ./print-matrix -i input_file"
	$(CC) $(CFLAGS) print-matrix.c functions.o -o print-matrix -lm

mm-serial: mm-serial.c functions.o
	@echo "	Matrix Multiplication Serial Command: ./mm-serial -A input_file -B input_file -C output_file"
	$(CC) $(CFLAGS) mm-serial.c functions.o -o mm-serial -lm

mm-parallel: mm-parallel.c functions.o MyMPI.o
	@echo "	Matrix Multiplication Parallel Command: mpirun -np <int> ./mm-parallel -A input_file -B input_file -C output_file"
	$(MCC) $(CFLAGS) mm-parallel.c functions.o MyMPI.o -o mm-parallel -lm

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c functions.h

MyMPI.o: MyMPI.c MyMPI.h
	$(MCC) $(CFLAGS) -c MyMPI.c MyMPI.h

clean:
	rm -f $(OBJECTS) *.o *.h.gch core*
