#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  int i,j;
  int n_x=3,n_y=3;

  double *arr;
  // double *arr2;

	arr  = (double*)malloc( (n_x*n_y)* sizeof(double) );
	// arr2  = (double*)malloc( (n_x*n_y)* sizeof(double) );

  FILE *fptr;

  if(( fptr = fopen("Vk.in","rb")) == NULL)
  {
    printf("error! Opening file");
    exit(1);
  }

  fread(arr,sizeof(arr),1,fptr);
  /*
  for(i=0;i<n_x;i++)
  {
    for(j=0;j<n_y;j++)
    {
      fread(arr+i*n_y+j,sizeof(double),1,fptr);
      // fread(arr2+i*n_y+j,sizeof(double),1,fptr);
    }
  }
*/
  for(i=0;i<n_x;i++)
  {
    printf(" | ");
    for(j=0;j<n_y;j++)
    {
      printf("%f | ",*(arr+i*n_y+j));
    }
    printf("\n");
  }
/*
  for(i=0;i<n_x;i++)
  {
    printf(" | ");
    for(j=0;j<n_y;j++)
    {
      printf("%f | ",*(arr2+i*n_y+j));
    }
    printf("\n");
  }
*/
  fclose(fptr);
  free(arr);

  return 0;
}
