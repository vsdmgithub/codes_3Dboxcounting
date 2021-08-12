#ifndef SYS_VAR_H
#define SYS_VAR_H

/*>>>>>>>>>>>>>>>>>>
*  GLOBAL VARIABLES
* <<<<<<<<<<<<<<<<< */

// Data
int N_data,N3_data;
int log2_N_data;
double *data;
double *dataAvg;

// Moments
int N_qMom;
double *qMom;
double *dataMom;

// Partition Function
int N_Zfn;
double *dataBox;
int *noofBoxes;
int *boxGrids;

// Debug
int testMode;
int errorStatus;

/*>>>>>>>>>>>>>>>>>>
* FUNCTION LIST DECL.
* <<<<<<<<<<<<<<<<< */
void getInputDetails();
void allocateDataArrays();
void getInputData();
void normalizeData();
void getBoxDetails();
void getMomentList();
void getPartitionFunction();

#endif
