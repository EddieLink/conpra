#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int main()
{
	srand(time(NULL));
	freopen("inputGen","w",stdout);
	int tests = 100;
	cout<<tests<<endl;
	for(int z = 0; z<tests; z++)
	{
		int coins, value;
		coins = rand()%100 + 1;
		value = rand()% 10000 + 1;
		cout<<coins<<" "<<value<<"\n";
		for(int i =0 ;i<coins; i++)
			cout<<rand()%1001<<" ";
		cout<<endl<<endl;
	}
}
