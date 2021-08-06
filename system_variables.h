#ifndef SYS_VAR_H
#define SYS_VAR_H

/*>>>>>>>>>>>>>>>>>>
*  GLOBAL VARIABLES
* <<<<<<<<<<<<<<<<< */
// Data
int N_data;
int eDim;
double *data;
double dataDMin;
double dataMax;
// Moments
int N_qMom;
double *qMom;
// Partition Function
int N_ZFn;
double *qZFn;
double *lnqZFn;
double *lnR;
// Box Counting
int *box_data;
double *dummy;
double *rDim;

// Debug
int testMode;

/*>>>>>>>>>>>>>>>>>>
* FUNCTION LIST DECL.
* <<<<<<<<<<<<<<<<< */
void getInputSize();
void allocateArray();
void getInputData();
void sortArray( int low, int hig );
void mergingArray( int low, int mid, int hig );
void normalizeArray();
void getBoxDetails();
void getMomentList();
void getPartitionFunction();
// void getDimension();
double findMin( double *arr, int siz );

#endif
