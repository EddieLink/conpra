#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;
int main()
{
	freopen("inputGen","w",stdout);
	int t = rand()%15 + 1;
	cout<<t<<endl;
	for(int z = 0; z<t; z++)
	{
		int n,m,k,l;
		n = rand()%100 + 1;
		m = rand()%10001;
		k = rand()%n + 1;
		l = rand()%1001;
		cout<<n<<" "<<m<<" "<<k<<" "<<l<<endl;
		for(int i =0; i<m; i++)
		{
			int x, y;
			x = rand()%n + 1;
			y = rand()%n + 1;
			int l1 = rand()%1001;
			cout<<x<<" "<<y<<" "<<l1<<endl;
		}
		vector<bool> used = vector<bool>(n, false);
		for(int i =0; i<k; i++)
		{
			int a, b;
			a = rand()%n + 1;
			while(used[a])
				a = rand()%n + 1;
			used[a] = true;
			b = rand()%10001;
			cout<<a<<" "<<b<<endl;
		}
	}
}
