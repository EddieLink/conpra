#include <stdio.h>
int parent[10001], s[10001];
int findUnion(int x)
{
	if(parent[x] == x)
		return x;
	else
		return findUnion(parent[x]);
}
void mergeUnion(int x, int y)
{
	int fx = findUnion(x);
	int fy = findUnion(y);
	if(s[fx]<=s[fy])
	{
		parent[fx] = fy;
		s[fy]+= s[fx];
	}
	else
		mergeUnion(y,x);
}

int main()
{
	//freopen("input", "r",stdin);
	int t,a,b,c;
	scanf("%d", &t);
	int money[10001];
	bool married[10001];



	for(int z =0; z<t; z++)
	{
		scanf("%d%d%d",&a,&b,&c);
		for(int i=1; i<a; i++)
		{
			scanf("%d",&money[i]);
			s[i] = 1;
			parent[i] = i;
			married[i] = false;
		}
		parent[a] = a;
		married[a] = false;
		s[a] = 1;
		for(int i=0; i<b; i++)
		{
			int x,y;
			scanf("%d%d\n",&x,&y);
			mergeUnion(x,y);
		}
		for(int i=0; i<c; i++)
		{
			int x, y;
			scanf("%d%d\n",&x,&y);
			married[x] = married[y] = true;
			mergeUnion(x,y);
		}
		int setA = findUnion(a);
			int max = -1;
		for(int i =1; i<a; i++)
		{
			if(!married[i] && findUnion(i) != setA && max<money[i])
				max = money[i];
		}
		if(max!=-1)
			printf("Case #%d: %d\n",z+1, max);
		else
			printf("Case #%d: impossible\n", z+1);





	}
}
