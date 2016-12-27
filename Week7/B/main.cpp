#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#define line tuple<point,point>
struct point{
	int x,y;
};
//intersection algorithm from http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/

int orient(point a, point b, point c)
{
	int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
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

int main()
{
    int t;
    cin>>t;
	vector<line> pol;
	for(int z =1; z<=t; z++)
    {
		pol.clear();
		int n;
		point imp;
		cin>>imp.x>>imp.y>>n;
		for(int i=0; i<n; i++)
		{
			point a, b;
			cin>>a.x>>a.y>>b.x>>b.y;
			pol.push_back(make_tuple(a,b));
		}
		point l;
		l.x = -1000;
		l.y = -1000;
		int inters = 0;
		int difX, difY;
		difX = 0;
		difY = 1;
		for(int i =0; i<pol.size(); i++)
		{
			point p,q;
			p = get<0>(pol[i]);
			q = get<1>(pol[i]);
			if((onSegment(imp, p, l) && !orient(imp,p,l))  || (onSegment(imp, q, l) && !orient(imp,q,l)))
			{
				i = -1;
				inters = 0;
				l.x+=difX;
				l.y+=difY;
				while(l.x == imp.x && l.y == imp.y)
				{
					l.x+=difX;
					l.y+=difY;
				}
				if(l.x>1000)
				{
					l.x = 1000;
					difX = 0;
					difY = -1;
				}
				if(l.y>1000)
				{
					l.y = 1000;
					difY = 0;
					difX = 1;
				}
				if(l.x<-1000)
				{
					l.x = -1000;
					difX = 0;
					difY = 1;
				}
				if(l.y<-1000)
				{
					l.y = -1000;
					difY = 0;
					difX = -1;
				}
				continue;
			}
			if(lineIntersect(imp,l,p,q))
				inters++;
		}
		cout<<"Case #"<<z<<": ";
		if(!(inters%2))
			cout<<"too bad";
		else
			cout<<"jackpot";
		cout<<"\n";
    }
}
