#include<bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
	int *msg,m,r;
	cout<<"Enter the message length : \n";
	cin>>m;
	msg = (int *)malloc((m+1)*sizeof(int));
	cout<<"Enter the message : \n";
	for(int i=1;i<=m;++i)
		cin>>msg[i];
	// Calculate sizeof r bits
	
	for(int i=1;i<=m;++i)
		cout<<msg[i];
	cout<<"\n";

	for(r = 1;pow(2,r)<m+r+1;r<<=1);
	cout<<"length of redundant bits = "<<r<<"\n";

	int send[m+r+1] = {0};
	
	for(int x = 1; x<=(m+r) ; x<<=1)
		send[x] = -1;

	// for(int i=1;i<=m+r;++i)
	// 	cout<<send[i];

	// cout<<"\n";
	
	int a=1;
	for(int x=1;x<=m+r;x++){
		if(send[x]!=-1){
			send[x] = msg[a++];
			// cout<<x<<" : "<<send[x]<<"\n";
		}
	}

	for (int i = 1; i <= m+r; ++i)
	{
		cout<<send[i];
	}
	cout<<"\n";
	int s=0;
	for(int p=0;p<r;++p){
		s = 0;
		// cout<<"p = "<<p<<"\n";
		for(int x = 1;x<=m+r;x++){
			// cout<<"x : "<<x<<"\t";
			// cout<<"if : "<<(x&(1<<p))<<"\t";
			if(x&(1<<p)&& send[x]!=-1){
				s ^= send[x];
				// cout<<send[x]<<" "<<s<<" ";
			}
		}
		// cout<<(1<<p)<<" : "<<s<<"\n";
		send[1<<p] = s;
	}

	for (int i = 1; i <= m+r; ++i)
	{
		cout<<send[i];
	}
	cout<<"\n --------SENT----------\n";

	//introducing a single bit error
	srand(time(0));

	int random = (rand()%(m+r));
	// cout<<random<<"\n";
	send[random] = !(send[random]);

	cout<<"After receiving:\n";
	for (int i = 1; i <= m+r; ++i)
	{
		cout<<send[i];
	}

	s=0;
	int ans=0;
	for(int p=0;p<r;++p){
		s = 0;
		// cout<<"p = "<<p<<"\n";
		for(int x = 1;x<=m+r;x++){
			// cout<<"x : "<<x<<"\t";
			// cout<<"if : "<<(x&(1<<p))<<"\t";
			if(x&(1<<p)){
				s ^= send[x];
				// cout<<send[x]<<" "<<s<<" ";
			}
		}
		// cout<<(1<<p)<<" : "<<s<<"\n";
		if(s){
			ans+=(1<<p);
		}
	}  

	cout<<"\nBit error at  position : "<<ans<<"\n";

	return 0;
}