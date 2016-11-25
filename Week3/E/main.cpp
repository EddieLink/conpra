#include <stdio.h>
#include <vector>
using namespace std;
#define MAX 150

int mat[MAX][MAX];
vector<int> path;
int n;
void find(int start, int end,  int current_length)
{
	if(start == end)
		return;
	int next = -1;
	for(int i =0; i<n; i++)
	{
		if(i == start)
			continue;
        if(mat[i][end] == current_length - mat[start][i] && mat[i][end]!=0)
		{
			next = i;
			break;
		}
	}
	if(next == -1)
		path.push_back(end);
	else
	{
		find(start, next, mat[start][next]);
		find(path.back(), end, mat[path.back()][end]);
	}

}
int main()
{
	int t;
	scanf("%d\n",&t);
	for(int z = 1; z<=t; z++)
	{
		scanf("%d\n",&n);
		for(int i =0; i<n; i++)
			for(int j =0; j<n; j++)
				scanf("%d", &mat[i][j]);
		path.clear();
		path.push_back(0);
		find(0, n-1, mat[0][n-1]);
		if(path[path.size()-1] != n-1)
			path.push_back(n-1);

		printf("Case #%d: ", z);
		for(int i =0; i<path.size(); i++)
			printf("%d ", path[i] + 1);
		printf("\n");
	}
}
