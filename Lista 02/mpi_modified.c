#include <mpi.h>
#include <papi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define NUM_EVENTS 3
#define SIZE 1000000

int m;

void exit(int), do_flops(double *, int);

int main(int argc, char* argv[]){

	int myid, numprocs;
	
// Create the events vector
	int Events[NUM_EVENTS] = {PAPI_TOT_CYC, PAPI_TOT_INS, PAPI_FP_INS};
	long_long avalues[NUM_EVENTS], bvalues[NUM_EVENTS];

// Initialize the MPI environment
	MPI_Init(&argc, &argv);
		
// Get the number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	
// Get the rank of the process
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
// Initializations
	m = myid + 1;
	double x = 0.5;
	
// Warmup and start counting events
	if (PAPI_start_counters(Events, NUM_EVENTS) != PAPI_OK) exit(-1);
		do_flops(&x, 4*SIZE);
	
// Do flops and read the counters
		if (PAPI_read_counters(avalues, NUM_EVENTS) != PAPI_OK) exit(-1);
		do_flops(&x, SIZE);
	
// Do many more flops and read the counters again
		if (PAPI_read_counters(bvalues, NUM_EVENTS) != PAPI_OK) exit(-1);
		do_flops(&x, 4*SIZE);
	
	printf("\nRank process %d, all done: x = %lf\n", myid, x);
	printf("\nApos primeira leitura dos conunters\nPAPI_TOT_CYC: %lld, PAPI_TOT_INS: %lld, PAPI_FP_INS: %lld\n", avalues[0], avalues[1], avalues[2]);
	printf("\nApos segunda leitura dos counters\nPAPI_TOT_CYC: %lld, PAPY_TOT_INS: %lld, PAPI_FP_INS: %lld\n", bvalues[0], bvalues[1], bvalues[2]);
		
// Finalize the MPI environment
	MPI_Finalize();
}

void do_flops(double *x, int k){

	int i, passes;
	
	for (passes=0; passes<m; passes++){
		for (i=0; i<k; i++){
			
			*x = sin(*x);
		}
	}
}
