#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 24000

int main(int argc, char *argv[]) {
	double sum=0.0, t1, t2, f(), mysecond();
	int i, n=N, nt=1, len[N]; 

	if (argc>1) nt = atoi(argv[1]);
	if (nt<0) {
		printf("Use: %s [num_threads]\n",argv[0]);
		exit(-1);
	}

	for (i=0; i<n; i++) len[i]=(rand()) % (2*N-i);

	t1=mysecond();

# pragma omp parallel for num_threads(nt) reduction(+:sum) schedule(runtime)
	for(i=0; i<n; i++) {
		sum += f(i,len[i]);
	}

	t2=mysecond();

	printf("Num_threads=%d, Time=%lf\n",nt,t2-t1);
}

double f(int i, int k) {
	int j, start=i*(i+1)/2. , finish=start+k;
	double r_val=0;

	for (j=start; j<=finish; j++) {
		r_val += sin(j);
	}
	return r_val;
}
	
