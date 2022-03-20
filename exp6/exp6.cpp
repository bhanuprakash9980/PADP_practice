
#include<iostream>
#include<fstream>
#include<cstring>
#include<omp.h>
#define BUFSIZE 32
using namespace std;
int main(int argc, char** argv){
char *fname="words.txt";
int n_t,n=8,count;
double st,end;
for(n_t=1;n_t<=n;n_t*=2)
{
fstream file;
char words[4][BUFSIZE]={"fuck","and","your","mistakes"};
string s;
st = omp_get_wtime();
#pragma omp parallel for num_threads(n_t)
for(int k=0;k<4;k++)
{count=0;

file.open(fname);
while(file >> s)
{
if(strcmp(s.c_str(),words[k])==0)
{count++;
}
}
cout<<"\t word = "<<words[k]<<"\t count= "<<count<<"\n";

file.close();
}
end=omp_get_wtime();
cout<<"no. of threads = "<<n_t<<"\t time = "<<end-st<<"\n";
}
return 0;
}
