#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define SEED 10000

int main(int argc, char** argv)
{
	int n,i,j,count=0;
	double x,y,z,pi,st,end;
	srand(SEED);
	for(n=1000;n<=1000000;n*=10)
	{
		printf("No. of iterations %d\n",n);
		for(i=1;i<=8;i*=2)
		{
			count=0;
			printf("No. of threads %d\n",i);
			omp_set_num_threads(i);
			st=omp_get_wtime();
#pragma omp parallel for
			for(j=0;j<n;j++)
			{
				x= (double)rand()/RAND_MAX;
				y= (double)rand()/RAND_MAX;
				z=x*x+y*y;
				if(z<=1)
					count++;
			}
			pi = (double)count/n*4;
			end=omp_get_wtime();
			printf("pi = %lf\t time = %lf\n",pi,end-st);


		}
	}

}
