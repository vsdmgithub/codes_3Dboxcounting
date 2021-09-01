#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  int i,n_x=3;
  int j,n_y=3;

  double *arr;
	arr  = (double*)malloc( (n_x*n_y)* sizeof(double) );

  FILE *fptr;

  if(( fptr = fopen("data.in","rb")) == NULL)
  {
    printf("error! Opening file");
    exit(1);
  }

  for(i=0;i<n_x;i++)
  {
    for(j=0;j<n_y;j++)
    fread(arr+i*n_y+j,sizeof(double),1,fptr);
  }

  for(i=0;i<n_x;i++)
  {
    printf(" | ");
    for(j=0;j<n_y;j++)
    {
      printf("%30.24f | ",*(arr+i*n_y+j));
    }
    printf("\n");
  }

  fclose(fptr);
  free(arr);

  return 0;
}
