#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int t; cin>>t;
	for(int z = 1; z<=t; z++)
	{
		int n,c; cin>>n>>c;
		vector<int> coins = vector<int>(n);
		for(int i =0; i<n; i++)
			cin>>coins[i];
		int mat[n+1][c+1];
		for(int i =0; i<=c; i++)
			mat[0][i] = i;
		int taken[n+1][c+1];
		for(int i =0; i<=n; i++)
			for(int j =0; j<=c; j++)
				taken[i][j] = 0;
		for(int i =1; i<=n; i++)//found at https://en.wikipedia.org/wiki/Change-making_problem#Simple_dynamic_programming
			for(int j =1; j<=c; j++)
				if(coins[i-1] == j)
				{
					mat[i][j] = 1;
					taken[i][j] = 1;
				}
				else if(coins[i-1] > j)
				{
					mat[i][j] = mat[i-1][j];
					taken[i][j] = 0;
				}
				else
				{
					int val = 1 + mat[i][j-coins[i-1]];
					if(val<mat[i-1][j])
					{
						mat[i][j] = val;
						taken[i][j] = taken[i][j-coins[i-1]] + 1;
					}
					else
					{
						mat[i][j] = mat[i-1][j];
						taken[i][j] = 0;
					}
				}
		vector<int> it = vector<int>(n+1, 0);
		int col = c;
		for(int row = n; row>=0; row--)
		{
			it[row-1] = taken[row][col];
			col-=taken[row][col] * coins[row-1];
		}

		cout<<"Case #"<<z<<": ";
		int sum = 0;
		for(int i =0; i<n; i++)
			sum+=it[i] * coins[i];

		it[0]+= c-sum;
		for(int i =0; i<n; i++)
			cout<<it[i]<<" ";

		cout<<"\n";
	}
}
