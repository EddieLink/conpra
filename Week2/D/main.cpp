//Algorithm from http://stackoverflow.com/questions/11218746/bridges-in-a-connected-graph/11221469#11221469

#include <stdio.h>
int n,m;
int g[10000][10000];
int low[10000], pre[10000];
int counter = 0;
int bridges[10000];
int bridgeCount;

void dfs(int u, int v)
{
	pre[v] = counter++;
	low[v] = pre[v];
	for(int i=0; i<n; i++)
	{
		if(!g[v][i])
			continue;
		if(pre[i] == -1)
		{
            dfs(v, i);
            low[v] = (low[v]>low[i])?low[i]:low[v];
            if(low[i] >= pre[i])
				bridges[bridgeCount++] = g[v][i];
		}
		else if( i != u)
			low[v] = (low[v]>pre[i])?pre[i]:low[v];
	}
}
void bridge()
{
	bridgeCount =0 ;
	counter = 0;
    for(int i =0; i<n; i++)
		low[i] = pre[i] = -1;
	for(int i=0; i<n; i++)
		if(pre[i] == -1)
			dfs(i,i);
	for(int i=0; i<n; i++)
		for(int j =0; j<m; j++)
			g[i][j] = g[j][i] = 0;
}

int main()
{
	//freopen("input","r",stdin);
	int t;
	scanf("%d",&t);
	for(int z =1; z<=t; z++)
	{
		scanf("%d%d",&n,&m);
		for(int i =0; i<m; i++)
		{
			int x,y;
			scanf("%d%d\n",&x,&y);
			g[x-1][y-1] = g[y-1][x-1] = i+1;

		}
		bridge();
		printf("Case #%d: ", z);
		for(int i =0; i<bridgeCount; i++)
			for(int j = i+1; j<bridgeCount; j++)
				if(bridges[j]<bridges[i])
				{
					int aux = bridges[i];
					bridges[i] = bridges[j];
					bridges[j] = aux;
				}
		for(int i=0; i<bridgeCount; i++)
			printf("%d ", bridges[i]);
		printf("\n");
	}
}
