#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 251

int n, d, m;
struct tup{
	int x,y,z;
};
int mat[MAX][MAX];
vector<tup>k;
int parent[MAX];
int size[MAX];
int unionFind(int x)
{
	if(x == parent[x])
		return x;
	parent[x] = unionFind(parent[x]);
	return parent[x];
}
void unionMerge(int x, int y)
{
	int fx = unionFind(x);
	int fy = unionFind(y);

	if(size[fx]<=size[fy])
	{
		parent[fx] = fy;
		size[fy] += size[fx];
	}
	else
		unionMerge(y,x);
}
bool callback(tup x, tup y)
{
	return x.z<y.z;
}
int main()
{
	freopen("input","r",stdin);
	int t;
	scanf("%d\n",&t);
	for(int z = 1; z<=t; z++)
	{
		bool dung[MAX] = {};
		k.clear();
		scanf("%d%d%d\n", &n, &m, &d);
		for(int i=0; i<n; i++)
		{
			size[i] = 1;
			parent[i] = i;
		}
		for(int i =0; i<d; i++)
		{
			int x;
			scanf("%d\n",&x);
			dung[x] =true;
		}
		for(int i =0; i<m; i++)
		{
			tup x;
			scanf("%d%d%d\n", &x.x,&x.y,&x.z);
			k.push_back(x);
			mat[x.x][x.y] = mat[x.y][x.x] = x.z;
		}
		int cost = 0;
/*		for(int i =1; i<=n; i++)
		{
			if(dung[i] || i==1) continue;
			for(int j =1; j<=n; j++)
			{
				if(!mat[i][j]) continue;
				for(int k = 1;k<=n; k++)
				{
					if(!mat[i][k]) continue;
					mat[j][k] = mat[k][j] = mat[i][j] + mat[i][k];
					mat[i][k] = mat[k][i] = 0;
				}
				mat[i][j] = mat[j][i] = 0;
			}
		}

       bool visited[MAX] = {};
       visited[1] = true;
		tup x;
       vector <tup> q;
       for(int i =1; i<=n; i++)
			if(mat[1][i])
			{
				x.x = mat[1][i];
				x.y = 1;
				x.z = i;
				q.push_back(x);
			}

		int vis = 0;
		while(vis<d)
		{
			sort(q.begin(), q.end(),callback);
			tup w = q.front();
			q.erase(q.begin());
            cost+=w.x;
            vis++;
            visited[w.z] = true;
            for(int i =1; i<=n; i++)
				if(!visited[i] && mat[w.z][i])
				{
					x.x = mat[w.z][i];
					x.y = w.z;
					x.z = i;
					q.push_back(x);
				}
		}*/

		sort(k.begin(), k.end(), [](tup x, tup y){return x.z<y.z;});
        for(int i=0; i<k.size(); i++)
        {
			if(unionFind(k[i].x) == unionFind(k[i].y))
				continue;
			int loc_d= 0;
			if(dung[k[i].x])
				loc_d++;
			if(dung[k[i].y])
				loc_d++;
			if(!loc_d)
				continue;
			unionMerge(k[i].x,k[i].y);
			cost+=mat[k[i].x][k[i].y];
			k.erase(k.begin()+i);
		}
		for(int i =0; i<k.size(); i++)
		{
			int fx,fy;
			fx = unionFind(k[i].x);
			fy = unionFind(k[i].y);
			if(fx == fy || (size[fx] == 1 && !dung[fx]) && (size[fy] == 1 && !dung[fy]))
				continue;
			unionMerge(k[i].x,k[i].y);
			cost+=mat[k[i].x][k[i].y];
			k.erase(k.begin()+i);
		}
		printf("Case #%d: %d\n",z,cost);

	}
}
