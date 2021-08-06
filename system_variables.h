#ifndef SYS_VAR_H
#define SYS_VAR_H

/*>>>>>>>>>>>>>>>>>>
*  GLOBAL VARIABLES
* <<<<<<<<<<<<<<<<< */
int ind,N_data;
int N_qMom;
int N_pFun;
int *box_data;
double *data;
double *dummy;
double *pFun;
double *qMom;
double *rDim;
double dataDMin;

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
void getMomentExp();
void getPartitionFunction();
void writeMoments();
void getDimension();
double findMin( double *arr, int siz );

#endif
