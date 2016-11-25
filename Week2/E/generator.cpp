#include <stdio.h>
#include <stdlib.h>

int print(int n, bool calc = false)
{
	int m = 0;
	for(int i =2; i<n/2 - 1; i++)
		if(!calc)
			printf("F %d %d\n", i+1, i+2);
		else
			m++;
	if(!calc)
		printf("F 1 %d\n", (n/2)+1);
	else
		m++;

	for(int i = (n/2)+1; i<= n; i++)
		if(!calc)
			printf("A 2 %d\n", i);
		else m++;

	return m;

}

int main(int argc, char** argv)
{
	int n = atoi(argv[1]);
	int m = print(n, true);
	freopen("input2", "w", stdout);
//	int n = 19001, m =19001;
	printf("1 %d %d\n", n, m);

	print(n);

}
