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
#include "system_variables.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{

  testMode = 0;
  // testMode = 0;

  errorStatus = 0;
  getInputDetails();

  allocateDataArrays();

  getInputData();

  if ( errorStatus != 1 ){

    normalizeData();

    getBoxDetails();

    getMomentList();

    getPartitionFunction();

    getExponents();
  }

    free( data );

	return 0;
}
