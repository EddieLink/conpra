#include <stdio.h>

int gcd(int x, int y)
{
	int t;
	if(x<y)
		return gcd(y,x);
	while(y!=0)
	{
		t = y;
		y = x % t;
		x = t;
	}
	return x;
}

int main()
{
	int t;
	scanf("%d", &t);
	for(int z = 1; z<=t; z++)
	{
		int current;
		int n;
		scanf("%d",&n);
		for(int i =0; i<n; i++)
		{
			int x;
			scanf("%d",&x);
			if(!i)
				current = x;
			else
				current = gcd(current,x);
		}
		printf("Case #%d: %d\n", z, current);
	}
}
