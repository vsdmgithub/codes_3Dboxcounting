program main
    implicit none
double precision,dimension(3,3,3)::vel,vel2
integer(kind=4)::i,j,k,nx,ny,nz
double precision::val

nx=3
ny=3
nz=3

do i=1,nx
  do j=1,ny
    do k=1,nz
      val=DBLE(100*i+10*j+k)
      vel(i,j,k)=val
      vel2(i,j,k)=-val
    end do
  end do
end do

do k=1,nz
  print*,'Slice no',k
  do i=1,nx
    print*,int(vel(i,:,k))
  end do
end do


open(unit=11,file='Vk.in',form='unformatted',status='unknown')
write(11)(((vel(i,j,k),vel2(i,j,k),k=1,nz),j=1,ny),i=1,nx)
close(11)

end
