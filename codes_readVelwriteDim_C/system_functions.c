/*
* -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
* CODE BY:
* --------   |         |   ---------        /\        |\      |
* |          |         |  |                /  \       | \     |
* |          |         |  |               /    \      |  \    |
* --------   |         |  |   ------|    /------\     |   \   |
*         |  |         |  |         |   /        \    |    \  |
*         |  |         |  |         |  /          \   |     \ |
* ---------   ----------  ----------  /            \  |      \|
*
* TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
* ______________________________________________________________
* DATE   :- 01 SEPTEMBER 2021
* AUTHOR :- SUGAN DURAI MURUGAN V
* IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
*/
/*>>>>>>>>>>>>>>>>>>
*      HEADERS
* <<<<<<<<<<<<<<<<< */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>
#include <time.h>
#include <fftw3.h>
#include "system_functions.h"

/*==============================================================
* FUNCTION : To calculate FFT forward.
*============================================================== */
void fftR2C(double *in,fftw_complex *out)
{
  fftw_plan r2c;
  r2c = fftw_plan_dft_r2c_3d(N,N,N,in,out,FFTW_ESTIMATE);
  fftw_execute(r2c);
  fftw_destroy_plan(r2c);
}

/*==============================================================
* FUNCTION : To calculate FFT backward
*============================================================== */
void fftC2R(fftw_complex *in,double *out)
{
  fftw_plan c2r;
  c2r = fftw_plan_dft_c2r_3d(N,N,N,in,out,FFTW_ESTIMATE);
  fftw_execute(c2r);
  fftw_destroy_plan(c2r);
}

/*==============================================================
* FUNCTION : To safely allocate memory to array with error message
*============================================================== */
void *safe_malloc(size_t n)
{
  void *p = malloc(n);
  if (p == NULL) {
    fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", n);
    abort();
  }
  return p;
}

/*==============================================================
* FUNCTION :To get input parameters
*============================================================== */
void getInputDetails()
{
  log2_N = 6 ; // Log of resolution
  N      = pow( 2, log2_N ) ; // resolution
  Nh     =(int) N/2 + 1; // Half of N
  N3     = pow( N, 3 ); // No of grid points
  N3_d   = (double)N3; // Double valued normalization factor
  outLoc = "../../results/";

  if (testMode == 1) {
    printf(" ============================ \n ");
    printf(" Size of data ~ 10^(%d) \n",(int)log10(N3));
    printf(" ============================ \n ");
  }
}

/*==============================================================
* FUNCTION : To allocate memory to real velocity pointer
*============================================================== */
void allocateRealVelocity()
{
  // Allocating the velocity
	u_x  = (double*)safe_malloc( N3 * sizeof(double) );
	u_y  = (double*)safe_malloc( N3 * sizeof(double) );
	u_z  = (double*)safe_malloc( N3 * sizeof(double) );

  if (testMode == 1) {
  	printf(" Data Allocated for velocity ~ %ld MB \n ", 3 * N3 * sizeof(double) / (1024*1024) );
    printf(" ============================ \n ");
  }
}

