#include <papi.h>
#include <stdio.h>
#include <math.h>

// #define NUM_EVENTS 3
#define NUM_EVENTS 4
#define TIMES 1000000

main()
{
//  int i, Events[NUM_EVENTS] = {PAPI_TOT_CYC,PAPI_TOT_INS,PAPI_FP_INS};
  int i, Events[NUM_EVENTS] = {PAPI_L1_DCM,PAPI_TLB_DM,PAPI_BR_TKN,PAPI_L2_DCH};
  long_long avalues[NUM_EVENTS],bvalues[NUM_EVENTS];
  double x=0.5;

  int nc = PAPI_num_counters();
  printf("Num.Counters=%d\n",nc);
//  printf("PAPI_TOT_CYC,PAPI_TOT_INS,PAPI_FP_INS\n");
  printf("PAPI_L1_DCM, PAPI_TLB_DM, PAPI_BR_TKN, PAPI_L2_DCH\n");

/* Start counting events */
if (PAPI_start_counters(Events, NUM_EVENTS) != PAPI_OK) exit(-1);

  for (i=0; i<TIMES/4; i++) x=sin(x);

/* Read the counters */
  if (PAPI_read_counters(avalues, NUM_EVENTS) != PAPI_OK) exit(-1);
   
  for (i=0; i<TIMES; i++) x=sin(x);

/* Read the counters again */
  if (PAPI_read_counters(bvalues, NUM_EVENTS) != PAPI_OK) exit(-1);

/* Print counters */
//  printf("Apos primeira leitura dos counters: %lld, %lld, %lld, x=%lf\n",
//		avalues[0],avalues[1],avalues[2],x);
//  printf("Apos segunda leitura dos counters: %lld, %lld, %lld, x=%lf\n",
//		bvalues[0],bvalues[1],bvalues[2],x);

  printf("Apos primeira leitura dos counters: %lld, %lld, %lld, %lld, x=%lf\n", avalues[0], avalues[1], avalues[2], avalues[3], x);
  printf("Apos segunda leitura dos counters: %lld, %lld, %lld, %lld, x=%lf\n", bvalues[0], bvalues[1], bvalues[2], bvalues[3], x);

  printf("All done\n");
}
