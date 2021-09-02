module system_readVelocityFortran

  use iso_c_binding
  implicit none

  double precision,dimension(:,:,:),allocatable::ux,uy,uz
  contains

  subroutine readVelocityFortran( u_x,u_y,u_z ) bind (C, name="readVelocityFortran")

  implicit none

  real (c_double), dimension (64,64,64), intent (out) :: u_x,u_y,u_z
  integer(kind=4)::ix,iy,iz
  integer(kind=4)::N=64,c=0
  character(len=100)::inpLoc

  ALLOCATE(ux(N,N,N),uy(N,N,N),uz(N,N,N))
  inpLoc = '../../Vk8.in'
  OPEN( UNIT = 44, FILE = trim(adjustl(inpLoc)), FORM='unformatted', STATUS='old')
  READ(44)(((ux(ix,iy,iz),uy(ix,iy,iz),uz(ix,iy,iz),iz=1,N),iy=1,N),ix=1,N)
  CLOSE(44)

  do iz=1,N
  do iy=1,N
  do ix=1,N
    u_x(iz,iy,ix)=ux(ix,iy,iz)
    u_y(iz,iy,ix)=uy(ix,iy,iz)
    u_z(iz,iy,ix)=uz(ix,iy,iz)
  end do
  end do
  end do

  DEALLOCATE(ux,uy,uz)
  end subroutine readVelocityFortran

end module
