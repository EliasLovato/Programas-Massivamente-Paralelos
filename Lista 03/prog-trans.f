        program transpose

        double precision, allocatable :: a(:,:)
        double precision, allocatable :: b(:,:)
        double precision t1, t2, fn, rate, mysecond

        call pegavalor(N)
        fn = n

        allocate ( a(N,N) )
        allocate ( b(N,N) )

        call inicia(A,B,N)

        t1 = mysecond()
        do J=1,N
          do I=1,N
                B(I,J)=A(J,I)
          enddo
        enddo
        t2 = mysecond()

        rate=2*fn*fn/(1024*1024*(t2-t1))

        call confere(A,B,N)
        print *,"N=",N," T=",t2-t1," Rate=",rate,"MB/s"

        stop
        end