/*==============================================================
* FUNCTION : To compute the dataipation field
*============================================================== */
void computeDissipationField()
{
  int kx,ky,kz;
  int ix,iy,iz;
  int Bkx,Bky;
  int ind;
  fftw_complex *dv;
  fftw_complex *v_x;
  fftw_complex *v_y;
  fftw_complex *v_z;
  double *du;

	v_x  = (fftw_complex*)fftw_malloc( sizeof(fftw_complex)* (N*N*Nh) );
	v_y  = (fftw_complex*)fftw_malloc( sizeof(fftw_complex)* (N*N*Nh) );
	v_z  = (fftw_complex*)fftw_malloc( sizeof(fftw_complex)* (N*N*Nh) ); // Allocating for spectral velocity
  if (( v_x == NULL ) || (v_y == NULL) || (v_z == NULL)) {
    fprintf(stderr, "Fatal: failed to allocate memory! \n");
    exit(1);
  }

  fftR2C(u_x,v_x);
  free(u_x);

  fftR2C(u_y,v_y);
  free(u_y);

  fftR2C(u_z,v_z);
  free(u_z);
  // releasing memory

	dv  = (fftw_complex*)fftw_malloc( sizeof(fftw_complex)* (N*N*Nh) ); // Allocating memory for spectral strain component
  if ( dv == NULL ) {
    fprintf(stderr, "Fatal: failed to allocate memory! \n");
    exit(1);
  }

	data  = (double*)safe_malloc( N3 * sizeof(double) );
	du    = (double*)safe_malloc( N3 * sizeof(double) ); // Allocating memory for the dataipation field and strain component

  for(kx=0;kx<N ;kx++) {
  for(ky=0;ky<N ;ky++) {
  for(kz=0;kz<Nh;kz++) {
    ind = kx*N*Nh+ky*Nh+kz;
    /*=================== TRIGONOMETRIC INTERPOLATION =====================*/
    Bkx = (kx > Nh)? kx - N: kx;
    /*=============== STRAIN TENSOR - XX ========================*/
    *(dv+ind) = I * Bkx * (*(v_x+ind)) / N3_d;
  }}}

  fftC2R(dv,du);

  for(ix=0;ix<N;ix++) {
  for(iy=0;iy<N;iy++) {
  for(iz=0;iz<N;iz++)
    /*=============== DISSIPATION FIELD CONTRIBUTION - XX ================*/
    *(data + ix*N*N + iy*N + iz) = pow(*(du + ix*N*N + iy*N + iz),2) ;
  }}

  for(kx=0;kx<N ;kx++) {
  for(ky=0;ky<N ;ky++) {
  for(kz=0;kz<Nh;kz++) {
    ind = kx*N*Nh+ky*Nh+kz;
    /*=================== TRIGONOMETRIC INTERPOLATION =====================*/
    Bky = (ky > Nh)? ky - N: ky;
    /*=============== STRAIN TENSOR - YY ========================*/
    *(dv+ind) = I * Bky * (*(v_y+ind)) / N3_d;
  }}}

  fftC2R(dv,du);

  for(ix=0;ix<N;ix++) {
  for(iy=0;iy<N;iy++) {
  for(iz=0;iz<N;iz++)
    /*=============== DISSIPATION FIELD CONTRIBUTION - YY ================*/
    *(data + ix*N*N + iy*N + iz) += pow(*(du + ix*N*N + iy*N + iz),2) ;
  }}

  for(kx=0;kx<N ;kx++) {
  for(ky=0;ky<N ;ky++) {
  for(kz=0;kz<Nh;kz++) {
    ind = kx*N*Nh+ky*Nh+kz;
    /*=============== STRAIN TENSOR - ZZ ========================*/
    *(dv+ind) = I * kz * (*(v_z+ind)) / N3_d;
  }}}

  fftC2R(dv,du);

  for(ix=0;ix<N;ix++) {
  for(iy=0;iy<N;iy++) {
  for(iz=0;iz<N;iz++)
    /*=============== DISSIPATION FIELD CONTRIBUTION - ZZ ================*/
    *(data + ix*N*N + iy*N + iz) += pow(*(du + ix*N*N + iy*N + iz),2) ;
  }}

  for(kx=0;kx<N ;kx++) {
  for(ky=0;ky<N ;ky++) {
  for(kz=0;kz<Nh;kz++) {
    ind = kx*N*Nh+ky*Nh+kz;
    /*=================== TRIGONOMETRIC INTERPOLATION =====================*/
    Bky = (ky > Nh)? ky - N: ky;
    Bkx = (kx > Nh)? kx - N: kx;
    /*=============== STRAIN TENSOR - XY ========================*/
    *(dv+ind) = I * 0.5f * ( Bkx * (*(v_y+ind)) + Bky * (*(v_x+ind)) ) / N3_d ;
  }}}

  fftC2R(dv,du);

  for(ix=0;ix<N;ix++) {
  for(iy=0;iy<N;iy++) {
  for(iz=0;iz<N;iz++)
    /*=============== DISSIPATION FIELD CONTRIBUTION - XY ================*/
    *(data + ix*N*N + iy*N + iz) += 2.0f * pow(*(du + ix*N*N + iy*N + iz),2) ;
  }}

  for(kx=0;kx<N ;kx++) {
  for(ky=0;ky<N ;ky++) {
  for(kz=0;kz<Nh;kz++) {
    ind = kx*N*Nh+ky*Nh+kz;
    /*=================== TRIGONOMETRIC INTERPOLATION =====================*/
    Bky = (ky > Nh)? ky - N: ky;
    /*=============== STRAIN TENSOR - YZ ========================*/
    *(dv+ind) = I * 0.5f * ( Bky * (*(v_z+ind)) + kz * (*(v_y+ind)) ) / N3_d ;
  }}}

  fftC2R(dv,du);

  for(ix=0;ix<N;ix++) {
  for(iy=0;iy<N;iy++) {
  for(iz=0;iz<N;iz++)
    /*=============== DISSIPATION FIELD CONTRIBUTION - YZ ================*/
    *(data + ix*N*N + iy*N + iz) += 2.0f * pow(*(du + ix*N*N + iy*N + iz),2) ;
  }}

  for(kx=0;kx<N ;kx++) {
  for(ky=0;ky<N ;ky++) {
  for(kz=0;kz<Nh;kz++) {
    ind = kx*N*Nh+ky*Nh+kz;
    /*=================== TRIGONOMETRIC INTERPOLATION =====================*/
    Bkx = (kx > Nh)? kx - N: kx;
    /*=============== STRAIN TENSOR - ZX ========================*/
    *(dv+ind) = I * 0.5f * ( kz * (*(v_x+ind)) + Bkx * (*(v_z+ind)) ) / N3_d ;
  }}}

  fftC2R(dv,du);

  for(ix=0;ix<N;ix++) {
  for(iy=0;iy<N;iy++) {
  for(iz=0;iz<N;iz++)
    /*=============== DISSIPATION FIELD CONTRIBUTION - ZX ================*/
    *(data + ix*N*N + iy*N + iz) += 2.0f * pow(*(du + ix*N*N + iy*N + iz),2) ;
  }}
  if (testMode == 1)
	printf("  Dissipation field computed \n ============================ \n ");

  fftw_free(dv);
  free(du);
  fftw_free(v_x);
  fftw_free(v_y);
  fftw_free(v_z);
  // releasing memory
}

