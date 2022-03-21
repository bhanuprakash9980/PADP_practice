#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
int main()
{
 string words[4]={"fuck","you","and","mistakes"};
  for(int i=1;i<=8;i*=2)
{
double st= omp_get_wtime();
#pragma omp parallel for num_threads(i)
for(int k=0;k<4;k++)
{
string s;
fstream file;
file.open("words.txt");
int count =0;
while(file>>s)
if(s == words[k])
count++;

cout<<"Word = "<<words[k]<<" Count = "<<count<<"\n";
file.close();
}
st= omp_get_wtime()-st;
cout<<"no of threads = "<<i<<" time = "<<st<<"\n";
}
return 0;
}
