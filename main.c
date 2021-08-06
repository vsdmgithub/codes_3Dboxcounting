/*
* IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
* PROGRAM :- TO FIND THE FRACTAL DIMENSION OF GIVEN DATA
*         	 USING BOX-COUNTING ALGORITHM.
* _________________________________________________________________
* REF    :- Efficient box-counting determination of generalized
*   			  fractal dimensions, A.Block et.al.,(1990)
* DATE   :- 29 JULY 2021
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
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{

  testMode = 1;
  // testMode = 0;

  getInputSize();

  allocateArray();

  getInputData();

  sortArray( 0, N_data );

  normalizeArray();

  getBoxDetails();

  getMomentList();

  getPartitionFunction();

  free( box_data );
  free( dummy );
  free( data );

	return 0;
}
