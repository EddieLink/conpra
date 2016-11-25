#include <stdio.h>
#include <vector>
#include <limits.h>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX 10001
int n,s,l;
struct tup
{
	int x,y,z;
};

int calculateLength(int die, vector<tup> c[])
{
	int dist[MAX];
	fill_n(dist, n+1, INT_MAX);
	queue<int> q;
	q.push(1);
	dist[1] = 0;
	while(!q.empty())
	{
		int w = q.front();
		q.pop();

		if(c[w].size()>0)
		{
			if(c[w][0].z == 1)
			{
				if(dist[w]>=dist[c[w][0].x])
					return INT_MAX;
				dist[c[w][0].x] = dist[w];
				q.push(c[w][0].x);
				continue;
			}
			else if(dist[c[w][0].x] >= dist[w])
			{
				dist[c[w][0].x] = dist[w];
				q.push(c[w][0].x);
			}
		}
		int next = w+die;
		if(next>n)
			next = n;
		if(dist[next] > dist[w]+1)
		{
			dist[next] = dist[w]+1;
			q.push(next);
		}
	}
	return dist[n];
}

int main()
{
	freopen("input2","r",stdin);
	int t;
	scanf("%d\n",&t);
	for(int z = 1;z<=t ; z++)
	{
        int x, y;
		tup x1;
		scanf("%d%d%d\n", &n, &s, &l);
		vector<tup>c[n+1];
		for(int i=0; i<s; i++)
		{
			scanf("%d%d", &x,&y);
			x1.x = y;
			x1.y = 0;
			x1.z = 1;
			c[x].clear();
			c[x].push_back(x1);
		}
		for(int i =0; i<l; i++)
		{
			scanf("%d%d", &x,&y);
			if(c[x].size()>0)
				continue;
			x1.x = y;
			x1.y = 0;
			x1.z = 2;
			c[x].push_back(x1);
		}
		int min = INT_MAX;
		vector<int>p;

		for(int i =1; i<=6; i++)
		{
			int length = calculateLength(i,c);
			if(length == min)
				p.push_back(i);
			if(length<min)
			{
				min = length;
				p.clear();
				p.push_back(i);
			}
		}

		printf("Case #%d: ", z);
		if(p.empty() || min == INT_MAX || !min)
			printf("impossible");
		else
			for(int i =0; i<p.size(); i++)
				printf("%d ", p[i]);
		printf("\n");
	}
}
