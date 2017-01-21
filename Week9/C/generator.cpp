#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;
int main()
{
	freopen("inputGen","w",stdout);
	srand(time(NULL));
	int n,m;
//	n = rand()%250;
//	m = rand()%250;
	n = m = 250;
	cout<<n<<" "<<m<<endl;
	
	for(int i =0; i<n; i++)
	{
		bool prez[m];
		for(int j =1; j<=m; j++)
			if(rand()%1000 <= 700)
				prez[j] = true;
			else 
				prez[j] = false;	
		bool displayed = false;
		for(int j = 1; j<=m; j++)
		{
			cout<<",";
			if(prez[j])
			{
				//if(displayed) cout<<",";
				displayed = true;
				int range = j;
				while(prez[range]) range++;
				if(range!=j && range>j+1)
					cout<<j<<"-"<<range;
				else if(range == j+1)
					cout<<j<<","<<range;
				else
					cout<<j;
				j = range;
			}
		}			
		cout<<endl;
	}
}
