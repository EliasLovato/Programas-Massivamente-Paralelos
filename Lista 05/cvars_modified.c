#include <stdio.h>
#include "mpi.h"

// Lengths for statically allocated character arrays
#define MAX_NAME_LEN 128
#define MAX_DESC_LEN 1024

int main(int argc, char *argv[]){
	int myid, count;
	int i, num_cvar, nameLen, verbosity, descLen, binding;
	int required = MPI_THREAD_SINGLE, provided, err, scope;
	char name[MAX_NAME_LEN], desc[MAX_DESC_LEN];
	
	MPI_T_enum		enumtype;
	MPI_Datatype		datatype;
	MPI_T_cvar_handle	handle;
	void *comm, *val;
		
	MPI_Init_thread(0, 0, required, &provided);
	MPI_T_init_thread(required, &provided);
	
// Get the rank of the process
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	MPI_T_cvar_get_num(&num_cvar);
	printf("%d MPI Control Variables\n", num_cvar);
	
	for(i=0; i<3; i++){
		nameLen = sizeof(name);
		descLen = sizeof(desc);
		
		err = MPI_T_cvar_get_info(i, name, &nameLen, &verbosity, &datatype, &enumtype, desc, &descLen, &binding, &scope);
		
// This example assumes that the variable index can be bound to a communicator
		err = MPI_T_cvar_handle_alloc(i, &comm, &handle, &count);
		
		val = (int *)malloc(count * sizeof(int));

// The following assumes that the variable is represented by a single integer		
		err = MPI_T_cvar_read(handle, val);
		
		printf("\nProcesso: %d - cvar: %d \n%-32s\t%s\n valor: %d \n", myid, i, name, desc, val);
		
		err = MPI_T_cvar_handle_free(&handle);
	}
		
// No test on return because we're about to exit
	MPI_T_finalize();

// Finalize the MPI environment
	MPI_Finalize();
	
	return 0;
}
