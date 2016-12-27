#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
using namespace std;
#define MAX 8
int n;
int mat[MAX][MAX];

vector<int> perm;
vector <int> shortest;
int calc()
{
	int val =0;
	for(int i=0; i<n-1; i++)
		val+=mat[perm[i]][perm[i+1]];
	val+=mat[perm[n-1]][perm[0]];
	return val;
}
int main()
{
	int t;
	cin>>t;
	for(int z =1; z<=t; z++)
	{
		int min = INT_MAX;
		cin>>n;
		perm.clear();
		shortest.clear();
		for(int i =0; i<n; i++)
			for(int j =0; j<n; j++)
				cin>>mat[i][j];
		for(int i=0; i<n; i++)
			perm.push_back(i);
		while(next_permutation(perm.begin(), perm.end()))
		{
			int v = calc();
			if(v<min)
			{
				min = v;
				shortest = perm;
			}
		}
		cout<<"Case #"<<z<<": ";
		for(int i =0; i<n; i++)
			cout<<shortest[i]+1<<" ";
		cout<<"\n";
	}
}
