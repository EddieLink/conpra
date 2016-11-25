#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	freopen("input2", "w", stdout);
	srand(time(NULL));
	int n = rand() % 10000;
	int m = rand() % 10000;
	printf("1\n%d %d\n", n, m);
	for(int i =0; i<n; i++)
		printf("%d\n", rand() % 1000);

	for(int i =0; i<m; i++)
	{
		int x = rand() % n +1;
		int y = rand() % n + 1;
		printf("%d %d\n", x,y);
	}
}
