#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
#define MAX 100000001
int n;
bool primes[MAX];
void generatePrimes()
{
	n = MAX;
	primes[2] = true;
	for(int i = 3; i<=n; i+=2)
		primes[i] = true;
    for(int i = 3; i<=n; i+=2)
		if(primes[i])
			for(int j =2; j*i<=n; j++)
				primes[j*i] = false;
}
vector<int> findPair(int sum)
{
	vector<int>sol;
	if((sum < 3 && !(sum%2)) || (sum<6 && (sum%2)))
		return sol;
	if(primes[sum-2])
	{
		sol.push_back(2);
		sol.push_back(sum-2);
		return sol;
	}
	for(int i =3; i<=sum-3; i+=2)
	{
		if(!primes[i] || !primes[sum-i])
			continue;
		sol.push_back(i);
		sol.push_back(sum-i);
		break;
	}
	return sol;
}
int main()
{
	generatePrimes();
	int t;
	scanf("%d\t",&t);
    for(int z=1; z<=t; z++)
	{
		scanf("%d\n",&n);
		vector<int> sol;
		if(!(n%2))
			sol = findPair(n);
		else
		{
			sol = findPair(n-2);
			if(!sol.size())
			{
				if(primes[n-4])
				{
					sol.push_back(2);
					sol.push_back(2);
					sol.push_back(n-4);
				}
				else
				{
					sol = findPair(n-3);
					sol.push_back(3);
				}
			}
			else
				sol.push_back(2);
		}
		sort(sol.begin(), sol.end());
		printf("Case #%d: ", z);
		for(int i =0; i<sol.size(); i++)
			printf("%d ", sol[i]);
		printf("\n");

    }

}
