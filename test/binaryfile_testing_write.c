#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  int i,n_x=3;
  int j,n_y=3;
  double *arr;

  FILE *fptr;
	arr  = (double*)malloc( (n_x*n_y)* sizeof(double) );

  for(i=0;i<n_x;i++)
  {
    for(j=0;j<n_y;j++)
      *(arr+i*n_y+j)=sqrt(i*2 + j*3);
  }

  if(( fptr = fopen("data.in","wb")) == NULL)
  {
    printf("error! Opening file");
    exit(1);
  }


  for(i=0;i<n_x;i++)
  {
    printf(" | ");
    for(j=0;j<n_y;j++)
    {
      printf("%30.24f | ",*(arr+i*n_y+j));
      fwrite(arr+i*n_x+j,sizeof(double),1,fptr);
    }
    printf("\n");
  }

  fclose(fptr);
  free(arr);

  return 0;
}
