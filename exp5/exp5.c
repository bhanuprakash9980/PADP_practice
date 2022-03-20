#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>
#define BUFSIZE 32

char mes[3][BUFSIZE] ={"HELLO","CSE","RVCE"};

int main(int argc,char** argv)
{
	MPI_Init(&argc,&argv);
int rank,size,root=0,tag=0;
char msg[BUFSIZE];
MPI_Status status;
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);

if(rank!=0)
{
	strcpy(msg,mes[rank-1]);
	MPI_Send(&msg,BUFSIZE,MPI_CHAR,root,tag,MPI_COMM_WORLD);
}
else
{
	for(int i=1;i<size;i++)
	{
		MPI_Recv(&msg,BUFSIZE,MPI_CHAR,i,tag,MPI_COMM_WORLD,&status);
		printf("msg = %s\t, from %d\n",msg,i);
	}

}

MPI_Finalize();
return 0;

}

