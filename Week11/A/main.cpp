#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct lec{
	int score, index, length;
	lec(int s, int i, int l): score(s), index(i),length(l) {};
};
int main()
{
	int t; cin>>t;
	for(int z =1; z<=t; z++)
	{
		int m,n; cin>>m>>n;
		vector<lec> ls;
		for(int i =0; i<n; i++)
		{
			int p,l,s; cin>>p>>l>>s;
			ls.insert(ls.begin(), p, lec(s, i, l));
		}
		int mat[ls.size() + 1][m + 1];
		bool take[ls.size()+1][m+1];
		for(int i =0; i<= ls.size(); i++)
			for(int j =0; j<= m; j++)
			{
				mat[i][j] = 0;
				take[i][j] = false;
			}
		for(int i =1; i<=ls.size(); i++)
			for(int j =0; j<=m; j++)
				if(ls[i-1].length > j)
					mat[i][j] = mat[i-1][j];
				else
				{
					int val = mat[i-1][j-ls[i-1].length] + ls[i-1].score;
					if(val>mat[i-1][j])
						take[i][j] = true;
					else
						take[i][j] = false;
					mat[i][j] = max(val, mat[i-1][j]);
				}

		int sol = mat[ls.size()][m];
		vector<int> it;
		int col = m;
		for(int row = ls.size(); row>=1; row--)
		{
			if(take[row][col])
			{
				it.push_back(ls[row-1].index+1);
				col-=ls[row-1].length;
			}
		}

		cout<<"Case #"<<z<<": ";
		for(int i =0; i<it.size(); i++)
			cout<<it[i]<<" ";
		cout<<"\n";

	}
}
