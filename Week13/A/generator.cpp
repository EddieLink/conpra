#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;
int main()
{
	freopen("inputGen","w",stdout);
	int t = rand()%15 + 1;
	t = 1;
	cout<<t<<endl;
	for(int z = 0; z<t; z++)
	{
		int n,m,k,l;
		n = rand()%1000000 + 1;
		k = rand()%100000 + 1;
		cout<<" "<<n<<" "<<k<<endl;
		for(int i =0; i<n; i++)
		{
			int x, y;
			int c = rand()%3;
			char com;
			switch(c)
			{
				case 0: com = 's'; break;
				case 1: com = 'd'; break;
				case 2: com = 'c'; break;
			}
			x = rand()%n + 1;
			y = rand()%n + 1;
			cout<<com<<" ";
			if(com == 'c')
				cout<<x<<" "<<y<<endl;
			else
				cout<<x<<endl;
		}
	}
}
