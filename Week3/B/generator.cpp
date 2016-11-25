#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
  srand(time(NULL));
  freopen("input3","w",stdout);
  int n = 10000;
  int m = 100000;

  printf("1\n%d %d\n", n, m);

  for(int i =0; i<m; i++)
  {
    int x, y, c;
    x = rand()%n;
    y = rand()%n;
    c = rand()%n;

    printf("%d %d %d\n", x,y,c);
  }

}
