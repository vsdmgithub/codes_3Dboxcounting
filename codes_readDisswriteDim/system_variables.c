/*
* --------------------------------------------------------------
* -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
* CODE BY:
* --------   |         |   ---------        /\        |\      |
* |          |         |  |                /  \       | \     |
* |          |         |  |               /    \      |  \    |
* --------   |         |  |   ------|    /------\     |   \   |
*         |  |         |  |         |   /        \    |    \  |
*         |  |         |  |         |  /          \   |     \ |
* ---------   ----------  ----------  /            \  |      \|
* -------------------------------------------------------------
*
* TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
* FUNCTION CONTAINING ALL GLOBAL VARIABLES AND PARAMETERS
* _______________________________________________________________
* DATE   :- 29 JULY 2021
* AUTHOR :- SUGAN DURAI MURUGAN V
* IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
*
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

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*           To get input parameters for the Box-counting
* algorithm to work.
*============================================================== */
void getInputDetails()
{

  log2_N_data = 9 ;
  // Log of resolution

  N_data  = pow( 2, log2_N_data ) ;
  // resolution

  N3_data = pow( N_data, 3 );
  // No of grid points

  if (testMode == 1)
  {
    printf(" ============================ \n ");
    printf(" Size of data = %d \n",N3_data);
    printf(" ============================ \n ");
  }

}
/*==============================================================
* FUNCTION :
* ______________________________________________________________
*           To allocate array memory
*============================================================== */
void allocateDataArrays()
{

	data  = (double*)malloc( N3_data * sizeof(double) );

  if (testMode == 1)
  {
  	printf(" Data Allocated %ld KB \n ", N3_data * sizeof(double) / 1024 );
    printf(" ============================ \n ");
  }
}
/*==============================================================
* FUNCTION :
* ______________________________________________________________
*           To read the input data in 1D
*============================================================== */
void getInputData()
{
  FILE *fptr;
  char fileAddress[100];
  int i_data;

  strcpy(fileAddress , "../data_dissField/DSCODE/ds_Vk9.dat");
  // Address of input file

  if ((fptr = fopen(fileAddress,"r")) == NULL)
  {
    printf(" ============================ \n ");
    printf(" Error! opening file");
    printf(" ============================ \n ");
    errorStatus = 1;
    exit(1);
  }

  for( i_data = 0; i_data < N3_data; i_data++ ){
    fscanf(fptr, "%lf", data + i_data );
    if ( *(data + i_data) != *(data + i_data) ){
      errorStatus = 1;
      printf(" NaN Detected ");
      printf(" ============================ \n ");
    }
  }

  if (testMode == 1)
  {
  	printf(" Data READ successfully. \n ");
    printf(" ============================ \n ");
  }

}
/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To normalize the array by dividing by the average.
*============================================================== */
void normalizeData()
{
  int i_data;
  //double max_data;

  avg      = 0.0f;
  std      = 0.0f; 

  for( i_data = 0; i_data < N3_data ; i_data++ )
  {
    avg = avg + *( data + i_data ) ;
    std = std + (*( data + i_data )) * (*( data+ + i_data)) ;
  }

  avg = avg / (double) N3_data ;
  std = std / (double) N3_data ; 
  // Average  and Stand. dev of data

  if (testMode == 1)
  {
  	printf(" Average of the data = %12.8f \n ",avg );
  	printf(" St.Dev  of the data = %12.8f \n ",std );
    printf(" ============================ \n ");
  }

  //for( i_data = 0; i_data < N3_data ; i_data++ )
  // *( data + i_data ) = *( data + i_data ) / avg ;
  // *( data + i_data ) = *( data + i_data ) / max_data ;

}

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To formulate the details of boxes at different partitions.
*============================================================== */
void getBoxDetails()
{
  FILE *fptr;
  double a_Z,b_Z;
  int i_Zfn;

  N_Zfn      = 6 ;
  // Declaring the no of partitions

	noofBoxes    = (int*)malloc( N_Zfn * sizeof(int) );
	boxGrids     = (int*)malloc( N_Zfn * sizeof(int) );
	log_boxGrids = (double*)malloc( N_Zfn * sizeof(double) );

	fptr	       =	fopen("../data_boxDim/DSCODE/levels_of_partition.dat","w");

  a_Z = 3.0f / (double) ( N_Zfn - 1 );
  b_Z = 1.0f ;

  if (testMode == 1)
    printf(" Partition Details \n");

  for (i_Zfn = 0; i_Zfn < N_Zfn; i_Zfn++ )
  {
    *( noofBoxes + i_Zfn ) = (int) pow( 2.0f, log2_N_data - a_Z * i_Zfn - b_Z ) ;
    // No of boxes in this partition level

    *( boxGrids + i_Zfn )  = (int) pow( 2.0f,  a_Z * i_Zfn + b_Z ) ;
    // No of grid points in a box at this partition level

    *( log_boxGrids + i_Zfn ) = log( (double) *( boxGrids + i_Zfn ) );
   // Log of box size

    fprintf(fptr,"%3d %6d %6d \n",i_Zfn + 1, *( noofBoxes + i_Zfn ), *( boxGrids + i_Zfn ) );

    if (testMode == 1)
    	printf(" Level = %d ; No of boxes = %d ; Grids in a Box : %d \n ", i_Zfn + 1, *( noofBoxes + i_Zfn ), *( boxGrids + i_Zfn ) );
  }
  fclose(fptr);

  if (testMode == 1)
    printf(" ============================ \n ");
}

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To initialize the list of moment expons.
*============================================================== */
void getMomentList()
{
  FILE *fptr;
  int i_qMom;

  N_qMom    = 21 ;
  // No of moments to be calculated

  fptr    =	fopen("../data_boxDim/DSCODE/moment_details.dat","w");
  qMom    = (double*)malloc( N_qMom * sizeof(double) );
  dataMom = (double*)malloc( ( N_qMom * N_Zfn ) * sizeof(double) );

  double qMom_ar[21]={-4.0,-3.0,-2.5,-2.2,-2.0,-1.8,-1.5,-1.2,-1.0,-0.8,-0.5,0.5,0.8,1.2,1.5,1.8,2.0,2.2,2.5,3.0,4.0};

  for( i_qMom = 0; i_qMom < N_qMom; i_qMom++ )
  {
    *( qMom + i_qMom ) = qMom_ar[i_qMom] ; 
    //*( qMom + i_qMom ) = -1.1f + 0.20f * ( (double) ( i_qMom ) );
   
    // Value of the moment will be calculated
    fprintf(fptr,"%6.4f \n",*( qMom + i_qMom ) );
  }
}

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To find the moments
*============================================================== */
void getPartitionFunction()
{
  FILE *fptr;
  int N_box, I_grid;
  int N3_box;
  int i_x,i_y,i_z;
  int box_x,box_y,box_z;
  int i_box,i_data;
  int i_qMom;
  int i_Zfn;
  int N_dataAdj;
  int count_box;

  i_Zfn  = 0;

  fptr	     =	fopen("../data_boxDim/DSCODE/partition_function.dat","w");

  if (testMode == 1)
    printf(" Partition Function \n ");

  while( i_Zfn < N_Zfn ){
  // For each partition level, the moments are calculated.

    I_grid      = *( boxGrids + i_Zfn ) ;
    // total no of grids in a box at this level

    fprintf(fptr," %30.15f ", *( log_boxGrids + i_Zfn ) ) ;
    // Printing the log of box size, proportionality

    N_box     = *( noofBoxes + i_Zfn ) ;
    N3_box    = pow( N_box, 3 );
    // Total no of boxes at this level

    N_dataAdj = I_grid * N_box ;
    // Adjusted data size, removing the extra padding at this level.

    dataBox   = (double*)malloc( N3_box * sizeof(double) );
    // Allocating box data size

    for( i_box = 0; i_box < N3_box; i_box++ )
      *( dataBox + i_box ) = 0.0f;

    for( i_x = 0; i_x < N_dataAdj; i_x++ ) {
    for( i_y = 0; i_y < N_dataAdj; i_y++ ) {
    for( i_z = 0; i_z < N_dataAdj; i_z++ ) {

      i_data = ( i_x * N_data * N_data + i_y * N_data + i_z ) ;
      // Linear address of the data

      box_x = (int) ( i_x / I_grid ) ;
      box_y = (int) ( i_y / I_grid ) ;
      box_z = (int) ( i_z / I_grid ) ;
      // Finding the x,y,z location of the box_x

      i_box = ( box_x * N_box * N_box + box_y * N_box + box_z ) ;
      // Linear address of the box location

      *( dataBox + i_box ) = *( dataBox + i_box ) + ( *( data + i_data ) );
      // Adding the grid data to corresponding box data

    }
    }
    }

    i_qMom = 0;

    while( i_qMom < N_qMom ) {
// At 'r' level, finding all moments
      if( *( qMom + i_qMom ) < 0.0f ) 
// Special for negative moments alone, to avoid NaN
 	{
      count_box = 0;	
      for( i_box = 0; i_box < N3_box; i_box++ )
	{
	if ( *(dataBox + i_box) > 0.0f ) // Taking only non-zero value statistics
	//if ( *(dataBox + i_box) != 0.0f )
		{
 		count_box = count_box + 1 ;
		*( dataMom + i_Zfn * N_qMom + i_qMom ) = *( dataMom + i_Zfn * N_qMom + i_qMom ) + pow( *( dataBox + i_box ) , *( qMom + i_qMom ) ) ;
		// For each moment, calculating the partition function at this level
		}
        }

      *( dataMom + i_Zfn * N_qMom + i_qMom ) = log( *( dataMom + i_Zfn * N_qMom + i_qMom ) / (double) N3_box ) ;
      fprintf(fptr," %30.15f ",*( dataMom + i_Zfn * N_qMom + i_qMom ) ) ;
      // Printing each moment (log) at this partition level

      if (testMode == 1)
      	printf(" %10.8f ", *( dataMom + i_Zfn * N_qMom + i_qMom ) );
	}	
      else // For positive moments
 	{
      for( i_box = 0; i_box < N3_box; i_box++ )
	{
		*( dataMom + i_Zfn * N_qMom + i_qMom ) = *( dataMom + i_Zfn * N_qMom + i_qMom ) + pow( *( dataBox + i_box ) , *( qMom + i_qMom ) ) ;
		// For each moment, calculating the partition function at this level
		
        }

      *( dataMom + i_Zfn * N_qMom + i_qMom ) = log( *( dataMom + i_Zfn * N_qMom + i_qMom ) / (double) N3_box ) ;
      fprintf(fptr," %30.15f ",*( dataMom + i_Zfn * N_qMom + i_qMom ) ) ;
      // Printing each moment (log) at this partition level

      if (testMode == 1)
      	printf(" %10.8f ", *( dataMom + i_Zfn * N_qMom + i_qMom ) );
        }

      i_qMom = i_qMom + 1 ;
    }

    fprintf(fptr," \n ") ;
    // this partition level calculation is completed, over to next partition level

    if (testMode == 1)
    	printf(" \n ");

    free(dataBox) ;
    // Freeing box data

    i_Zfn = i_Zfn + 1 ;
  }
	fclose(fptr);

  if (testMode == 1)
      printf("================================= \n ");

}

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To find the moment exponents using partition function.
*============================================================== */
void getExponents()
{
  FILE *fptr;
  double sumX2,sumXY;
  double sumX,sumY;
  int i_Zfn;
  int i_qMom;

  dataExp = (double*)malloc( N_qMom * sizeof(double) );

  fptr	     =	fopen("../data_boxDim/DSCODE/exponents.dat","w");

  if (testMode == 1)
  	printf(" Exponents \n ") ;

  for( i_qMom=0; i_qMom < N_qMom; i_qMom++ )
  {
    sumX2 = 0.0f;
    sumXY = 0.0f;
    sumY = 0.0f;
    sumX = 0.0f;

    for(i_Zfn=0; i_Zfn < N_Zfn; i_Zfn++ )
    {
    sumX = sumX + *( log_boxGrids + i_Zfn );
    sumY = sumY + *( dataMom + i_Zfn * N_qMom + i_qMom );
    sumX2 = sumX2 + pow( *( log_boxGrids + i_Zfn ), 2.0f );
    sumXY = sumXY + ( *( log_boxGrids + i_Zfn ) ) * ( *( dataMom + i_Zfn * N_qMom + i_qMom ) ) ;
    }

    *( dataExp + i_qMom ) = ( N_Zfn * sumXY - sumX * sumY ) / ( N_Zfn * sumX2 - pow( sumX, 2.0f ) );
    // Slope of the moments in log scale gives the exponent.

    fprintf(fptr," %6.4f %30.15f \n",*( qMom + i_qMom ), *( dataExp + i_qMom ) ) ;

    if (testMode == 1)
    	printf(" %6.4f %10.8f \n ",*( qMom + i_qMom ), *( dataExp + i_qMom ) );
  }

	fclose(fptr);

  if (testMode == 1)
    printf("================================= \n ");
}
