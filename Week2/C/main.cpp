#include <stdio.h>
#include <queue>
#include <list>
using namespace std;

int counter;
//int g[10000][10000];
list <int> g[10000];
int n, m;
int points[10000];
bool visited[10000];
bool change;
int maxPoints;
queue <int> q;

void init()
{
	int s = q.size();
	for(int i =0; i<s; i++)
		q.pop();
	counter = 0;
	maxPoints = 0;
	for(int i =0; i<n; i++)
	{
		g[i].clear();
		visited[i] = false;
	}

}
bool over(int i)
{
	if(g[i].size() == 0)
		return false;
	if(visited[i])
		return true;
	for(list<int>::iterator j= g[i].begin(); j != g[i].end(); j++)
		if(!visited[*j])
			return true;
	return false;
}
void dfs(int x)
{
	if(visited[x])
		return;
	visited[x] = true;
	change = true;
	maxPoints+=points[x];
	for(int i=0; i<n; i++)
	{
		if(visited[i] || i==x)
			continue;
		if(!over(i))
			q.push(i);
	}
	if(q.size()>0)
	{
		x = q.front();
		q.pop();
		if(!visited[x])
			dfs(x);
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	for(int z =1; z<=t; z++)
	{
		scanf("%d%d\n", &n, &m);
		init();
		for(int i=0; i<n; i++)
			scanf("%d",&points[i]);
		for(int i =0; i<m; i++)
		{
			int x,y;
			scanf("%d%d\n",&x,&y);
			g[y-1].push_front(x-1);
		}
		change = true;
		while(change)
		{
			change = false;
			for(int i =0; i<n; i++)
				if(!over(i))
					dfs(i);
		}
		printf("Case #%d: %d\n", z, maxPoints);
	}
}