/*==============================================================
* FUNCTION :To find the average, normalize, PDF,
* then histogram, finally to PDF of data.
*============================================================== */
void swap(double *a, double *b)
{
  double t = *a;
  *a = *b;
  *b = t;
}
int partition (double arr[], int low, int high)
{
  double pivot = arr[high]; // pivot
  int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

  for (int j = low; j <= high - 1; j++)
  {
    // If current element is smaller than the pivot
    if (arr[j] < pivot)
    {
      i++; // increment index of smaller element
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}
void quickSort(double arr[], int low, int high)
{
  if (low < high)
  {
    /* pi is partitioning index, arr[p] is now
    at right place */
    int pi = partition(arr, low, high);

    // Separately sort elements before
    // partition and after partition
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}
void computePdfDissipationField()
{
  double arr[N3];
  double avg,max,min;
  int ind;
  int bin,binCurrent;
  int noBins = 100;
  double binVal[noBins];
  double binPdf[noBins];
  double binSize;
  int binFreq[noBins];
  char *fileName="pdf_dissipation.dat";
  FILE *fptr;

  char *fileAdd = (char *) malloc( 1+ sizeof(char*) *(strlen(outLoc) + strlen(fileName)));
  strcpy(fileAdd,outLoc);
  strcat(fileAdd,fileName);

	fptr	  =	fopen(fileAdd,"w");
  if(fptr == NULL) {
    printf("Error!");
    exit(1);
   }
  avg = 0.0f;

  for( ind=0;ind<N3;ind++ ){
    avg += *( data + ind );
    if(*(data+ind)> 1E18)
    printf("Value too high detected : %f \n",*(data+ind));
  }
  avg /= N3_d; // Average

  for(ind=0;ind<N3;ind++){
    *(data + ind) /= avg ;
    arr[ind]=*(data+ind);
  }

  quickSort(arr,0,N3-1);
  min = arr[0];
  max = arr[N3-1];

  if (testMode == 1) {
  	printf(" Data sorted: \n ");
    printf(" ============================ \n ");
  	printf(" Average disspation = %12.8f \n ",avg );
  	printf(" Relative max = %12.8f \n ",max );
  	printf(" Relative min = %12.8f \n ",min );
    printf(" ============================ \n ");
  }

  binSize = (max - min) / (double) noBins;
  for(bin=0;bin<noBins;bin++){
    binVal[bin]  = min + (double) bin * binSize ;
    binFreq[bin] = 0;
  }

  binCurrent = 0;
  for(ind=0;ind<N3;ind++) {
    if( arr[ind] < binVal[binCurrent+1] )
      binFreq[binCurrent] += 1 ;
    else
      binCurrent += 1 ;
  }

  for(bin=0;bin<noBins;bin++){
    binPdf[bin] = (double)binFreq[bin]/N3_d;
    fprintf(fptr," %30.15f %30.15f %12d \n",binVal[bin]+0.5f*binSize,binPdf[bin],binFreq[bin]) ;
  }
  fclose(fptr);
}

/*==============================================================
* FUNCTION :To formulate the details of boxes at different partitions.
*============================================================== */
void getBoxDetails()
{
  FILE *fptr;
  double a_Z,b_Z;
  int i_Zfn;
  char fileName[]="levels_of_partition.dat";
  char *fileAdd = (char *) malloc( 1+ sizeof(char*) *(strlen(outLoc) + strlen(fileName)));

  N_Zfn      = 4 ; // Declaring the no of partitions

  strcpy(fileAdd,outLoc);
  strcat(fileAdd,fileName);

	fptr	  =	fopen(fileAdd,"w");
  if(fptr == NULL) {
    printf("Error!");
    exit(1);
   }

	noofBoxes    = (int*)malloc( N_Zfn * sizeof(int) );
	boxGrids     = (int*)malloc( N_Zfn * sizeof(int) );
	log_boxGrids = (double*)malloc( N_Zfn * sizeof(double) );

  a_Z = 3.0f / (double) ( N_Zfn - 1 );
  b_Z = 1.0f ;

  if (testMode == 1)
  printf(" Partition Details \n");

  for (i_Zfn = 0; i_Zfn < N_Zfn; i_Zfn++ ) {
    *( noofBoxes + i_Zfn ) = (int) pow( 2.0f, log2_N - a_Z * i_Zfn - b_Z ) ; // No of boxes in this partition level
    *( boxGrids + i_Zfn )  = (int) pow( 2.0f,  a_Z * i_Zfn + b_Z ) ; // No of grid points in a box at this partition level
    *( log_boxGrids + i_Zfn ) = log( (double) *( boxGrids + i_Zfn ) / (double) N ); // Log of box size
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
*     To initialize the list of moment exponents.
*============================================================== */
void getMomentList()
{
  FILE *fptr;
  int i_qMom;
  char fileName[]="moment_details.dat";
  char *fileAdd = (char *) malloc( 1+ sizeof(char*) *(strlen(outLoc) + strlen(fileName)));

  N_qMom    = 10 ; // No of moments to be calculated

  strcpy(fileAdd,outLoc);
  strcat(fileAdd,fileName);

	fptr	  =	fopen(fileAdd,"w");
  if(fptr == NULL) {
    printf("Error!");
    exit(1);
   }

  qMom    = (double*)malloc( N_qMom * sizeof(double) );
  dataMom = (double*)malloc( ( N_qMom * N_Zfn ) * sizeof(double) );

  // double qMom_ar[21]={-4.0,-3.0,-2.5,-2.2,-2.0,-1.8,-1.5,-1.2,-1.0,-0.8,-0.5,0.5,0.8,1.2,1.5,1.8,2.0,2.2,2.5,3.0,4.0};
  // double qMom_ar[4]={-1.2,-1.0,1.2,1.5};
  double qMom_ar[10]={-2.5,-2.0,-1.5,-1.0,0.6,0.6,1.5,2.0,2.5,3.0};

  for( i_qMom = 0; i_qMom < N_qMom; i_qMom++ ) {
    *( qMom + i_qMom ) = qMom_ar[i_qMom] ;
    //*( qMom + i_qMom ) = -1.1f + 0.20f * ( (double) ( i_qMom ) );

    fprintf(fptr,"%6.4f \n",*( qMom + i_qMom ) );
  }
  fclose(fptr);
}

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To find the moments
*============================================================== */
void computePartitionFunction()
{
  FILE *fptr;
  int i_data,N_box,i_grid,N3_box,i_x,i_y,i_z;
  int i_box,i_qMom,i_Zfn,N_dataAdj,count_box;
  int box_x,box_y,box_z;
  char fileName[]="partition_function.dat";
  char *fileAdd = (char *) malloc( 1+ sizeof(char*) *(strlen(outLoc) + strlen(fileName)));

  strcpy(fileAdd,outLoc);
  strcat(fileAdd,fileName);

	fptr	  =	fopen(fileAdd,"w");
  if(fptr == NULL) {
    printf("Error!");
    exit(1);
   }

  i_Zfn  = 0;

  if (testMode == 1)
  printf(" Partition Function \n ");

  while( i_Zfn < N_Zfn ){ // For each partition level, the moments are calculated.

    i_grid      = *( boxGrids + i_Zfn ) ; // total no of grids in a box at this level
    fprintf(fptr," %30.15f ", *( log_boxGrids + i_Zfn ) ) ; // Printing the log of box size, proportionality
    N_box     = *( noofBoxes + i_Zfn ) ;
    N3_box    = pow( N_box, 3 ); // Total no of boxes at this level

    N_dataAdj = i_grid * N_box ; // Adjusted data size, removing the extra padding at this level.

    dataBox   = (double*)malloc( N3_box * sizeof(double) ); // Allocating box data size

    for( i_box = 0; i_box < N3_box; i_box++ )
      *( dataBox + i_box ) = 0.0f;

    for( i_x = 0; i_x < N_dataAdj; i_x++ ) {
    for( i_y = 0; i_y < N_dataAdj; i_y++ ) {
    for( i_z = 0; i_z < N_dataAdj; i_z++ ) {
      i_data               = ( i_x * N * N + i_y * N + i_z ) ; // Linear address of the data
      box_x                = (int) ( i_x / i_grid ) ;
      box_y                = (int) ( i_y / i_grid ) ;
      box_z                = (int) ( i_z / i_grid ) ; // Finding the x,y,z location of the box_x
      i_box                = ( box_x * N_box * N_box + box_y * N_box + box_z ) ; // Linear address of the box location
      *( dataBox + i_box )+= ( *( data + i_data ) ); // Adding the grid data to corresponding box data
    }}}

    i_qMom = 0;
    while( i_qMom < N_qMom ) { // At 'r' level, finding all moments
      *( dataMom + i_Zfn * N_qMom + i_qMom ) = 0.0f; // Declaring zero at start
      if( *( qMom + i_qMom ) < 0.0f ){ // Special for negative moments alone, to avoid NaN
        count_box = 0;
        for( i_box = 0; i_box < N3_box; i_box++ ) {
        	if ( *(dataBox + i_box) > 0.0f ){ // Taking only non-zero value statistics
         		count_box = count_box + 1 ;
        		*( dataMom + i_Zfn * N_qMom + i_qMom ) +=  pow( *( dataBox + i_box ) , *( qMom + i_qMom ) ) ;
        		// For each moment, calculating the partition function at this level
      		}}
        *( dataMom + i_Zfn * N_qMom + i_qMom ) = log( *( dataMom + i_Zfn * N_qMom + i_qMom ) / (double) count_box ) ;
        fprintf(fptr," %30.15f ",*( dataMom + i_Zfn * N_qMom + i_qMom ) ) ; // Printing each moment (log) at this partition level
        if (testMode == 1)
      	printf(" %10.8f ", *( dataMom + i_Zfn * N_qMom + i_qMom ) );
    	}
      else{ // For positive moments
        for( i_box = 0; i_box < N3_box; i_box++ )
      		*( dataMom + i_Zfn * N_qMom + i_qMom ) +=  pow( *( dataBox + i_box ) , *( qMom + i_qMom ) ) ;
      		// For each moment, calculating the partition function at this level
        *( dataMom + i_Zfn * N_qMom + i_qMom ) = log( *( dataMom + i_Zfn * N_qMom + i_qMom ) / (double) N3_box ) ;
        fprintf(fptr," %30.15f ",*( dataMom + i_Zfn * N_qMom + i_qMom ) ) ;
        // Printing each moment (log) at this partition level
        if (testMode == 1)
      	printf(" %10.8f ", *( dataMom + i_Zfn * N_qMom + i_qMom ) );
      }
      i_qMom = i_qMom + 1 ; // To next moment
    }
    fprintf(fptr," \n ") ; // this partition level calculation is completed, over to next partition level
    if (testMode == 1)
  	printf(" \n ");
    free(dataBox) ; // Freeing box data
    i_Zfn = i_Zfn + 1 ; // To next partition
  }
	fclose(fptr);
  if (testMode == 1)
  printf("================================= \n ");
  free(data);
}

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To find the moment exponents using partition function.
*============================================================== */
void computeExponents()
{
  FILE *fptr;
  double sumX2,sumXY;
  double sumX,sumY;
  int i_Zfn;
  int i_qMom;
  char fileName[]="exponents.dat";
  char *fileAdd = (char *) malloc( 1+ sizeof(char*) *(strlen(outLoc) + strlen(fileName)));

  strcpy(fileAdd,outLoc);
  strcat(fileAdd,fileName);

	fptr	  =	fopen(fileAdd,"w");
  if(fptr == NULL) {
    printf("Error!");
    exit(1);
   }

  dataExp = (double*)malloc( N_qMom * sizeof(double) );

  if (testMode == 1)
  	printf(" Exponents \n ") ;
  for( i_qMom=0; i_qMom < N_qMom; i_qMom++ ) {
    sumX2 = 0.0f;
    sumXY = 0.0f;
    sumY  = 0.0f;
    sumX  = 0.0f;
    for(i_Zfn=0; i_Zfn < N_Zfn; i_Zfn++ ) {
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

/*==============================================================
* FUNCTION :
* ______________________________________________________________
*     To free left out pointer arrays
*============================================================== */
void freePointerMemory()
{
  free(dataExp);
  free(dataMom);
  free(qMom);
  free(noofBoxes);
  free(boxGrids);
  free(log_boxGrids);
}
