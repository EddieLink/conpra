#include <stdio.h>
#include <limits.h>
#include <queue>
using namespace std;
#define MAX 1000
int main()
{
	int t;
	scanf("%d\n",&t);
	for(int z = 1; z<=t;  z++)
	{
		int n;
		int mat[MAX][MAX] = {{0,0}};
		int dist[MAX] = {-INT_MAX};
		int time[MAX] = {0}, pred[MAX] = {1};

		scanf("%d\n", &n);
		for(int i=0; i<n; i++)
		{
			int b;
			scanf("%d%d", &time[i], &b);
			for(int j=0; j<b; j++)
			{
				int x;
				scanf("%d",&x);
				x--;
				mat[i][x] = 1;
				pred[x]++;
			}
		}
		pred[0] = 0;
		queue<int> q;
		q.push(0);
		dist[0] = 0;
		while(!q.empty())
		{
			int v = q.front();
			q.pop();
			for(int j =0; j<n; j++)
				if(mat[v][j])
					pred[j]--;
			for(int i=0; i<n; i++)
			{
				if(!mat[v][i])
					continue;
				if(!pred[i])
					q.push(i);
				if(dist[v] + time[v]>=dist[i])
					dist[i] = dist[v]+time[v];
			}
		}
		printf("Case #%d: %d\n", z, dist[n-1] + time[n-1]);

	}
}
