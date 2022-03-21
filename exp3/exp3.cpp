#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

double t = 0.0;

long Strike(bool composite[],long i,long stride, long limit);
long ufs(long n);
long cfs(long n);
long pfs(long n);

int main()
{
long count1,count2,count3;
for(long n=100000000;n>=1000000;n/=10)
{cout<<"n= "<<n<<"\n";
count1= ufs(n);
cout<<"count= "<<count1<<"  time= "<<t<<"\n";
count2=cfs(n);
cout<<"count= "<<count2<<" time= "<<t<<"\n";
count3=pfs(n);
cout<<"count= "<<count3<<" time= "<<t<<"\n";

}
}

long Strike(bool composite[],long i,long stride,long limit)
{
for(;i<=limit;i+=stride)
composite[i]=true;
return i;
}

long ufs(long n){

long m = (long)sqrt((double)n);
bool* composite = new bool[n+1];
long count =0,i;
memset(composite,0,n);
t=omp_get_wtime();

for(i=2;i<=m;i++)
{
if(!composite[i])
 {
count++;
Strike(composite,2*i,i,n);
}
}

for(i= m+1;i<=n;i++)
{
if(!composite[i]) count++;
}

t=omp_get_wtime()-t;

delete[] composite;
return count;
}

long cfs(long n){

long m = (long)sqrt((double)n);
bool* composite = new bool[n+1];
long count =0,i,k,n_factor=0,window,limit;
long* striker =  new long[m];
long* factor = new long[m];
 
memset(composite,0,n);
t=omp_get_wtime();

for(i=2;i<=m;i++)
{
if(!composite[i])
 {
count++;
striker[n_factor] = Strike(composite,2*i,i,m);
factor[n_factor++] = i;

}
}

for(window= m+1;window<=n;window+=m)
{

limit = min(window+m-1,n);
for(k=0;k<n_factor;k++)
 striker[k] = Strike(composite,striker[k],factor[k],limit);

for(i= window;i<=limit;i++)
if(!composite[i]) count++;
}

t=omp_get_wtime()-t;

delete[] striker;
delete[] factor;
delete[] composite;
return count;
}



long pfs(long n){

long m = (long)sqrt((double)n);
long count =0,n_factor=0;
long* factor = new long[m];

t=omp_get_wtime();

#pragma omp parallel 
{
long* striker = new long[m];
bool* composite = new bool[m+1];

#pragma omp single
{
memset(composite,0,m);
for(long i=2;i<=m;i++)
{
if(!composite[i])
{count++;
Strike(composite,2*i,i,m);
factor[n_factor++] = i;
}
}
}

long base = -1;

#pragma omp for reduction(+:count)
for(long window = m+1; window <=n; window+=m)
{
memset(composite,0,m);
if(base!=window)
{
base = window;
for(long k=0;k<n_factor;k++)
striker[k] = (base + factor[k] -1)/factor[k]*factor[k] - base;
}

long limit = min(window+m-1,n) - base;

for(long k = 0;k<n_factor;k++)
striker[k] = Strike(composite,striker[k],factor[k],limit)-m;

for(long i = 0;i<=limit;i++)
if(!composite[i])
count++;
base+=m;
}

delete[] composite;
delete[] striker;


}

t=omp_get_wtime()-t;


delete[] factor;
return count;
}
