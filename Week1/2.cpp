#include <stdio.h>
int main()
{
	long long unsigned en = 0;
	int n;
	scanf("%d", &n);
	int i;
	for(i =0; i<n; i++)
	{
		scanf("%llu",&en);
		en*=(unsigned long long int)299792458*(unsigned long long int)299792458;
		printf("Case #%d: %llu\n", i+1, en);
	}
}