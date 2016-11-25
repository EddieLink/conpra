#include <stdio.h>
#include <vector>
#include <utility>
using namespace std;

#define MAX 25000

int size[MAX];
int parent[MAX];
int n,m;

int unionFind(int x)
{
	if(x == parent[x])
		return x;
	//return unionFind(parent[x]);
	parent[x] = unionFind(parent[x]);
	return parent[x];
}
void unionMerge(int x, int y)
{
	int fx = unionFind(x);
	int fy = unionFind(y);

	if(size[fx] <= size[fy])
	{
		parent[fx] = fy;
		size[fy]+=size[fx];
	}
	else
		unionMerge(y,x);
}
int main()
{
	//freopen("input6","r",stdin);
	int t;
	scanf("%d\n",&t);
	vector<int> q[MAX];
	vector <pair<int,int> > friends;
	vector <pair<int,int> > enemies;
	for(int z =1; z<=t; z++)
	{

		scanf("%d %d\n", &n, &m);
		friends.clear();
		enemies.clear();
		for(int i =0; i<n; i++)
		{
			size[i] = 1;
			parent[i] = i;
			q[i].clear();
		}
		for(int i =0; i<m; i++)
		{
			char a;
			int x, y;
			scanf("%c %d %d\n", &a, &x, &y);
			x--;
			y--;
			if(a == 'F')
			{
				friends.push_back(make_pair(x, y));
				continue;
			}
			enemies.push_back(make_pair(x,y));
		}
		for(int i =0; i<friends.size(); i++)
			unionMerge(friends[i].first, friends[i].second);
		for(int i =0; i<enemies.size(); i++)
		{
			int fx = unionFind(enemies[i].first);
			int fy = unionFind(enemies[i].second);
			q[fx].push_back(fy);
			q[fy].push_back(fx);
		}
		for(int i =0; i<n; i++)
			for(int j =1; j<q[i].size(); j++)
				unionMerge(q[i][0], q[i][j]);
		printf("Case #%d: ", z);
		int ct = 0;
		int f = unionFind(0);
		for(int i =0; i<n; i++)
			if(parent[i] == f || unionFind(i) == f)
				ct++;
        if(ct>n/2)
			printf("yes\n");
		else
			printf("no\n");
	}
	return 0;


}
