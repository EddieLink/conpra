#include <stdio.h>
#include <list>
using namespace std;

#define MAX 20000

int parent[MAX];
int size[MAX];
int n, m;
int unionFind(int x)
{
	if(x <0 || x>n)
		return -1;
	if(parent[x] == x)
		return x;
	int y = unionFind(parent[x]);
	parent[x] = y;
	return y;

	if(x == parent[x])
		return x;
	return unionFind(parent[x]);

}
void unionMerge(int x, int y)
{

	int fx = unionFind(x);
	int fy = unionFind(y);

	if(fx == fy)
		return;
	if(size[fx]>=size[fy])
	{
		parent[fx] = fy;
		size[fy]+=size[fx];
	}
	else
		unionMerge(y,x);
}
struct hate{
	int first, second;
};
int main()
{
	freopen("input2","r",stdin);
	int t;
	scanf("%d\n",&t);
	list <hate> hateRelations;
	list <int> h[MAX];

	for(int z = 1; z<=t; z++)
	{
        scanf("%d%d\n",&n,&m);
		hateRelations.clear();
        for(int i =0; i<n; i++)
		{
			size[i] = 1;
			parent[i] = i;
			h[i].clear();
		}
		bool processed[n][n] = {{false,false}};
        for(int i =0; i<m; i++)
        {
			char x;
			int a, b;
            scanf("%c %d %d\n", &x, &a, &b);

            a--;
            b--;
            if(x == 'F')
				unionMerge(a,b);
			else
			{
				hate x;
				x.first = a;
				x.second = b;
				hateRelations.push_back(x);
			}
		}
		for(list<hate>::iterator  i= hateRelations.begin(); i!=hateRelations.end(); i++)
		{
			int fx = unionFind(i->first);
			int fy = unionFind(i->second);
			h[fx].push_back(fy);
		//	h[fy].push_back(fx);
		}
		for(int i=0; i<n; i++)
		{
			for(list<int>::iterator j = h[i].begin(); j!=h[i].end(); j++)
			{
				if(processed[i][i])
					continue;
				for(list<int>::iterator k = j; k!=h[i].end(); k++)
					unionMerge(*j, *k);
				processed[i][i] = true;
				if(processed[i][*j])
					continue;
				for(list<int>::iterator k = h[*j].begin(); k!= h[*j].end(); k++)
					unionMerge(i, *k);
				processed[i][*j] = true;
			}
		}
		if(size[unionFind(0)] > n/2)
			printf("Case #%d: yes\n", z);
		else
			printf("Case #%d: no\n", z);
	}
}
