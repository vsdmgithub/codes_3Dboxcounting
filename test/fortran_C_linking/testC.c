#include <stdio.h>
#include <stdlib.h>

// extern void fortransub();
extern void fortranReadFile (double * arr, double * arr2);

int main(void)
{
  int n_x=3;
  int n_y=3;
  int n_z=3;
  int i,j,k;
  double *arr,*arr2;

	arr  = (double*)malloc( (n_x*n_y*n_z)* sizeof(double) );
	arr2 = (double*)malloc( (n_x*n_y*n_z)* sizeof(double) );

  fortranReadFile (arr,arr2);

  for(k=0;k<n_z;k++)
  {
    printf(" Slice No %d \n ============================= \n",k+1);
    for(i=0;i<n_x;i++)
    {
      printf(" | ");
      for(j=0;j<n_y;j++)
      {
        printf("%f | ",*(arr+i*n_y*n_z+j*n_z+k));
      }
      printf("\n");
    }
  }

return 0;
}
