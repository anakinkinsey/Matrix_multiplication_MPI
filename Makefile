CFLAGS = -g -Wall -Wstrict-prototypes
OBJECTS = functions.o make-matrix print-matrix mm-serial
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
	@echo "	Matrix Multiplication Serial Command: ./mm-serial -i input_file"
	$(CC) $(CFLAGS) mm-serial.c functions.o -o mm-serial -lm

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c functions.h

clean:
	rm -f $(OBJECTS) *.o *.h.gch core*
