#include <stdio.h>
void swapSchools(int schools[][5], int a, int b )
{
	int aux;
	for(int i=0; i<5; i++)
	{
		aux= schools[a][i];
		schools[a][i] = schools[b][i];
		schools[b][i] = aux;
	}
}
int check (int schools[][5], int a, int b, int to)
{
	for(int i=0; i<to; i++)
	{
		if(schools[a][i] < schools[b][i])
			return 1;
		if(schools[b][i]<schools[a][i])
			return -1;
	}
	return 0;
}
int main()
{
	int schools[1000][5];
	int n, t,i,j;

	// freopen("input","r",stdin);

	scanf("%d\n", &t);
	for(i =0; i<t; i++)
	{
		scanf("%d\n",&n);
		printf("Case #%d:\n", i+1);
		for(j = 0; j<n ;j++)
		{
			for(int a =0; a<5; a++)
				scanf("%d",&schools[j][a]);

			for(int a =0; a<5; a++)
				for(int b =a; b<5; b++)
					if(schools[j][a]<schools[j][b])
					{
						int aux = schools[j][a];
						schools[j][a] = schools[j][b];
						schools[j][b] = aux;
					}
		}
		for(int a =0; a<5; a++)
		{
			for(int b =0; b<n; b++)
				for(int c = b+1; c<n; c++)
				{
					if((a>0 && check(schools, b,c, a)  == 0)|| a ==0)
					{
						if(schools[b][a] < schools[c][a])
							swapSchools(schools,b,c);
					}
				}
		}
		for(int a =0; a<n; a++)
		{
			for(int b =0; b<5; b++)
				printf("%d ", schools[a][b]);
			printf("\n");
		}



	}
}