#include <stdio.h>
#include <queue>
#include <limits.h>
using namespace std;

#define MAX 1000
int main()
{
    int t;
    scanf("%d\n",&t);
    for(int z = 1; z<=t; z++)
    {
		int n,m;
		scanf("%d%d\n",&n,&m);
		int dist[MAX], pred[MAX];

		int mat[MAX][MAX] = {{0,0}};


		for(int i=0; i<m; i++)
		{
			int x,y,z;
			scanf("%d%d%d\n", &x, &y, &z);
			x--;y--;
			mat[x][y] = mat[y][x] = z;

		}
		for(int i =0; i<n; i++)
		{
			dist[i] = INT_MAX;
			pred[i] = -1;
		}
		dist[0] = 0;

		queue<int> q;
		q.push(0);
		while(!q.empty())
		{
			int w = q.front();
			q.pop();
			for(int i=0; i<n; i++)
			{
				if(!mat[w][i])
					continue;
				if(dist[i] > dist[w] + mat[w][i])
				{
					dist[i] = dist[w] + mat[w][i];
					pred[i] = w;
					q.push(i);
				}
			}
		}
		printf("Case #%d: %d\n", z, dist[n-1]);
	}
}
