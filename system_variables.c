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
void getInputSize()
{
  int N_grid;
  int eDim;
  N_grid    = 96 ;
  eDim      = 3 ;
  N_data = pow( N_grid, eDim );

  printf(" ============================ \n ");
	printf(" Size of data = %d \n",N_data);
  printf(" ============================ \n ");

}
/*==============================================================
* FUNCTION :
* ______________________________________________________________
*           To allocate array memory
*============================================================== */
void allocateArray()
{

	data = (double*)malloc( N_data * sizeof(double) );
	dummy     = (double*)malloc( ( N_data - 1 ) * sizeof(double) );

  printf(" ============================ \n ");
	printf(" Data Allocated %ld KB \n ", N_data * sizeof(double) / 1024 );
  printf(" ============================ \n ");

}
/*==============================================================
* FUNCTION :
* ______________________________________________________________
*           To read the input data in 1D
*============================================================== */
void getInputData()
{
  FILE *fptr;

  if ((fptr = fopen("../ds_N96.dat","r")) == NULL)
  {
    printf(" ============================ \n ");
    printf(" Error! opening file");
    printf(" ============================ \n ");
    exit(1);
  }

  for( int i_data = 0; i_data < N_data; i_data++ )
  {
    fscanf(fptr, "%lf", data + i_data );
    *( data + i_data ) = fabs( *( data + i_data ) ) ;
  }

  printf(" ============================ \n ");
	printf(" Data READ successfully. \n ");
  printf(" ============================ \n ");

}
/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To sort array using Merge sort, uses order of N * log(N)
* operations.
*============================================================== */
void sortArray(int low, int hig )
{
  int mid;

  if ( low < hig )
  {
    mid = ( low + hig ) / 2;
    sortArray( low, mid );
    sortArray( mid + 1, hig );
    mergingArray( low, mid, hig );
  }
  else
  {
    return;
  }
}
void mergingArray( int low, int mid, int hig )
{
  int l1, l2, loc;
  for(l1 = low, l2 = mid + 1, loc = low; l1 <= mid && l2 <= hig; loc++)
  {
    if(*( data + l1 ) <= *( data + l2) )
      *( dummy + loc ) = *( data + l1++ );
    else
      *( dummy + loc ) = *( data + l2++ );
  }

  while(l1 <= mid)
    *( dummy + loc++ ) = *( data + l1++ );

  while(l2 <= hig)
    *( dummy + loc++ ) = *( data + l2++ );

  for(loc = low; loc <= hig; loc++)
    *( data + loc ) = *( dummy + loc );
}

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To normalize the array to range between (0,1). Also to find
*the smallest difference.
*============================================================== */
void normalizeArray()
{
  double dataMax;
  double dx;

  printf(" First and Last (Before Normalization) %.2e,%.2e",*data,*(data+N_data-1));
  dataMax = *( data + N_data - 1 ) ;

  for( i_data = 0; i_data < N_data - 1; i_data++ )
  {
    *( data + i_data ) = *( data + i_data ) / dataMax ;
    *( dummy + i_data ) = fabs( *( data + i_data + 1 ) - *( data + i_data ) ) ;
  }
  *( data + i_data ) = *( data + i_data ) / dataMax ;

  printf(" First and Last (After Normalization) %.2e,%.2e",*data,*(data+N_data-1));
  dataDMin = findMin(dummy, ( N_data - 1 ) ) ;

  printf(" ============================ \n ");
	printf(" Existing diff. in data = %.2e \n ", dataDMin );

  dx = 1.0f / ( (double) N_data ) ;
  printf(" Grid diff. in data = %.2e \n ", dx );

  if ( dataDMin < dx )
    dataDMin = dx;

  printf(" ============================ \n ");
	printf(" Minimum diff. in data = %.2e \n ", dataDMin );
  printf(" ============================ \n ");

}
double findMin( double *arr, int siz )
{
  double minVal;
  minVal = *arr;
  for( int y = 1; y < siz; y++ )
  {
    if ( *(arr + y) < minVal )
      minVal = *( arr + y );
  }

  return minVal;
}

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To formulate the details of boxes at different partitions.
*============================================================== */
void getBoxDetails()
{
  int i_pFun,noBox;
  double lenBox;
  double expon;

  N_pFun = 12 ;

  printf(" ============================ \n ");
  for ( i_pFun = 1; i_pFun <= N_pFun; i_pFun++ )
  {
    expon = - ( (double) i_pFun ) / ( (double) N_pFun ) ;
    noBox  = (int) ( pow( dataDMin, expon ) ) ;
    lenBox  = 1.0f / ( (double) noBox );
    printf(" At i_pFun = %d, no of Boxes = %d with size = %.8f \n",i_pFun,noBox,lenBox ) ;
  }
  printf(" ============================ \n ");

}

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To initialize the list of moment expons.
*============================================================== */
void getMomentExp()
{
  N_qMom    = 10;
  pFun = (double*)malloc( N_qMom * sizeof(double) );
  qMom     = (double*)malloc( N_qMom * sizeof(double) );
  for( int i_qMom = 0; i_qMom < N_qMom; i_qMom++ )
  {
    *( qMom + i_qMom ) = 0.4f * ( (double) ( i_qMom + 1 ) );
  }
}

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To find the moments
*============================================================== */
void getPartitionFunction()
{
  int i_pFun,noBox;
  int i_data;
  int boxCount;
  double expon;
  int i_box;
  double io_xVal,y_value;
  FILE *fptr, *fptr2;

	fptr	=	fopen("moment_q.dat","w");
	fptr2 =	fopen("box_dataData.dat","w");

	box_data = (int*)malloc( N_data * sizeof(int) );

  for ( i_pFun = 1; i_pFun <= N_pFun; i_pFun++ )
  {
    expon = - ( (double) i_pFun ) / ( (double) N_pFun ) ;
    noBox  = (int) ( pow( dataDMin, expon ) ) ;

    io_xVal  = - log( (double) noBox ) ;


    for( i_data = 0; i_data < N_data; i_data++ )
    {
      *( box_data + i_data ) = (int) ( *( data + i_data ) * ( (double) noBox ) ) ;
      if (i_pFun == 4)
        fprintf(fptr2,"%d \n", *(box_data + i_data) );
    }

    i_data      = 1 ;
    i_box    = *box_data ;
    for( int i_qMom = 0; i_qMom < N_qMom; i_qMom++ )
      *( pFun + i_qMom )   = 0.0f ;

    boxCount = 1 ;

    while( i_data < N_data )
    {
      if ( *( box_data + i_data ) != i_box )
      {
        for( int i_qMom = 0; i_qMom < N_qMom; i_qMom++ )
          *( pFun + i_qMom )  = *( pFun + i_qMom ) + pow( (double) boxCount / (double) N_data, *( qMom + i_qMom ) );
        i_box    = *( box_data + i_data );
        boxCount = 1;
      }
      else
      {
        ++boxCount;
      }
      ++i_data;
    }

    fprintf(fptr,"%.8f",io_xVal );
    for( int i_qMom = 0; i_qMom < N_qMom; i_qMom++ )
    {
      y_value =  log( *( pFun + i_qMom ) + pow( (double) boxCount / (double) N_data, *( qMom + i_qMom ) ) ) / ( *( qMom + i_qMom ) - 1 ) ;
      fprintf(fptr,"%.8f ",y_value );
    }
    fprintf(fptr,"\n ");
  }

	fclose(fptr);
	fclose(fptr2);

}
