program transpose

	IMPLICIT NONE

	INCLUDE 'f90papi.h'
	
	DOUBLE PRECISION, ALLOCATABLE :: a(:,:), b(:,:)
	DOUBLE PRECISION :: t1, t2, fn, rate, mysecond
	
	INTEGER, DIMENSION(5) :: events = (/PAPI_LD_INS, PAPI_SR_INS, PAPI_L1_TCM, PAPI_L2_TCM, PAPI_L3_TCM/)
	INTEGER*8, DIMENSION(5) :: avalues, bvalues
	INTEGER :: I, J, N, K, L, check, strideI, strideJ
	INTEGER, PARAMETER :: M = 1024
	
	CALL pegavalor(N)
	fn = n

	strideJ = M
	strideI = M
	
	ALLOCATE (a(N, N))
	ALLOCATE (b(N, N))
	
	CALL inicia(a, b, N)
	
	t1 = mysecond()
	
	CALL PAPIF_start_counters(events, 5, check)
	IF (check .ne. PAPI_OK) STOP
	
	DO K = 1, N, strideJ
		DO L = 1, N, strideI
			DO J = K, min(N, K + strideJ - 1)
				DO I = L, min(N, L + strideI - 1)
					B(I, J) = A(J, I)
				ENDDO
			ENDDO
		ENDDO
	ENDDO
	
	CALL PAPIF_read_counters(bvalues, 5, check)
	IF (check .ne. PAPI_OK) STOP
	
	t2 = mysecond()
	
	rate = 2*fn*fn/(1024*1024*(t2 - t1))
	
	CALL confere(a,b,N)
	
	PRINT *,"N =",N," T=",t2-t1," Rate=",rate,"MB/s"
	PRINT *,"PAPI_LD_INS=",bvalues(1)," PAPI_SR_INS",bvalues(2)," PAPI_L1_TCM=",bvalues(3)," PAPI_L2_TCM=",bvalues(4)," PAPI_L3_TCM=", bvalues(5)
	
	STOP
END 
	
