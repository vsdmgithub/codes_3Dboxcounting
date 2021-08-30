PROGRAM test_readdata 
! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
! ------------
! All the work is done in the modules. Calling a few would finish
! the code.
! -------------
! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

! [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
!  MODULES
!  ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

	IMPLICIT NONE
	! _________________________
	! LOCAL VARIABLES
	! !!!!!!!!!!!!!!!!!!!!!!!!!

       integer(kind=4)::i,j
       double precision,dimension(3,3)::datax,datax2
       double precision,dimension(3,3)::datay,datay2

       do i=1,3
       do j=1,3
      datax(i,j)= DBLE( i*j ) + 30.0d0
      datax2(i,j)= -DBLE( i*j ) - 20.0d0
      end do
      end do

     open(unit=11,file='write.in',form='unformatted',status='unknown')
       write(11)((datax(i,j),datax2(i,j),i=1,3),j=1,3)
   !  do i=1,3 
    ! do j=1,3 
     !end do
     !end do

     close(11)

     open(unit=11,file='write.in',form='unformatted',status='old')
     read(11)((datay(i,j),datay2(i,j),i=1,3),j=1,3)
     do i=1,3 
     do j=1,3 
     !read(11)datay(i,j),datay2(i,j)
     print*,i,j,datay2(i,j)+datay(i,j)
     end do
     end do
     close(11)
     
END PROGRAM test_readdata
