#include <stdio.h>
#include "mpi.h"

// Lengths for statically allocated character arrays
#define MAX_NAME_LEN 128
#define MAS_DESC_LEN 1024

int main(int argc, char *argv[]){
	int myid, numprocs;
	int i, num_cvar, nameLen, verbosity, descLen, binding;
	int required = MPI_THREAD_SINGLE, provided, err, scope;
	char name[MAX_NAME_LEN], desc[MAX_DESC_LEN];
	
	MPI_T_enum	enumtype;
	MPI_Datatype	datatype;

// Initialize the MPI environmnt
	MPI_Init(&argc, &argv);
	
// Get the number processes and get the rank of the process
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	MPI_Init_thread(0, 0, required, &provided);
	MPI_T_init_thread(required, &provided);
	
	int getValue_int_comm(int index, MPI_Comm comm, int *val){
		int err, count;
		
		MPI_T_cvar_handle	handle;
		
// This example assumes that the variable index can be bound to a communicator
		err = MPI_T_cvar_handle_alloc(index, &comm, &handle, &count);
		
		if(err != MPI_SUCCESS) return err;
		
// The following assumes that the variable is represented by a single integer
		err = MPI_T_cvar_read(handle, val);
		
		if(err != MPI_SUCCESS) return err;
		
		err = MPI_T_cvar_handle_free(&handle);
		
		return err;
	}
	
// No test on return because we're about to exit
	MPI_T_finalize();

// Finalize the MPI environment
	MPI_Finalize();
	
	return 0;
}
