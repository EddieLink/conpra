#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
  freopen("inputGen","w",stdout);
  srand(time(NULL));
  int n = 10000;
  printf("1\n");
  int s,l;
  s = rand()%n;
  l = rand()%n;
  printf("%d %d %d\n", n, s, l);
  bool used[n] = {};
  for(int i =0; i<s; i++)
  {
    int x, y;
    x = rand()%n;
    y = rand()%n;
    while(used[x])
      x = rand()%n;
    while(used[y])
      y = rand()%n;
    used[x] = used[y] = true;
    printf("%d %d\n", x,y);
  }
  for(int i= 0; i<l; i++)
  {
    int x, y;
    x = rand()%n;
    y = rand()%n;
    while(used[x])
      x = rand()%n;
    while(used[y])
      y = rand()%n;
    used[x] = used[y] = true;
    printf("%d %d\n", x,y);
  }

}
