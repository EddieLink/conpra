#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

int mat[9][9];
int open;
vector<int> findSol(int x, int y)
{
	bool sol[10];
	for(int i =1; i<10; i++)
		sol[i] = true;
	for(int i =0; i<9; i++)
	{
		if(i != y && mat[x][i] != -1)
			sol[mat[x][i]] = false;
		if(i!=x && mat[i][y] != -1)
			sol[mat[i][y]] = false;
	}
	int vert = x/3;
	int hor = y/3;
	for(int i = vert*3; i<vert*3+3; i++)
		for(int j = hor*3; j<hor*3+3; j++)
			if((i!=x || j!=y) && mat[i][j] != -1)
				sol[mat[i][j]] = false;
	vector<int> pos;
	for(int i =1; i<10; i++)
		if(sol[i]) pos.push_back(i);
	return pos;
}
bool finished;
void displaySol()
{
	for(int i =0; i<9; i++)
	{
		for(int j =0; j<9; j++)
			cout<<mat[i][j];
		cout<<"\n";
	}
}
void backtr(int x, int y)
{
	if(finished)
		return;
	if(!open)
	{
		finished =true;
		displaySol();
		return;
	}
	if(y>=9)
		backtr(x+1,0);
	if(x>=9)
		return;
	if(mat[x][y]!=-1)
	{
		backtr(x,y+1);
		return;
	}
	vector<int> pos = findSol(x,y);
	if(finished)
		return;
	open--;
	for(int i =0; i<pos.size(); i++)
	{
		mat[x][y] = pos[i];
		backtr(x, y+1);
		if(finished)
			return;
	}
	mat[x][y] = -1;
	open++;
}
int main()
{
    int t;
    cin>>t;
    for(int z = 1; z<=t; z++)
    {
		finished = false;
		open = 0;
		for(int i =0; i<9; i++)
		{
			string s;
			cin>>s;
			for(int j =0; j<9; j++)
			{
				if(s.at(j) != '?')
				{
					int x = s[j] - '0';
					mat[i][j] = x;

				}
				else
				{
					open++;
					mat[i][j] = -1;
				}
			}
		}
		cout<<"Case #"<<z<<":\n";
		backtr(0,0);

    }
}
