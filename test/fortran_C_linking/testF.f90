module fortmodule
use iso_c_binding
implicit none

double precision,dimension(3,3,3)::vel,vel2
contains

subroutine fortranReadFile ( array,array2 ) bind (C, name="fortranReadFile")

   implicit none
   real (c_double), dimension (3,3,3), intent (out) :: array,array2
  integer(kind=4)::i,j,k,nx,ny,nz
  nx=3
  ny=3
  nz=3

  OPEN( UNIT = 44, FILE = '../Vk.in', FORM='unformatted', STATUS='old')
  READ(44)(((vel(i,j,k),vel2(i,j,k),k=1,nz),j=1,ny),i=1,nx)
  CLOSE(44)

  DO k=1,nz
  DO j=1,ny
  DO i=1,nx
    array(k,j,i)=vel(i,j,k)
    array2(k,j,i)=vel2(i,j,k)
  END do
  END DO
  END DO

end subroutine fortranReadFile

end module
