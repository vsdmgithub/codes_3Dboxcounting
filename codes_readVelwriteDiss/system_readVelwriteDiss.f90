! --------------------------------------------------------------
! -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
! CODE BY:
! --------   |         |   ---------        /\        |\      |
! |          |         |  |                /  \       | \     |
! |          |         |  |               /    \      |  \    |
! --------   |         |  |   ------|    /------\     |   \   |
!         |  |         |  |         |   /        \    |    \  |
!         |  |         |  |         |  /          \   |     \ |
! ---------   ----------  ----------  /            \  |      \|
! --------------------------------------------------------------

! #########################
! MODULE: system_readVelwriteDiss
! LAST MODIFIED: 18 Aug 2021
! #########################

MODULE system_readVelwriteDiss
! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
! ------------
! Reads real space velocity from file and calculates dissipation density at every point
! writes as 1D lienar list
! -------------
! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  ! [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
  !  SUB-MODULES
  !  ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
  USE system_basicvariables
  USE system_fftw_adv
  ! HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

  IMPLICIT  NONE

  CONTAINS

  SUBROUTINE IC_from_file_spectral
  ! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ! ------------
  ! CALL THIS SUBROUTINE TO:
  ! Read a file for the velocity data in spectral space.
  ! -------------
  ! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    IMPLICIT  NONE
    ! _________________________
    ! LOCAL VARIABLES
    ! !!!!!!!!!!!!!!!!!!!!!!!!!
    DOUBLE PRECISION::real_part,imag_part
    CHARACTER(LEN=80)::IC_file_name

    !>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    ! V   E  L  O  C  I  T  Y       I  N  P  U  T     F  I  L  E
    !>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    IC_file_name  = 'spectralinput.dat'
    !>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    OPEN( UNIT = 43, FILE = IC_file_name )

    ! '+++++++++++++++++++++'
    ! 'I.C FROM FILE'
    ! '+++++++++++++++++++++'

    DO i_x = kMin_x, kMax_x
    DO i_y = kMin_y, kMax_y
  	DO i_z = kMin_z, kMax_z

      READ(43,f_c32p17,ADVANCE='NO') real_part, imag_part
      v_x( i_x, i_y, i_z ) = DCMPLX( real_part, imag_part )
      READ(43,f_c32p17,ADVANCE='NO') real_part, imag_part
      v_y( i_x, i_y, i_z ) = DCMPLX( real_part, imag_part )
      READ(43,f_c32p17,ADVANCE='YES') real_part, imag_part
      v_z( i_x, i_y, i_z ) = DCMPLX( real_part, imag_part )

    END DO
    END DO
    END DO

    CLOSE(43)
    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  END

  SUBROUTINE IC_from_file_real
  ! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ! ------------
  ! CALL THIS SUBROUTINE TO:
  ! Read a file for the velocity data in real space.
  ! -------------
  ! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    IMPLICIT  NONE
    ! _________________________
    ! LOCAL VARIABLES
    ! !!!!!!!!!!!!!!!!!!!!!!!!!
    CHARACTER(LEN=180)::IC_file_name
     DOUBLE PRECISION::a1,a2,a3

    !>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    ! V   E  L  O  C  I  T  Y       I  N  P  U  T     F  I  L  E
    !>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    IC_file_name  = TRIM(ADJUSTL(fileAdd))//TRIM(ADJUSTL(velName))//'.in'
    !>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !OPEN( UNIT = 44, FILE = IC_file_name, FORM='unformatted', STATUS='old', ACCESS='sequential', ACTION='read')
    OPEN( UNIT = 44, FILE = IC_file_name, FORM='unformatted', STATUS='old')

    ! '+++++++++++++++++++++'
    ! 'I.C FROM FILE'
    ! '+++++++++++++++++++++'

        READ(44)(((u_x(i_x,i_y,i_z),u_y(i_x,i_y,i_z),u_z(i_x,i_y,i_z), &
        i_z=0,N_z-1),i_y=0,N_y-1),i_x=0,N_x-1)

    !DO i_x = 0 ,2! N_x - 1
    !DO i_y = 0 ,2!N_y - 1
    !DO i_z = 0 ,2! N_z - 1

    !    READ(44)u_x(i_x,i_y,i_z),u_y(i_x,i_y,i_z),u_z(i_x,i_y,i_z)
!print*,i_x,i_y,i_z
!print*,u_x(i_x,i_y,i_z),u_y(i_x,i_y,i_z),u_z(i_x,i_y,i_z)
     !READ(44,f_d32p17,ADVANCE = 'NO')  u_x( i_x, i_y, i_z)
     !READ(44,f_d32p17,ADVANCE = 'NO')  u_y( i_x, i_y, i_z)
     !READ(44,f_d32p17,ADVANCE = 'YES') u_z( i_x, i_y, i_z)

 !   END DO
  !  END DO
   ! END DO
  
    CLOSE(44)
    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    DO i_x = 0,N_x-1 
    DO i_y = 0,N_y-1 
    DO i_z = 0,N_z-1
        IF( u_x(i_x,i_y,i_z) .NE. u_x(i_x,i_y,i_z) ) THEN
                nan_status = 1
print*,"NaN detected at ",i_x,i_y,i_z
                exit
        END IF 
    END DO
    END DO
    END DO
                        
  END

  SUBROUTINE compute_strain_tensor
  ! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ! ------------
  ! CALL this to compute the strain tensor array
  ! -------------
  ! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    IMPLICIT NONE

    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !   S  T  R  A  I  N        T  E  N  S  O  R        C  A  L  C.
    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    CALL fft_c2r_vec(i*k_x*v_x,hf*i*(k_y*v_x+k_x*v_y),i*k_z*v_z,str_xx,str_xy,str_zz)
    CALL fft_c2r_vec(i*k_y*v_y,hf*i*(k_y*v_z+k_z*v_y),hf*i*(k_x*v_z+k_z*v_x),str_yy,str_yz,str_zx)
    ! All six components of strain tensor.

  END

  SUBROUTINE compute_dissipation_field
  ! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ! ------------
  ! CALL this to compute the dissipation field
  ! -------------
  ! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    IMPLICIT NONE

    dissipationMax = one

    dissipation_field = str_xx ** two + str_yy ** two + str_zz ** two + &
               two * ( str_xy ** two + str_yz ** two + str_zx ** two)

    dissipationMax = MAXVAL(dissipation_field)
    print*,MAXVAL(dissipation_field)

  END

  SUBROUTINE write_dissipation_field
  ! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ! ------------
  ! This writes the dissipation field.
  ! -------------
  ! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    IMPLICIT NONE
    CHARACTER(LEN=180)::file_name

    file_name = TRIM(ADJUSTL(outDir))//'ds_'//TRIM(ADJUSTL(velName))//'.dat'
    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ! File where energy vs time will be written. With additional data

    OPEN( unit = 74, file = file_name )
    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !  P  R  I  N   T          O  U  T  P  U  T   -   DATA FILE
    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    DO i_x = 0 , N_x - 1
    DO i_y = 0 , N_y - 1
    DO i_z = 0 , N_z - 1

      WRITE(74,f_d32p17,ADVANCE ='YES')  dissipation_field( i_x, i_y, i_z)/dissipationMax

    END DO
    END DO
    END DO

    CLOSE(74)
    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  END

END MODULE system_readVelwriteDiss
