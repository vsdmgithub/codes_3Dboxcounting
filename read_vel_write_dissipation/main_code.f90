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

PROGRAM get_dissipation
! INFO - START  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
! ------------
! All the work is done in the modules. Calling a few would finish
! the code.
! -------------
! INFO - END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

! [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
!  MODULES
!  ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
USE system_readVelwriteDiss
USE system_timer

	IMPLICIT NONE
	! _________________________
	! LOCAL VARIABLES
	! !!!!!!!!!!!!!!!!!!!!!!!!!

  CALL init_global_variables
	! REF-> <<< system_variables >>>

	CALL init_global_arrays
	CALL allocate_velocity
	! REF-> <<< system_variables >>>

	CALL start_run_timer
	! Clocks the date and time - PROGRAM STARTS
	! REF-> <<< system_timer >>>

  CALL IC_from_file_real

  CALL init_fft_size( N_x, N_y, N_z )

	CALL compute_strain_tensor

	CALL compute_dissipation_field

	CALL write_dissipation_field

	CALL end_run_timer

	CALL deallocate_velocity
	CALL deallocate_operators

END PROGRAM get_dissipation
