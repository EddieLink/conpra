#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
using namespace std;
int main()
{
	int n, i;
	char str[170];
	char first[170], second[170];
	// freopen("input","r",stdin);

	scanf("%d\n",&n);
	// n = 1;
	// printf("%s",str);
	for(i =0; i<n; i++)
	{
		char *v = fgets(str, sizeof(str), stdin);
		int x = (int)(strchr(str, '#')-str);

		strcpy(first, str);
		first[x] = '\0';
		int len = atoi(first);

		strcpy(second, str+x+len+1);
		second[strlen(second)-1] = '\0';

		strcpy(first, str+x+1);
		first[len] = '\0';
		strcpy(second+strlen(second), first);
		printf("Case #%d: %s\n",i+1, second); 
	}
}