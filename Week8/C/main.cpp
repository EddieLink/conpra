#include <iostream>
#include <tuple>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

typedef double T;

struct point{
	T x, y;
};

//only relevant here:
//intersection algorithm from http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/

int orient(point a, point b, point c)
{
	double val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	if(!val) return 0;
	return (val>0)?-1:1;
}
bool onSegment(point p, point q, point r)
{
	if(q.x<=max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y,r.y) && q.y >= min(p.y, r.y))
		return true;
	return false;
}
bool lineIntersect(point a1, point a2, point b1, point b2)
{
	int o1,o2,o3,o4;
	o1 = orient(a1, a2, b1);
	o2 = orient(a1, a2, b2);
	o3 = orient(b1, b2, a1);
	o4 = orient(b1, b2, a2);
	if(o1!=o2 && o3!=o4)
		return true;

	if(!o1 && onSegment(a1,b1,a2)) return true;
	if(!o2 && onSegment(a1, b2, a2)) return true;
	if(!o3 && onSegment(b1, a1, b2)) return true;
	if(!o4 && onSegment(b1, a2, b2)) return true;

	return false;
}
int n;
bool startL[100], endL[100];
bool mat[100][100];
int bfs()
{
	for(int i =0; i<n; i++)
	{
		if(!startL[i])
			continue;
		bool visited[n] = {};
		int d = 0;
		queue<tuple<int,int> > q;
		q.push(make_tuple(i,0));
		while(!q.empty())
		{
			int c = get<0>(q.front());
			visited[c] = true;
			int d = get<1>(q.front());
			q.pop();
			if(endL[c])
				return d;
			for(int j =0; j<n; j++)
				if(mat[c][j] && !visited[j])
					q.push(make_tuple(j,d+1));
		}
	}
	return -1;
}
int main()
{
	int t;
	cin>>t;
	for(int z = 1; z<=t; z++)
	{
		for(int i=0; i<100; i++)
		{
			startL[i] = endL[i] = false;
			for(int j =0; j<100; j++)
				mat[i][j] = false;
		}
		point start,end;
		cin>>n>>start.x>>start.y>>end.x>>end.y;
		vector<vector<point> > lines;
		for(int i =0; i<n; i++)
		{
			int m;
			cin>>m;
			vector<point> x;
			for(int j =0; j<m; j++)
			{
				point a;
				cin>>a.x>>a.y;
				x.push_back(a);
			}
			lines.push_back(x);
		}
		for(int i =0; i<n; i++)
			for(int j = 0; j<lines[i].size()-1; j++)
			{
				if(!orient(start, lines[i][j], lines[i][j+1]) && onSegment(lines[i][j], start, lines[i][j+1]))
					startL[i] = true;
				if(!orient(end, lines[i][j], lines[i][j+1]) && onSegment(lines[i][j], end, lines[i][j+1]))
					endL[i] = true;
				for(int k = i+1; k<n; k++)
					for(int l = 0; l<lines[k].size()-1; l++)
						if(lineIntersect(lines[i][j], lines[i][j+1], lines[k][l], lines[k][l+1]))
							mat[i][k] = mat[k][i] = true;
			}
		int d = bfs();
		cout<<"Case #"<<z<<": ";
		if(d == -1)
			cout<<"impossible";
		else
			cout<<d;
		cout<<endl;
	}
}
