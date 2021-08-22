#include <stdio.h>
#include "mpi.h"

// Lengths for statically allocated character arrays
#define MAX_NAME_LEN 128
#define MAX_DESC_LEN 1024

int main(int argc, char *argv[]){

	int i, num_pvar, nameLen, verbosity, descLen, binding;
	int var_class, readonly, continuous, atomic, count;
	int required = MPI_THREAD_SINGLE, provided, err;
	char name[MAX_NAME_LEN], desc[MAX_DESC_LEN];
	
	MPI_T_enum		enumtype;
	MPI_Datatype		datatype;
	MPI_Comm		comm;
		
	MPI_Init_thread(0, 0, required, &provided);
	MPI_T_init_thread(required, &provided);
		
	MPI_T_pvar_get_num(&num_pvar);
	printf("%d MPI Performance Variables\n", num_pvar);
	
	for(i=0; i<num_pvar; i++){
		nameLen = sizeof(name);
		descLen = sizeof(desc);
		
		err = MPI_T_pvar_get_info(i, name, &nameLen, &verbosity, &var_class, &datatype, &enumtype, desc, &descLen, &binding, &readonly, &continuous, &atomic);
		
		printf("\t%s\tClass=%d\tReadonly=%s\tContinuous=%s\tAtomic=%s\t%s\n", name, var_class, readonly ? "T" : "F", desc);
	}
		
// No test on return because we're about to exit
	MPI_T_finalize();

// Finalize the MPI environment
	MPI_Finalize();
	
	return 0;
}
