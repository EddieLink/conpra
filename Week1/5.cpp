#include <stdio.h>
int points;

int game[10005][10005], n;
int snake[10000][2];


void initZero()
{
	points = 0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			game[i][j] = 0;
}
void display(char s = ' ')
{
	return;
	printf("Strategy: %c\n", s);
	for(int i =1; i<=n; i++)
	{
		for(int j = 1; j<=n; j++)
		{
			if(game[i][j] == 2)
				printf("S");
			else if(game[i][j] == 0)
				printf("0");
			else
				printf("X");
		}
		printf("\n");
	}
	printf("\n\n");
}
int moveSnake(int dir)
{
	int d1,d2;

	switch(dir)
	{
		case 0:
		{
			d1 = -1;
			d2 = 0;
			break;
		}
		case 1:
		{
			d1 = 0;
			d2 = 1;
			break;
		}
		case 2:
		{
			d1 = 1;
			d2 = 0;
			break;
		}
		default:
		{
			d1 = 0;
			d2 = -1;
		}
	}
	int newCoord[2];
	newCoord[0] = snake[points][0] + d1;
	newCoord[1] = snake[points][1] + d2;

	if(newCoord[0] > n)
		newCoord[0] = 1;
	if(newCoord[0] <=0)
		newCoord[0] = n;
	if(newCoord[1] > n)
		newCoord[1] = 1;
	if(newCoord[1] <=0)
		newCoord[1] = n;


	int val = game[newCoord[0]][newCoord[1]];

	if(val == 1)
	{
		points++;
		game[newCoord[0]][newCoord[1]] = 2;
		snake[points][0] = newCoord[0];
		snake[points][1] = newCoord[1];
	}
	else
	{
		if(game[newCoord[0]][newCoord[1]] == 2 && ((snake[0][0] != newCoord[0]) || (snake[0][1] != newCoord[1])))
			return -1;

		game[snake[0][0]][snake[0][1]] = 0;
		if(points>0)
		{
			for(int i =0; i<points; i++)
			{
				snake[i][0] = snake[i+1][0];
				snake[i][1] = snake[i+1][1];
			}

		}

		snake[points][0] = newCoord[0];
		snake[points][1] = newCoord[1];
		game[newCoord[0]][newCoord[1]] = 2;

	}
	return 0;
}


int main()
{

	int t, m;
	freopen("input","r",stdin);

	scanf("%d",&t);

	for(int z = 0; z<t; z++)
	{
				// display();

		scanf("%d",&n);
		initZero();
		scanf("%d",&m);
		scanf("%d%d",&snake[0][1],&snake[0][0]);
		for(int a=0; a<m; a++)
		{
			int c1,r1,w,h;
			scanf("%d%d%d%d",&c1,&r1,&w,&h);

			for(int i =r1; i<r1+h; i++)
				for(int j = c1; j< c1+w; j++)
					game[i][j] = 1;
		}
		game[snake[0][0]][snake[0][1]] = 2;

		int l;
		scanf("%d",&l);
		char strategy[10002];
		int dir = 1;
		scanf("%s",strategy);
		int steps = 0;
		for(int i =0; i<l; i++)
		{
			// if(z == 3)

			switch(strategy[i])
			{
				case 'R':
				{
					dir++;
					if(dir>3)
						dir = 0;
					break;
				}
				case 'L':
				{
					dir--;
					if(dir<0)
						dir = 3;
					break;
				}
			}
			if(moveSnake(dir) == -1)
				break;
			steps++;
			// if(z == 3)
			// {
				display(strategy[i]);

			// }

		}
		printf("Case #%d: %d %d\n", z+1, steps, points);


	}
}
