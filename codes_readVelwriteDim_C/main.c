/*
* IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
* PROGRAM :- TO FIND THE FRACTAL DIMENSION OF GIVEN DATA
*         	 USING BOX-COUNTING ALGORITHM.
* _________________________________________________________________
* REF    :- Standard moment method.
* DATE   :- 12 AUGUST 2021
* AUTHOR :- SUGAN DURAI MURUGAN V
* _________________________________________________________________
* IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
*/

/*>>>>>>>>>>>>>>>>>>
*      HEADERS
* <<<<<<<<<<<<<<<<< */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fftw3.h>
#include "system_functions.h"

extern void readVelocityFortran (double *u_x, double *u_y, double *u_z);

int main()
{
  // testMode = 1;
  testMode = 0;
  errorStatus = 0;

  getInputDetails(); // <<< system_functions.c  >>>
  allocateRealVelocity(); // <<< system_functions.c  >>>
  readVelocityFortran(u_x,u_y,u_z); // <<< system_readVelocityFortran.f90 >>>
  computeDissipationField(); // <<< system_functions.c  >>>

  if ( errorStatus != 1 ) {
    computePdfDissipationField(); // <<< system_functions.c >>>
    getBoxDetails(); // <<< system_functions.c >>>
    getMomentList(); // <<< system_functions.c >>>
    computePartitionFunction(); // <<< system_functions.c >>>
    computeExponents(); // <<< system_functions.c >>>
    freePointerMemory(); // <<< system_functions.c >>>
  }
	return 0;
}
