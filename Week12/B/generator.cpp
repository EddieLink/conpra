#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
int main()
{
	freopen("inputGen","w",stdout);
	srand(time(NULL));
	int n = 1000000;
	int k = 10000;
	cout<<1<<"\n"<<n<<" "<<k<<endl;
	for(int i =0; i<k; i++)
	{
		if(rand()%1000 > 500)
		{
			int left, right, val;
			left = rand()%n + 1;
			right = rand()%n + 1;
			val = rand()%1000 + 1;
			cout<<"i "<<min(left,right)<<" "<<max(left,right)<<" "<<val<<"\n";
		}
		else
		{
			cout<<"q "<<rand()%n + 1;
		}
	}
}