#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>
#include <tuple>
#include <cmath>
using namespace std;

typedef vector<int> vec;
typedef vector<tuple<int,int>> tupVec;
int getMinTrips(int n, int a, int b, vec v)
{
	vec sums;
	int cur = 0;
	for(int i =0; i<n; i++)
	{
        if(!sums.size())
			sums.push_back(v[i]);
		else
			if(sums[cur] + v[i] <=b)
				sums[cur]+=v[i];
			else
			{
				sums.push_back(v[i]);
				cur++;
			}

	}
	return sums.size();
}
int mat[1001][1001];
vec ts;
int a,b;
int coefficient(int l, int r)
{
	int x = ts[r];
	if(l) x-=ts[l-1];

	if(x>b) return INT_MAX;
	if(x>a) return pow(x-a,2);
	return 0;
}
string solve()
{
	int n; cin>>n>>a>>b;
	vec v = vec(n);
	bool possible = true;
	ts = vec(n,0);
	for(int i =0; i<n; i++)
	{
		cin>>v[i];
		if(v[i]>b)
			possible = false;
		ts[i]+=v[i];
		if(i) ts[i]+=ts[i-1];
	}
	if(!possible)
		return "impossible";
	int minTrips = getMinTrips(n,a,b,v);
	for(int i =0; i<=n; i++)
		for(int j =0; j<=minTrips; j++)
			mat[i][j] = INT_MAX;
	for(int i =0; i<n; i++)
		mat[i][0] = coefficient(0,i);
	for(int i = 0; i<n; i++)
		for(int j = 1; j<= minTrips; j++)
			for(int x = 0; x<=i; x++)
			{
				int coef = coefficient(i-x+1, i);
				if(coef!=INT_MAX)
				{
					if(mat[i-x][j-1] != INT_MAX)
						mat[i][j] = min(mat[i][j], mat[i-x][j-1] + coef);
				}
				else break;
			}
    for(int i = 0; i<minTrips; i++)
		if(mat[n-1][i] != INT_MAX)
			return to_string(mat[n-1][i]);

}
int main()
{
	int t; cin>>t;
	for(int z = 1; z<=t; z++)
		cout<<"Case #"<<z<<": "<<solve()<<"\n";
}
