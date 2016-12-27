#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
using namespace std;

#define line tuple<point,point>
struct point{
	double x,y;

	bool operator ==(const point& a)
	{
		return a.x == x && a.y == y;
	}
	bool operator !=(const point& a)
	{
		return a.x!=x || a.y != y;
	}
};
int orient(point a, point b, point c)
{
	int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	if(!val) return 0;
	return (val>0)?-1:1;
}
bool onSegment(point p, point q, point r)
{
	if(orient(p,q,r))
	return false;
	if(q.x<=max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y,r.y) && q.y >= min(p.y, r.y))
		return true;
	return false;
}
point firstPoint(line x)
{
	return get<0>(x);
}
point secondPoint(line x)
{
	return get<1>(x);
}
point getProj(point p, point x1, point x2) // from http://stackoverflow.com/questions/1811549/perpendicular-on-a-line-from-a-given-point
{
	point proj;

	double dx = x2.x-x1.x;
	double dy = x2.y - x1.y;
	double mag = sqrt(dx*dx + dy*dy);
	dx/=mag;
	dy/=mag;
	double lam = (dx*(p.x-x1.x)) + (dy*(p.y-x1.y));
	proj.x = (dx*lam)+x1.x;
	proj.y = (dy*lam)+x1.y;
	return proj;

	double k = ((x2.y-x1.y) * (p.x-x1.x) - (x2.x - x1.x) * (p.y - x1.y)) / (pow(x2.y - x1.y, 2) + pow(x2.x - x1.x, 2));
	proj.x = p.x - k * (x2.y - x1.y);
	proj.y = p.y + k * (x2.x - x1.x);

	return proj;
}
int main()
{
	int t;
	cin>>t;
	vector<line> pol;
	for(int z = 1; z<=t; z++)
	{
		pol.clear();
		int n;
		int pos = 0;
		cin>>n;
		point mid;
		point old;
		mid.x = mid.y = 0;
		for(int i = 0; i<n; i++)
		{
			if(!i)
			{
				cin>>old.x>>old.y;
				mid.x+=old.x;
				mid.y+=old.y;
				i++;
			}
			point x;
			cin>>x.x>>x.y;
			pol.push_back(make_tuple(old, x));
			mid.x+=x.x;
			mid.y+=x.y;
			old.x = x.x;
			old.y = x.y;
		}
		pol.push_back(make_tuple(old, firstPoint(pol[0])));
		mid.x/=(double)n;
		mid.y/=(double)n;
		for(int i =0; i<n; i++)
		{
			int initial = -2;
			point p, q;
			p = firstPoint(pol[i]);
			q = secondPoint(pol[i]);
			bool possible = true;
			for(int j = 0; j<n; j++)
			{
				if(i == j)
					continue;
				point p1,q1;
				p1 = firstPoint(pol[j]);
				q1 = secondPoint(pol[j]);
				if(initial == -2 || !initial)
					initial = orient(p, p1, q);
				if(((orient(p, p1,q) != initial) && (p1 != p && p1 !=q)) || ((orient(p, q1,q) != initial) && q1!=p && q1!=q) && initial)
				{
					possible = false;
					break;
				}
			}
			if(!possible) continue;
			point proj = getProj(mid, p, q);
			if(onSegment(p,proj,q))
				pos++;
		}
		cout<<"Case #"<<z<<": "<<pos<<"\n";
	}
}
