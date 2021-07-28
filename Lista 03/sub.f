        subroutinea inicia(a,b,n)
        double precision a(n,n),b(n,n)
        do i=1,n
                do j=1,n
                        a(i,j)=1.0
                        b(i,j)=0
                enddo
        enddo
        return
        end

        subroutine confere(a,b,n)
        double precision a(n,n),b(n,n)
        do i=1,n
                do j=1,n
                        if ( a(i,j) .ne. b(i,j) ) print *,"Erro: ",i,j 
                enddo
        enddo
        return
        end

        subroutine mydummy()
        return
        end
