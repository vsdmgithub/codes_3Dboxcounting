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
! MODULE: system_basicvariables
! LAST MODIFIED: 18 Aug 2021
! #########################

! TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
! BASIC VARIABLES AND ARRAYS
! IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

MODULE system_basicvariables
! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
! ------------
! All the global variables and arrays for the simulation space are declared and given values
! -------------
! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  ! [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
  !  SUB-MODULES
  !  ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
  USE system_constants
  USE system_auxilaries
  ! HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

  IMPLICIT NONE
  ! _________________________
  ! REAL SPACE
  ! !!!!!!!!!!!!!!!!!!!!!!!!!
  INTEGER(KIND =4) ::N_x,N_y,N_z
  INTEGER(KIND =4) ::N_min,N_max
  INTEGER(KIND =4) ::kMax_x,kMax_y,kMax_z
  INTEGER(KIND =4) ::kMin_x,kMin_y,kMin_z
  INTEGER(KIND =4) ::i_x,i_y,i_z
  INTEGER(KIND =4) ::j_x,j_y,j_z
  INTEGER(KIND =4),DIMENSION(3)::N_ar
  DOUBLE PRECISION ::N3,vol,dxdydz
  DOUBLE PRECISION ::L_x,L_y,L_z
  DOUBLE PRECISION ::dx,dy,dz
  DOUBLE PRECISION ::K_scale_x,K_scale_y,K_scale_z
  ! _________________________________________
  ! REAL SPACE ARRAYS
  ! !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  DOUBLE PRECISION,DIMENSION(:,:,:),ALLOCATABLE ::u_x,u_y,u_z
  DOUBLE PRECISION,DIMENSION(:,:,:),ALLOCATABLE ::str_xx,str_yy,str_zz
  DOUBLE PRECISION,DIMENSION(:,:,:),ALLOCATABLE ::str_xy,str_yz,str_zx
  DOUBLE PRECISION,DIMENSION(:,:,:),ALLOCATABLE ::dissipation_field
  ! Real velocity matrix  (updated after every time step)
  ! _________________________________________
  ! FOURIER SPACE ARRAYS
  ! !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  DOUBLE PRECISION,DIMENSION(:,:,:),ALLOCATABLE ::k_x,k_y,k_z,k_2
  ! wavenumber,truncator matrix
  DOUBLE COMPLEX,DIMENSION(:,:,:),ALLOCATABLE   ::v_x,v_y,v_z
  ! Spectral velocity matrix (will be updated after every time step)
  !TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT

  CONTAINS

  SUBROUTINE init_global_variables
  ! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ! ------------
  ! CALL THIS SUBROUTINE TO:
  !       Initialize all the variables used in the code and
  ! are explained too. Only variables are initialized here.
  ! Arrays are initialized in  another SUBROUTINE.
  ! -------------
  ! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    IMPLICIT  NONE

    N_x         = 512
    N_y         = 512
    N_z         = 512
    N_ar        = (/ N_x, N_y, N_z /)
    N_min       = MINVAL( N_ar )
    N_max       = MAXVAL( N_ar )
    N3          = N_x * N_y * N_z
    ! Resolution of the cuboid

  	L_x         = ( N_x / N_min ) * two_pi
  	L_y         = ( N_y / N_min ) * two_pi
  	L_z         = ( N_z / N_min ) * two_pi
    ! Length of periodic cuboid

  	dx          = L_x / N_x
  	dy          = L_y / N_y
  	dz          = L_z / N_z
    ! Grid spacing - made to be equal in all direction

  	K_scale_x   = two_pi / L_x
  	K_scale_y   = two_pi / L_y
  	K_scale_z   = two_pi / L_z
    ! Scaling factor to be multiplied to the index to get the actual wavenumber

  	! ---------------------------
  	! MAX & MIN WAVENUMBERS ALLOWED
  	! ---------------------------
  	kMax_x      = + INT( N_x / 2 )
  	kMin_x      = + 0
  	kMax_y      = + INT( N_y / 2 ) - 1
  	kMin_y      = - INT( N_y / 2 )
  	kMax_z      = + INT( N_z / 2 ) - 1
  	kMin_z      = - INT( N_z / 2 )
    ! Maximum and Minimum wavemubers in the First Brillouin zone.

    dxdydz      = dx * dy * dz
    ! Grid volume

    vol         = L_x * L_y * L_z
    ! Volume of domain

  END

  SUBROUTINE init_global_arrays
  ! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ! ------------
  ! CALL THIS SUBROUTINE TO:
  !   This defines few arrays that do not evolve. k^2 matrix,k matrix, projection matrix,
  ! shell no matrix, count_modes_shell matrix.
  ! -------------
  ! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    IMPLICIT  NONE
    ! _________________________
    ! LOCAL VARIABLES
    ! !!!!!!!!!!!!!!!!!!!!!!!!!
    DOUBLE PRECISION::kx,ky,kz

    CALL allocate_operators
    ! Allocates the arrays declared here.

    DO j_x = kMin_x, kMax_x
  	DO j_y = kMin_y, kMax_y
  	DO j_z = kMin_z, kMax_z

      kx                    = K_scale_x * DBLE( j_x )
      ky                    = K_scale_y * DBLE( j_y )
      kz                    = K_scale_z * DBLE( j_z )

      k_x( j_x, j_y, j_z )  = kx
      k_y( j_x, j_y, j_z )  = ky
      k_z( j_x, j_y, j_z )  = kz
      ! Just the k component matrix storing its grid points.

    END DO
    END DO
    END DO

  END

  SUBROUTINE allocate_operators
  ! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ! ------------
  ! CALL this to allocate arrays which are constants basically, k2,truncator, shell no etc.,
  ! -------------
  ! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    IMPLICIT NONE
    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !  A  R  R  A  Y         A  L  L  O  C  A  T  I  O  N .
    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ALLOCATE( k_x( kMin_x       : kMax_x, kMin_y : kMax_y, kMin_z : kMax_z ) )
    ALLOCATE( k_y( kMin_x       : kMax_x, kMin_y : kMax_y, kMin_z : kMax_z ) )
    ALLOCATE( k_z( kMin_x       : kMax_x, kMin_y : kMax_y, kMin_z : kMax_z ) )

  END

  SUBROUTINE allocate_velocity
	! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	! ------------
	! CALL this to allocate arrays related to velocity(real and spectral) and it spectrum
	! -------------
	! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		IMPLICIT NONE
		!  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !  A  L  L  O  C  A  T  I  O  N    -   V  E  L  O  C  I  T  Y
    !  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ALLOCATE( u_x( 0 : N_x - 1, 0 : N_y - 1, 0 : N_z - 1 ) )
    ALLOCATE( u_y( 0 : N_x - 1, 0 : N_y - 1, 0 : N_z - 1 ) )
    ALLOCATE( u_z( 0 : N_x - 1, 0 : N_y - 1, 0 : N_z - 1 ) )
    ALLOCATE( str_xx( 0 : N_x - 1, 0 : N_y - 1, 0 : N_z - 1 ) )
    ALLOCATE( str_yy( 0 : N_x - 1, 0 : N_y - 1, 0 : N_z - 1 ) )
    ALLOCATE( str_zz( 0 : N_x - 1, 0 : N_y - 1, 0 : N_z - 1 ) )
    ALLOCATE( str_xy( 0 : N_x - 1, 0 : N_y - 1, 0 : N_z - 1 ) )
    ALLOCATE( str_yz( 0 : N_x - 1, 0 : N_y - 1, 0 : N_z - 1 ) )
    ALLOCATE( str_zx( 0 : N_x - 1, 0 : N_y - 1, 0 : N_z - 1 ) )
    ALLOCATE( v_x( kMin_x : kMax_x, kMin_y : kMax_y, kMin_z : kMax_z ) )
    ALLOCATE( v_y( kMin_x : kMax_x, kMin_y : kMax_y, kMin_z : kMax_z ) )
    ALLOCATE( v_z( kMin_x : kMax_x, kMin_y : kMax_y, kMin_z : kMax_z ) )
    ALLOCATE( dissipation_field( 0 : N_x - 1, 0 : N_y - 1, 0 : N_z - 1 ) )

	END

	SUBROUTINE deallocate_velocity
	! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	! ------------
	! CALL this to deallocate arrays
	! -------------
	! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		IMPLICIT NONE
		!  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		!  D  E  A  L  L  O  C  A  T  I  O  N
		!  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		DEALLOCATE( v_x, v_y, v_z )
		DEALLOCATE( u_x, u_y, u_z )
    DEALLOCATE( str_xx, str_yy, str_zz )
    DEALLOCATE( str_xy, str_yz, str_zx )
    DEALLOCATE( dissipation_field )

	END

  SUBROUTINE deallocate_operators
	! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	! ------------
	! CALL this to deallocate arrays
	! -------------
	! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		IMPLICIT NONE
		!  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		!  D  E  A  L  L  O  C  A  T  I  O  N
		!  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    DEALLOCATE( k_x, k_y, k_z )

	END

END MODULE system_basicvariables
