program transpose
        
	IMPLICIT NONE
        
	INCLUDE 'f90papi.h'

        double precision, allocatable :: a(:,:)
        double precision, allocatable :: b(:,:)
        double precision :: t1, t2, fn, rate, mysecond
        
        INTEGER, DIMENSION(5) :: events = (/PAPI_LD_INS, PAPI_SR_INS, PAPI_L1_TCM, PAPI_L2_TCM, PAPI_L3_TCM/)
        INTEGER*8, DIMENSION(5) :: avalues
        INTEGER*8, DIMENSION(5) :: bvalues
	INTEGER :: I, J, N, check

        call pegavalor(N)
        fn = n

        allocate ( a(N,N) )
        allocate ( b(N,N) )

        call inicia(A,B,N)
        
        t1 = mysecond()

	call PAPIF_start_counters(events, 5, check)
	if (check .ne. PAPI_OK) stop


	do J=1,N
		do I=1,N
			B(I,J)=A(J,I)
		enddo
	enddo
	
	call PAPIF_read_counters(avalues, 5, check)
	if (check .ne. PAPI_OK) stop
	        
	t2 = mysecond()

        rate=2*fn*fn/(1024*1024*(t2-t1))

        call confere(A,B,N)
        print *,"N=",N," T=",t2-t1," Rate=",rate,"MB/s"
        
	print *,"PAPI_LD_INS=",avalues(1)," PAPI_SR_INS=",avalues(2)," PAPI_L1_TCM=",avalues(3)," PAPI_L2_TCM=",avalues(4)," PAPI_L3_TCM=",avalues(5)

        stop
end
