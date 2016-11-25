#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 1001

int size[MAX], parent[MAX];
struct tup{
	int x, y;
	double z;
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
		size[fy]+=size[fx];
	}
	else
		unionMerge(y,x);
}
double powerNeeded(tup x, tup y)
{
	return pow(x.x - y.x,2) + pow(x.y - y.y,2);
}

int main()
{
	int t;
	scanf("%d\n",&t);
	for(int z = 1; z<=t; z++)
	{
		vector<tup> v;
		tup plane;
		plane.x = 0;
		plane.y = 0;
		plane.z = 200*200;
		v.push_back(plane);

		int n;
		scanf("%d\n",&n);
		size[0] = 1;
		parent[0] = 0;
		for(int i=1; i<=n; i++)
		{
			size[i] = 1;
			parent[i] = i;
			tup x;
			int c;
			scanf("%d%d%d\n", &x.x, &x.y, &c);
			x.z = (double)c;
			v.push_back(x);
		}
		vector<tup> k;
		for(int i =0; i<v.size(); i++)
			for(int j = i+1; j<v.size(); j++)
			{
				tup x;
				x.z = powerNeeded(v[i],v[j]);
				x.x = i;
				x.y = j;
				if((x.z <= v[i].z) && (x.z<=v[j].z))
					k.push_back(x);
			}
			sort(k.begin(), k.end(), [](tup x, tup y){ return x.z<y.z;});
			int mst = 0;
			for(int i =0; i<k.size(); i++)
				if(unionFind(k[i].x) != unionFind(k[i].y))
				{
						unionMerge(k[i].x, k[i].y);
						mst+=k[i].z*2;
				}
			printf("Case #%d: ", z);
			if(size[unionFind(1)]<=n || unionFind(0) != unionFind(1))
				printf("impossible\n");
			else
				printf("%d\n", mst);
		}

	}
