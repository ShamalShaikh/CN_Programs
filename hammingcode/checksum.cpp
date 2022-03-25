#include<bits/stdc++.h>
using namespace std;
 
int main(int argc, char const *argv[])
{
	int *msg,m,b;
	cout<<"Enter the length of message : ";
	cin>>m;

	msg = (int *)malloc(m*sizeof(int));

	cout<<"Enter the message : \n";

	for(int i=0;i<m;++i)
		cin>>msg[i];

	cout<<"Enter the blocksize  : \n";

	cin>>b;

	if(m%b)



	return 0;
}