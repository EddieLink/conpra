#include <stdio.h>
#include <queue>
using namespace std;
#define MAX 400

int n, mat[MAX][MAX];
int visited[MAX];
void dfs(int x, int prec)
{
	if(visited[x]>mat[x][prec])
		return;
    visited[x] = mat[x][prec];
    queue<int> q;
    for(int i =0; i<n; i++)
		if(visited[i]<mat[i][x])
			q.push(i);
	while(!q.empty())
	{
		dfs(q.front(), x);
		q.pop();
	}
}
int main()
{
	int t;
	scanf("%d\n",&t);
    for(int z = 1; z<=t; z++)
    {
		scanf("%d\n",&n);
		for(int i =0; i<n; i++)
		{
			visited[i] = 0;
			for(int j =0; j<n; j++)
				scanf("%d", &mat[i][j]);
		}

		dfs(0, 0);
		int sum =0;
		for(int i =1; i<n; i++)
			sum+=visited[i];
		printf("Case #%d: %d\n", z, sum);
	}
}
