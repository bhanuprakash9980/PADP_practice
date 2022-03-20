#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argc,char** argv)
{
int **a,**b,**c;
int n,i,j,k,n_threads;
double st,end;

for(n=250;n<=1000;n+=250)
{       a = (int **)malloc(n*sizeof(int **));
       	for(i=0;i<n;i++)
	a[i]=(int *)malloc(n*sizeof(int*));

	 b = (int **)malloc(n*sizeof(int**));
        for(i=0;i<n;i++)
        b[i]=(int *)malloc(n*sizeof(int*));

	c = (int **)malloc(n*sizeof(int**));
        for(i=0;i<n;i++)
        c[i]=(int *)malloc(n*sizeof(int*));



	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			a[i][j] = i+j;
	  for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                        b[i][j] = i+j;
	  for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
                       c[i][j] = 0;
	printf("size = %d \n",n); 
	for(n_threads = 1; n_threads<=8;n_threads*=2)
	{       printf("num of threads = %d \n",n_threads);
		st= omp_get_wtime();
		omp_set_num_threads(n_threads);

#pragma omp parallel for private(j,k)
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				for(k=0;k<n;k++)
					c[i][j] += a[i][k]*b[k][j];
			}
			
		}
		end = omp_get_wtime();
		printf("time = %lf\n",end-st);
	}
}
return 0;	


}
