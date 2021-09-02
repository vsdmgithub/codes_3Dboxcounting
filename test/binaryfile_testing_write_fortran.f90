program main
implicit none
double precision,dimension(64,64,64)::ux,uy,uz
integer(kind=4)::i,j,k,N
double precision,dimension(3)::val
N=64

do i=1,N
do j=1,N
do k=1,N
  call random_number(val)
  ux(i,j,k) = val(1) - 1.0d0
  uy(i,j,k) = val(2) - 1.0d0
  uz(i,j,k) = val(3) - 1.0d0
end do
end do
end do

open(unit=11,file='../../Vk8.in',form='unformatted',status='unknown')
write(11)(((ux(i,j,k),uy(i,j,k),uz(i,j,k),k=1,N),j=1,N),i=1,N)
close(11)

end
