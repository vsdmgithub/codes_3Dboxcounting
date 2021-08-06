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
*  C PROGRAM TO FIND THE FRACTAL DIMENSION OF GIVEN DATA
*	 USING BOX-COUNTING ALGORITHM.
* _________________________________________________________________
*  REF :- Efficient box-counting determination of generalized
*        fractal dimensions, A.Block et.al.,(1990)
* IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

* DATE : 29 JULY 2021
*
*/

/*>>>>>>>>>>>>>>>>>>
*      HEADERS
* <<<<<<<<<<<<<<<<< */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

// FUNCTIONS
void CallInput();
void GetInput();
void evolveEulerScheme(float *pos, float *vel);
float RandomNoGenerator();
float NormalNoGenerator();

// CONSTANTS
#define PI 3.142857
#define minimumNoSteps 100 // Bare minimum no of steps to run

// GLOBAL VARIABLES
int ensSize;
float temperature;
float timeStep;
float fricCoeff;
int totalTimeSteps;
char fileLocation[100];

// MAIN FUNCTION
int main()
{
    // VARIABLES DECLARATION
		// RUNNING THROUGH TIME AND ENSEMBLES
		int ensInd,stepInd;

		// POINTER FOR POSITION AND VELOCITY
		float *position;
		float *velocity;

		// POINTER FOR ENSEMBLE AVERAGED QUANTITIES
		float *ensAvgPositionVariance;
		float *ensAvgVelocityVariance;

		// INITIAL CONDITION
		float initialPosition=0.0;
		float initialVelocity=0.0;

		// OUTPUT SIZE DETAILS
		int noOfTimeOutput = 100; // No of data points stored.
		int jumpSize; // Size of jump, in terms of time steps to reach subsequent data points.
		int dataPoint;
		int saveStatus; // 0 means, its time to save it

		// OUTPUT STORAGE
		char fileName[100];
		FILE *fptr; // Pointer showing the address of file

		// TIME MEASURE
		clock_t	timeStart,timeEnd;
		double cpuTimeUsed;

		// START TIME
		timeStart = clock();

		// SETTING THE SEED WITH TIME FOR FRESH RANDOM NUMBERS ON NOISE
		srand(time(NULL));

		// INPUT PARAMETERS
		GetInput();
		jumpSize = (int) (totalTimeSteps / noOfTimeOutput);

		// ALLOCATING POINTER FOR ENSEMBLE AVERAGES
		velocity = (float*)malloc( sizeof(float));
		position = (float*)malloc( sizeof(float));
		ensAvgVelocityVariance = (float*)malloc( (noOfTimeOutput+1) * sizeof(float));
		ensAvgPositionVariance = (float*)malloc( (noOfTimeOutput+1) * sizeof(float));

		// MAKING SURE POINTER IS ALLOCATED MEMORY
		if(ensAvgVelocityVariance == NULL)
		{
				printf(" Error! Memory not allocated for 'TimeArray' \n ");
				exit(0);
		}

		// LOOP FOR ENSEMBLE
		for(ensInd = 1; ensInd <= ensSize; ++ensInd)
		{

		*velocity	= initialVelocity;
		*position	=	initialPosition;
		// LOOP FOR TIME
		for( stepInd = 0; stepInd<=totalTimeSteps; ++stepInd)
		{
				saveStatus = stepInd % jumpSize;
				if ( saveStatus ==0 ) // ITS TIME TO SAVE
				{
					dataPoint = (int) (stepInd / jumpSize);
					*(ensAvgVelocityVariance+dataPoint) = *(ensAvgVelocityVariance+dataPoint) + pow(*velocity,2.0);
					*(ensAvgPositionVariance+dataPoint) = *(ensAvgPositionVariance+dataPoint)+ pow(*position,2.0);
			  }

				// TIME EVOLUTION
				evolveEulerScheme(position,velocity);
		}
	}

	// FOLDER,FILE NAME AND CREATION
	system("mkdir ./data");
	sprintf(fileName,"%s",fileLocation);
	fptr	=	fopen(fileName,"w");

	for( dataPoint = 0; dataPoint<=noOfTimeOutput; ++dataPoint)
	{
		fprintf(fptr,"%.3f %.6f %.6f \n",dataPoint*timeStep*jumpSize,(*(ensAvgPositionVariance+dataPoint))/ensSize,(*(ensAvgVelocityVariance+dataPoint))/ensSize);
	}
	fclose(fptr);

	timeEnd = clock();
	cpuTimeUsed = ((double) (timeEnd - timeStart)) / CLOCKS_PER_SEC;
	cpuTimeUsed = cpuTimeUsed/60.0 ;

	printf("PROGRAM COMPLETED - - \n Time Taken = %f \n",cpuTimeUsed);
	return 0;
}
void evolveEulerScheme(float *pos,float *vel)
{
	*pos = *pos + timeStep * (*vel);
	*vel = *vel + timeStep * (- fricCoeff * (*vel) + sqrt(temperature) * NormalNoGenerator() );
}
void CallInput()
{
		// GETS THE INPUT FROM USER.
		printf("Enter the following \n");
		printf("1.Size of Ensemble : ");
		scanf("%d",&ensSize);
reInput:printf("2.Total no of Steps (atleast %d):",minimumNoSteps);
		scanf("%d",&totalTimeSteps);
		if( totalTimeSteps < minimumNoSteps)
		{
  			goto reInput;
		}
		printf("3.temperature of Bath: ");
		scanf("%f",&temperature);
		printf("4.friction coefficient: ");
		scanf("%f",&fricCoeff);
		printf("5.Time step: ");
		scanf("%f",&timeStep);
}
void GetInput()
{
	ensSize	=	100000;
	totalTimeSteps	=	5000;
	temperature = 5.0;
	fricCoeff = 0.1;
	timeStep = 0.005 / fricCoeff;
	strcpy(fileLocation , "data/brownianData-T5-Fp1.dat");
}
float RandomNoGenerator()
{
		// RETURN AN UNIFORMLY DISTRIBUTED RANDOM VALUE (0,1)
		return ((float)rand())/((float)RAND_MAX);
}
float NormalNoGenerator()
{
		// USE BOX-MUELLER METHOD TO GENERATE NORMAL DISTRIBUTION
		float x1=RandomNoGenerator();
		float x2=RandomNoGenerator();
		return sqrt( -2. * log(x1) ) * cos( 2. * PI * x2 );
}
