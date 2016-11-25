#include <stdio.h>

int main()
{
	int n;
	scanf("%d",&n);
	int i =0;
	char c[101];
	for(i =0; i<n; i++)
	{
		scanf("%s",c);
		printf("Case #%d: Hello %s!\n",i+1,c);
	}
}

