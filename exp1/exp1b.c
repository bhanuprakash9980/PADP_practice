#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define SEED 10000
void main(int argc,char** argv)
{
	MPI_Init(&argc,&argv);
	double x,y,z,pi,st,end;
	int iter = 1000,reduced_iter=0,reduced_count=0,count=0;
	int rank,size,i;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0)
		st= MPI_Wtime();
	if(rank > 0)
	{
		srand(SEED);
		for(int i=0;i<iter;i++)
		{
			x= (double)rand()/RAND_MAX;
			y = (double)rand()/RAND_MAX;
			z = x*x + y*y;
			if(z<=1)
				count++;
		}
	}

	MPI_Reduce(&count,&reduced_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Reduce(&iter,&reduced_iter,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	reduced_iter = reduced_iter - iter;
	if(rank==0)
	{
		pi = (double)reduced_count/reduced_iter*4;
		end = MPI_Wtime();
		printf("pi = %lf,\ttime = %lf\n",pi,end-st);
	}
	MPI_Finalize();
}
