#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
using namespace std;

#define line tuple<point,point>
#define T tuple<double, double, int>
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
//intersection algorithm from http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
double calculateAngle(T a,T b)
{
	double yDif = get<1>(b)-get<1>(a);
	double xDif = get<0>(b)-get<0>(a);
	return atan2(yDif, xDif);
}
double onRight(T x, T line1, T line2)
{
	return ((get<0>(line2)-get<0>(line1))*(get<1>(x)-get<1>(line1)) - (get<0>(x)-get<0>(line1))*(get<1>(line2)-get<1>(line1)));
}
double dist(T a, T b)
{
	return sqrt(pow(get<0>(a)-get<0>(b),2) + pow(get<1>(a)-get<1>(b),2));
}
int orient(point a, point b, point c)
{
	double val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	if(!val)
		return 0;
	return (val>0)?-1:1;
}
point heightE, widthE;
bool pointInPolygon(point imp, vector<line> pol)
{
	int initial = 2;
	if(imp.x<heightE.x || imp.x>heightE.y || imp.y<widthE.x || imp.y>widthE.y)
		return false;
	for(int i =0; i<pol.size(); i++)
	{
		point p, q;
		p = get<0>(pol[i]);
		q = get<1>(pol[i]);
		int ccw = orient(p,imp,q);
		if(p == imp || q == imp)
			continue;
		if(initial == 2)
			initial = ccw;
		if(ccw!=initial && ccw && initial )
			return false;
	}
	return true;
}
void checkMins(point old)
{
	if(old.x<heightE.x)
		heightE.x = old.x;
	if(old.x>heightE.y)
		heightE.y = old.x;
	if(old.y<widthE.x)
		widthE.x = old.y;
	if(old.y>widthE.y)
		widthE.y = old.y;
}
point convertFromTuple(T x)
{
		point a;
		a.x = get<0>(x);
		a.y = get<1>(x);
		return a;
}
	vector<int> hull;
vector<int> graham(vector<T> points)
{
	int p0;
	double minx,miny;
	minx = miny = 1000;
	for(int i =0; i<points.size(); i++)
	{
		point x;
		x.x = get<0>(points[i]);
		x.y = get<1>(points[i]);
		if(x.y<miny)
		{
			minx = x.x;
			miny = x.y;
			p0 = i;
		}
		else if(x.y == miny && x.x<minx)
		{
			minx = x.x;
			p0 = i;
		}
	}
	vector<T>remaining = points;
	sort(remaining.begin(), remaining.end(), [p = points[p0]](T a, T b){
		double ang1,ang2;
		ang1 = calculateAngle(p,a);
		ang2 = calculateAngle(p,b);
		if(ang1<ang2)
			return true;
		if(ang1 == ang2)
			return dist(p,a)<dist(p,b);
		return false;
	});

	hull.insert(hull.begin(),get<2>(remaining[0]));
	hull.insert(hull.begin(), get<2>(remaining[1]));
	hull.insert(hull.begin(), get<2>(remaining[2]));
	for(int i =3; i<remaining.size(); i++)
	{
		double v = onRight(remaining[i], points[hull[1]], points[hull[0]]);
		if(v < 0)
		{
			hull.erase(hull.begin());
			i--; continue;
		}
		hull.insert(hull.begin(), get<2>(remaining[i]));
	}
	for(int i =0; i<hull.size(); i++)
	{
		int a = i-1;
		int b = i+1;
		a = (a<0)?(hull.size()+a):a;
		b = (b>=hull.size())?(b-hull.size()):b;
		if(!onRight(points[hull[a]], points[hull[i]], points[hull[b]]))
			hull.erase(hull.begin()+i--);
	}

	return hull;
}
vector<T> points;
vector<T> getPoints(vector<int> hull)
{
		vector<T> p2;
		for(int i =0; i<hull.size(); i++)
			p2.push_back(points[hull[i]]);
		return p2;
}
int main()
{
    int t;
    cin>>t;
    vector<line> pol;
    for(int z = 1; z<=t; z++)
    {
		int n;
		cin>>n;
		heightE.x = widthE.x = 1000;
		heightE.y = widthE.y = 0;
		pol.clear();
		points.clear();
		hull.clear();
		point old;
		for(int i = 0; i<n; i++)
		{
			if(!i)
			{
				cin>>old.x>>old.y;
				i++;
				checkMins(old);
			}
			point x;
			cin>>x.x>>x.y;
			pol.push_back(make_tuple(old, x));
			old.x = x.x;
			old.y = x.y;
			checkMins(old);
		}
		pol.push_back(make_tuple(old, get<0>(pol[0])));
		double minx,miny;
		minx = miny = 1001;
		int ct = 0, p0;
		for(int i =0; i<=300; i++)
			for(int j = 0; j<=300; j++)
			{
				point x;
				x.x = i; x.y =j;
				if(pointInPolygon(x, pol))
				{
					points.push_back(make_tuple(x.x,x.y,ct++));
					if(x.y<miny)
					{
						minx = x.x;
						miny = x.y;
						p0 = points.size()-1;
					}
					else if(x.y == miny && x.x<minx)
					{
						minx = x.x;
						p0 = points.size()-1;
					}
				}
			}
		cout<<"Case #"<<z<<":\n";
		int nec = 3;
		if(points.size()>=2)
		{
			graham(points);

			if(hull.size() == 0)
				cout<<"2\n"<<get<0>(points[0])<<" "<<get<1>(points[0])<<"\n"<<get<0>(points[points.size()-1])<<" "<<get<1>(points[points.size()-1])<<"\n";
			else
			{
				cout<<hull.size()<<"\n";
				for(int i =0; i<hull.size(); i++)
					cout<<get<0>(points[hull[i]])<<" "<<get<1>(points[hull[i]])<<"\n";
			}
		}
		else if(points.size() == 0)
			cout<<"0\n";
		else
			cout<<"1\n"<<get<0>(points[0])<<" "<<get<1>(points[0])<<"\n";



    }
}
