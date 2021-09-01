program main
    implicit none
double precision,dimension(3,3)::vel
double precision,dimension(3,3)::vel2
integer(kind=4)::i,j,N
double precision::val
N=3

do i=1,N
  do j=1,N
      val=DBLE(10*i+1*j)
      vel(i,j)=val
      vel2(i,j)=-val
  end do
  print*,int(vel(i,:))
end do

open(unit=11,file='Vk.in',form='unformatted',status='unknown')
write(11)((vel(i,j),j=1,N),i=1,N)
! write(11)((vel(i,j),vel2(i,j),i=1,N),j=1,N)
close(11)

end
