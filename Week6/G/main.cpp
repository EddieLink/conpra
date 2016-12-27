#include <iostream>
#include <vector>
using namespace std;
#define MAX 50
int colors[MAX];
vector<int> g[MAX];
int n,k;

bool found;

bool verify(int p)
{
	for(int i =0; i<g[p].size(); i++)
		if(colors[g[p][i]] == colors[p])
			return false;
	return true;
}
void displaySol()
{
	if(found)
		return;
	for(int i =0; i<n; i++)
		cout<<colors[i]+1<<" ";
	cout<<"\n";
}
void backtr(int p)
{
	if(p == n)
	{
		displaySol();
		found = true;
	}
	if(found) return;
	for(int i =0; i<k; i++)
	{
		colors[p] = i;
		if(verify(p) && !found)
			backtr(p+1);
		colors[p] = -1;
	}
}

int main()
{
	int t;
	cin>>t;
	for(int z = 1; z<=t; z++)
	{
		int m;
		found = false;
		cin>>n>>m>>k;
		for(int i =0; i<n; i++)
		{
			g[i].clear();
			colors[i] = -1;
		}
		for(int i =0; i<m; i++)
		{
			int x, y;
			cin>>x>>y;
			x--;y--;
			g[x].push_back(y);
			g[y].push_back(x);
		}
		cout<<"Case #"<<z<<": ";
		backtr(0);
		if(!found)
			cout<<"impossible\n";
	}
}
