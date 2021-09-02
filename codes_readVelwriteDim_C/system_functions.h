/*>>>>>>>>>>>>>>>>>>
*  GLOBAL VARIABLES
* <<<<<<<<<<<<<<<<< */

// INPUT OUTPUT
 char * outLoc, * inpLoc;

// DATA SIZES
int N,N3,Nh,log2_N;
double N3_d;

// MOMENTS
int N_qMom;

// PARTITION FUNCTION
int N_Zfn;

// DEBUG
int testMode,errorStatus;

/*************************
    VELOCITY POINTERS
*************************/
double *u_x,*u_y,*u_z;

/*************************
DISSIPATION FIELD POINTER
*************************/
double *data;

/*************************
MOMENTS POINTERS
*************************/
double *qMom,*dataMom;

/*************************
PARTITION FN POINTERS
*************************/
int *noofBoxes,*boxGrids;
double *dataBox,*log_boxGrids;

/*************************
EXPONENTS POINTERS
*************************/
double *dataExp;

/*>>>>>>>>>>>>>>>>>>
* FUNCTION LIST DECL.
* <<<<<<<<<<<<<<<<< */
void fftR2C(double *in,fftw_complex *out);
void fftC2R(fftw_complex *out,double *in);
void getInputDetails();
void allocateRealVelocity();
void computeDissipationField();
void computePdfDissipationField();
void getBoxDetails();
void getMomentList();
void computePartitionFunction();
void computeExponents();
void freePointerMemory();
