#include <iostream>
#include <vector>
using namespace std;

#define MAX 15
int n,m;
int mat[MAX][MAX];
int dr[MAX][MAX];
int tools;
bool finished;
void backtr(int x, int y)
{
	dr[x][y] = 1;
	if(mat[x][y] == 1) tools--;
	if(!tools && !finished)
	{
		cout<<"yes\n";
		finished = true;
	}
	if(finished) return;

	if(x-1>=0 && mat[x-1][y]!=-1 && dr[x-1][y] == -1)
		backtr(x-1,y);
	if(x+1<n && mat[x+1][y]!=-1 && dr[x+1][y] == -1)
		backtr(x+1,y);
	if(y-1>=0 && mat[x][y-1]!=-1 && dr[x][y-1] == -1)
		backtr(x,y-1);
	if(y+1<m && mat[x][y+1]!=-1 && dr[x][y+1] == -1)
		backtr(x,y+1);

	dr[x][y] = -1;
	if(mat[x][y] == 1) tools++;
}
int main()
{
    int t;
    cin>>t;
    for(int z =1; z<=t; z++)
    {
		tools = 0;
		finished = false;
		cin>>m>>n;
		int startx,starty;
		for(int i =0; i<n; i++)
		{
			char s[m];
			cin>>s;
			for(int j = 0; j<m; j++)
			{
				dr[i][j] = -1;
				if(s[j] == '_') mat[i][j] = 0;
				else if(s[j] == '#') mat[i][j] = -1;
				else if(s[j] == 'L')
				{
					startx = i;
					starty= j;
					mat[i][j] = 0;
					dr[i][j] = 1;
				}
				else
				{
					mat[i][j] = 1;
					tools++;
				}
			}
		}
		cout<<"Case #"<<z<<": ";
		backtr(startx, starty);
		if(!finished)
			cout<<"no\n";
    }
}
