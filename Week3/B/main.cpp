#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 10000
struct tup{
  int x, y, z;
};
int size[MAX],parent[MAX];

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
int main()
{
  int t;
  scanf("%d\n", &t);
  for(int z = 1; z<=t; z++)
  {
    int n,m;
    vector <tup> k;
    scanf("%d%d\n",&n, &m);
    for(int i=0; i<m;  i++)
    {
      tup x;
      scanf("%d%d%d\n",&x.x, &x.y, &x.z);
      x.x--;
      x.y--;
      size[x.x] =size[x.y] = 1;
      parent[x.x] = x.x;
      parent[x.y] = x.y;
      k.push_back(x);
    }
    sort(k.begin(), k.end(), [](tup x, tup y){return x.z<y.z;});
    int nec = 0;
    printf("Case #%d: ",z);
    for(int i =0; i<k.size(); i++)
      if(unionFind(k[i].x) != unionFind(k[i].y))
      {
        unionMerge(k[i].x,k[i].y);
        nec+=k[i].z;
        if(size[unionFind(0)] == n)
          printf("%d\n",nec);
      }
    if(n-size[unionFind(0)]>0)
      printf("impossible\n");
  }
}
