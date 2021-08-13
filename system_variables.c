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

  log2_N_data = 7 ;
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

  strcpy(fileAddress , "../ds_N128.dat");
  // Address of input file

  if ((fptr = fopen(fileAddress,"r")) == NULL)
  {
    printf(" ============================ \n ");
    printf(" Error! opening file");
    printf(" ============================ \n ");
    errorStatus = 1;
    exit(1);
  }

  for( int i_data = 0; i_data < N3_data; i_data++ ){
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
  double avg;
  int i_data;

  avg = 0.0f;

  for( i_data = 0; i_data < N3_data ; i_data++ )
  {
    avg = avg + *( data + i_data ) ;
  }

  avg = avg / (double) N3_data ;
  // Average data

  if (testMode == 1)
  {
  	printf(" Average of the data = %30.15f \n ",avg );
    printf(" ============================ \n ");
  }

  for( i_data = 0; i_data < N3_data ; i_data++ )
    *( data + i_data ) = *( data + i_data ) / avg ;

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

  N_Zfn      = 4 ;
  // Declaring the no of partitions

	noofBoxes  = (int*)malloc( N_Zfn * sizeof(int) );
	boxGrids   = (int*)malloc( N_Zfn * sizeof(int) );

	fptr	     =	fopen("partition_details.dat","w");

  // Minimum size of box = dx * 2^2
  // Maximum size of box = dx * 2^(p-2)

  a_Z = (double) (log2_N_data - 4) / ( N_Zfn - 4 );
  b_Z = 2.0f - a_Z ;

  for (int i_Zfn = 0; i_Zfn < N_Zfn; i_Zfn++ )
  {
    *( noofBoxes + i_Zfn ) = (int) pow( 2.0f, log2_N_data - a_Z * ( i_Zfn + 1 ) - b_Z ) ;
    // No of boxes in this partition level

    *( boxGrids + i_Zfn )  = (int) pow( 2,  a_Z * ( i_Zfn + 1 ) + b_Z ) ;
    // No of grid points in a box at this partition level

    fprintf(fptr,"%3d %6d %6d \n",i_Zfn + 1, *( noofBoxes + i_Zfn ), *( boxGrids + i_Zfn ) );
    if (testMode == 1)
    	printf(" Level = %d ; No of boxes = %d ; Grids in a Box : %d \n ", i_Zfn + 1, *( noofBoxes + i_Zfn ), *( boxGrids + i_Zfn ) );
  }
  fclose(fptr);

}

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To initialize the list of moment expons.
*============================================================== */
void getMomentList()
{
  FILE *fptr;

  N_qMom    = 5 ;
  // No of moments to be calculated

	fptr	     =	fopen("moment_details.dat","w");
  qMom    = (double*)malloc( N_qMom * sizeof(double) );
  dataMom = (double*)malloc( N_qMom * sizeof(double) );

  for( int i_qMom = 0; i_qMom < N_qMom; i_qMom++ )
  {
    *( qMom + i_qMom ) = 0.4f * ( (double) ( i_qMom + 1 ) );
    // Value of exponent, that the moment will be calculated
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
  int N3_box, I3_grid;
  int i_x,i_y,i_z;
  int box_x,box_y,box_z;
  int i_box,i_data;
  int i_qMom;
  int i_Zfn;
  double N3_box_inv;
  double I3_grid_inv;

  i_Zfn  = 0;

  fptr	     =	fopen("partition_function.dat","w");

  while( i_Zfn < N_Zfn ){
  // For each partition level, the moments are calculated.

    fprintf(fptr," %2d ",i_Zfn + 1) ;
    // Printing the log of box size, proportionality

    I_grid = *( boxGrids + i_Zfn ) ;
    I3_grid= pow( I_grid, 3 ) ;
    I3_grid_inv = 1.0f / (double) I3_grid ;
    // total no of grids in a box at this level

    N_box  = *( noofBoxes + i_Zfn )  ;
    N3_box = pow( N_box, 3 );
    N3_box_inv = 1.0f / (double) N3_box ;
    // Total no of boxes at this level

    dataBox = (double*)malloc( N3_box * sizeof(double) );
    // Allocating box data size

    // for( i_box = 0; i_box < N3_box; i_box++ )
      // *( dataBox + i_box ) = 0.0f;

    for( i_x = 0; i_x < N_data; i_x++ ) {
    for( i_y = 0; i_y < N_data; i_y++ ) {
    for( i_z = 0; i_z < N_data; i_z++ ) {

      i_data = ( i_x * N_data * N_data + i_y * N_data + i_z ) ;
      // Linear address of the data

      box_x = (int) ( i_x / I_grid ) ;
      box_y = (int) ( i_y / I_grid ) ;
      box_z = (int) ( i_z / I_grid ) ;
      // Finding the x,y,z location of the box_x

      i_box = ( box_x * N_box * N_box + box_y * N_box + box_z ) ;
      // Linear address of the box location

      *( dataBox + i_box ) = *( dataBox + i_box ) + I3_grid_inv * ( *( data + i_data ) );
      // Adding the grid data to corresponding box data

    }
    }
    }

    i_qMom = 0;

    while( i_qMom < N_qMom ) {

      *( dataMom + i_qMom ) = 0.0f ;
      // Reseting the parition function value for each moment at this le  vel

      for( i_box = 0; i_box < N3_box; i_box++ )
        *( dataMom + i_qMom ) = *( dataMom + i_qMom ) + N3_box_inv * pow( *( dataBox + i_box ) , *( qMom + i_qMom ) ) ;
        // For each moment, calculating the partition function at this level

      fprintf(fptr," %30.15f ",log( *( dataMom + i_qMom ) ) ) ;
      // Printing each moment at this partition level

      i_qMom = i_qMom + 1 ;
    }

    fprintf(fptr," \n ") ;
    // this partition level calculation is completed, over to next partition level

    free(dataBox) ;
    // Freeing box data

    i_Zfn = i_Zfn + 1 ;
  }
	fclose(fptr);

}
