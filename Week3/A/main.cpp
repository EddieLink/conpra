#include <stdio.h>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX 1000

int size[MAX], parent[MAX];
struct tuple{
	int x, y, z;
};

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
		size[fx]+=size[fy];
	}
	else
		unionMerge(y,x);
}

bool sortCallback(tuple x, tuple y)
{
	return x.z<=y.z;
}
int main()
{
	int t;
	scanf("%d\n",&t);
	for(int z = 1; z<=t; z++)
	{
		vector<tuple> v;
		int n;
		scanf("%d\n",&n);
		int mat[MAX][MAX] = {{0,0}};
		for(int i=0; i<n; i++)
		{
			size[i] = 1;
			parent[i] = i;
			tuple x;
			scanf("%d%d%d\n", &x.x, &x.y, &x.z);
			v.push_back(x);
		}
		vector<tuple> k;
		for(int i =0; i<v.size(); i++)
			for(int j = i+1; j<v.size(); j++)
			{
				tuple x;
				x.z = abs(v[i].x - v[j].x) + abs(v[i].y-v[j].y) + abs(v[i].z - v[j].z);
				x.x = i;
				x.y = j;
				k.push_back(x);
			}
		sort(k.begin(), k.end(), sortCallback);
		int mst = 0;
		for(int i =0; i<k.size(); i++)
			if(unionFind(k[i].x) != unionFind(k[i].y))
			{
					unionMerge(k[i].x, k[i].y);
					mst+=k[i].z;
			}
		printf("Case #%d: %d\n", z, mst);
	}
}
