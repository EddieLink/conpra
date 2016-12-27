#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>
#include <cmath>
#include <queue>
#define line tuple<point, point>
using namespace std;

#define MAX 500
struct point{
	double x,  y;
		bool operator ==(const point& a)
	{
		return a.x == x && a.y == y;
	}
	bool operator !=(const point& a)
	{
		return a.x!=x || a.y != y;
	}
};

point first(line x)
{
	return get<0>(x);
}
point second(line x)
{
	return get<1>(x);
}
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
	return false;
	if(!o1 && onSegment(a1,b1,a2)) return true;
	if(!o2 && onSegment(a1, b2, a2)) return true;
	if(!o3 && onSegment(b1, a1, b2)) return true;
	if(!o4 && onSegment(b1, a2, b2)) return true;

	return false;
}
double mat[MAX][MAX];
int w,h,n;
vector<point>v;
vector<line>obst;
double dist[MAX];
int pred[MAX];
bool visited[MAX];
void bellman(int start)
{
	for(int i =0; i<MAX; i++)
	{
		dist[i] = INT_MAX;
		visited[i] = false;
		pred[i] = -1;
	}
	dist[start] = 0;
	queue<int> q;
	q.push(start);
	while(!q.empty())
	{
		int w = q.front();
		q.pop();
		for(int i = 0; i<MAX; i++)
			if(mat[i][w] != -1)
			{
				if(dist[i]>dist[w]+mat[i][w])
				{
					dist[i] = dist[w]+mat[i][w];
                    pred[i] = w;
                    q.push(i);
				}
			}
	}
}
vector<point>getPath(int start,int end)
{
	vector<point> path;
	while(end!=-1)
	{
		path.push_back(v[end]);
		end = pred[end];
	}
	reverse(path.begin(), path.end());
	return path;
}
int edgOb[MAX];
int main()
{
		freopen("input2","r",stdin);
    int t;
    cin>>t;
    for(int z = 1; z<=t; z++)
    {
		v.clear();
		obst.clear();
		cin>>w>>h>>n;
		for(int i =0; i<MAX; i++)
		{
			edgOb[i] = -1;
			for(int j =0; j<MAX; j++)
				mat[i][j] =-1;
		}
		for(int i =0; i<n; i++)
		{
			point a,b;
			int wi, he;
			cin>>a.x>>a.y>>wi>>he;
			v.push_back(a);
			edgOb[v.size() -1] = i;
			b.x = a.x+wi;
			b.y = a.y;
			edgOb[v.size() -1] = i;
			v.push_back(b);
			mat[v.size()-2][v.size()-1] = mat[v.size()-1][v.size()-2] = wi;
			obst.push_back(make_tuple(a,b));
			b.x = a.x;
			b.y = a.y+he;
			v.push_back(b);
			edgOb[v.size() -1] = i;
			mat[v.size()-3][v.size()-1] = mat[v.size()-1][v.size()-3]= he;
			obst.push_back(make_tuple(a,b));
			a.x = b.x+wi;
			a.y = b.y;
			v.push_back(a);
			edgOb[v.size() -1] = i;
			mat[v.size()-2][v.size()-1] = mat[v.size()-1][v.size()-2] = wi;
			obst.push_back(make_tuple(a,b));
			b.x = a.x;
			b.y = a.y-he;
			mat[v.size()-3][v.size()-1]= mat[v.size()-1][v.size()-3] = he;
			obst.push_back(make_tuple(a,b));

		}
		point x;
		cin>>x.x>>x.y;
		v.insert(v.begin(), x);
		cin>>x.x>>x.y;
		v.push_back(x);

		vector<point> points  = v;
	/*	sort(points.begin(), points.end(), [](point a, point b){
			if(a.x == b.x)
				return a.y<b.y;
			return a.x<b.x;
		});*/
		for(int i =0; i<points.size(); i++)
			for(int j = 0; j<points.size(); j++)
			{
				if(i == j) continue;
				bool pos= true;
				for(int k = 0; k<obst.size(); k++)
				{
					if(lineIntersect(first(obst[k]), second(obst[k]), points[i],points[j]))
					{
						if((points[j] == first(obst[k])  || points[j] == second(obst[k]) || points[i] == first(obst[k]) || points[i] == second(obst[k])))
						{
							//pos = !pos;
						}
						else
						{
							pos = false;
							break;
						}
					}
				}
				if(pos)
					mat[i][j] = mat[j][i] = sqrt(pow(points[i].x-points[j].x,2) + pow(points[i].y - points[j].y, 2));
			}
	/*	for(int i =0; i<MAX; i++)
			for(int j =i; j<MAX; j++)
			{
				if(mat[i][j] != -1)
					cout<<v[i].x<<" "<<v[i].y<<" - "<<v[j].x<<" "<<v[j].y<<": "<<mat[i][j]<<endl;
			}
		return 0;*/
		bellman(0);
	//	for(int i =0; i<v.size(); i++)
	//		cout<<v[i].x<<" "<<v[i].y<<": "<<v[pred[i]].x<<" "<<v[pred[i]].y<<endl;
		//return 1;
		vector<point> sol = getPath(0, v.size()-1);
		cout<<"Case #"<<z<<": ";
		for(int i =0; i<sol.size(); i++)
			cout<<"("<<sol[i].x<<","<<sol[i].y<<") ";
		cout<<"\n";
    }
}
