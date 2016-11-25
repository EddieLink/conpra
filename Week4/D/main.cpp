#include <stdio.h>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

#define MAX 201
char mat[MAX][MAX];
vector<int> v[MAX*MAX];

struct tup{
	int x,y;
};
vector<tup> used[MAX*MAX];
queue<int> q;
int w,h;
char u = '_';
char p = '@';
int dist[MAX*MAX];
void check(int x, int y, int i, int j)
{
	int num_n = (x-1)*w + y;
	int num_o = (i-1)*w + j;
	if(x<=h && x>0 && y<=w && y>0 && mat[x][y] == u)
	{
		v[num_n].push_back(num_o);
		v[num_o].push_back(num_n);
	}
}
void use(int x, int y, int old, int p1, int p2)
{
	tup t;
	int m = (x-1)*w + y;
	if(used[old].size() == 3)
		return;
	if(dist[m] > dist[old]+1)
	{
		t.x = p1;
		t.y = p2;
		used[m] = used[old];
		used[m].push_back(t);
		dist[m] = dist[old]+1;
		q.push(m);
	}
}
void checkUse(int m, int dir)
{
	int x = m/w + 1;
	int y = m%w;
	switch(dir)
	{
		case 0:
		{
			if(x+2<=w && mat[x+1][y] == p && mat[x+2][y] == u)
				use(x+2, y, m, x+1, y);
			break;
		}
		case 1:
		{
			if(x-2>0 && mat[x-1][y] == p && mat[x-2][y] == u)
				use(x-2,y,m, x-1, y);
			break;
		}
		case 2:
		{
			if(y+2<=w && mat[x][y+1] == p && mat[x][y+2] ==u)
				use(x,y+2,m, x, y+1);
			break;
		}
		default:
		{
			if(y-2>0 && mat[x][y-1] == p && mat[x][y-2] ==u)
				use(x,y-2,m, x, y-1);
		}
	}
}
int main()
{
	freopen("input","r",stdin);
	int t;
	scanf("%d\n",&t);
	int start, end;
	for(int z = 1; z<=t; z++)
	{
		scanf("%d%d\n",&w,&h);
		for(int i =1; i<=h; i++)
		{
			for(int j = 1; j<=w; j++)
			{
				scanf("%c",&mat[i][j]);
				int num = (i-1)*w+j;
				if(mat[i][j] == '*')
				{
					start = num;
					mat[i][j] = u;
				}
				if((i == h || i ==1 || j == w|| j== 1) && mat[i][j] == u)
					end =num;
				dist[num] = INT_MAX;
				used[num].clear();
				v[num].clear();
			}
			scanf("\n");
		}
		for(int i= 1; i<=h; i++)
			for(int j=1; j<=w; j++)
			{
				if(mat[i][j]!= u)
					continue;
				check(i+1, j, i, j);
				check(i,j+1, i, j);
			}
		q = queue<int>();
		q.push(start);
		dist[start] = 0;
		while(!q.empty())
		{
			int k = q.front();
			q.pop();
			for(int i =0; i<v[k].size(); i++)
				if(dist[v[k][i]] > dist[k] + 1)
				{
					dist[v[k][i]] = dist[k]+1;
					q.push(v[k][i]);
					used[v[k][i]] = used[k];
				}
			for(int i =0; i<4; i++)
				checkUse(k,i);
		}

		printf("Case #%d:\n", z);
		for(int i =used[end].size()-1; i>=0; i--)
			printf("%d %d\n",used[end][i].y, used[end][i].x);
		for(int i = 3-used[end].size(); i>0; i--)
			printf("unused\n");
	}
}
