#include <iostream>
#include <tuple>
#include <stdio.h>
#include <cmath>
using namespace std;

typedef double T;
typedef tuple<T, T, T> coord;

struct point{
	T x, y;
};
T first(coord x)
{
	return get<0>(x);
}
T second(coord x)
{
	return get<1>(x);
}
T third(coord x)
{
	return get<2>(x);
}
bool infinite(coord x)
{
	return abs(third(x)) <= 1e-13;
}
coord normalize(coord x)
{
	if(infinite(x))
		return x;
	T val = third(x);
	if(val == 0)
		return x;
	return make_tuple(first(x)/val, second(x)/val, 1);
}
coord normalizeLine(coord x)
{
	if(infinite(x))
		return x;
	T xa,xb,xc;
	xa = first(x);
	xb = second(x);
	xc = third(x);

	T a,b,c;
	a= xa/sqrt(pow(xa,2) + pow(xb,2));
	b =xb/sqrt(pow(xa,2) + pow(xb,2));
	c = xc/sqrt(pow(xa,2) + pow(xb,2));

	return make_tuple(a,b,c);
}
coord crossProd(coord a, coord b)
{
	return make_tuple(second(a) * third(b) - third(a)*second(b),
		third(a) * first(b) - first(a) * third(b),
		first(a) * second(b) - second(a) * first(b)
	);
}
T scalarProd(coord a, coord b)
{
	return first(a) * first(b) + second(a) * second(b) + third(a) * third(b);
}
bool pointOnLine(coord point, coord line)
{
	return scalarProd(point, line) == 0;
}
coord orthogonal(coord x)
{
	return make_tuple(second(x), -first(x), third(x));
}
coord projPointOnLine (coord p, coord l)
{
	coord dir = crossProd(l, make_tuple(0,0,1));
	coord m = crossProd(p, make_tuple(second(dir), first(dir) * (-1), 0));
	return crossProd(m, l);
}

T ccw(point p0, point p1, point p2){
	return (p1.x - p0.x) * (p2.y- p0.y) - (p2.x- p0.x) * (p1.y- p0.y);
}
point getPoint(coord x)
{
	x = normalize(x);
	point a;
	a.x = first(x);
	a.y = second(x);
	return a;
}
//only relevant here:
coord getHeight(coord a, coord b, coord c)
{
	coord proj = normalize(projPointOnLine(a, crossProd(b,c)));
	return normalizeLine(crossProd(a,proj));
}
coord getMiddle(coord b, coord c)
{
	b = normalize(b);
	c = normalize(c);
	T x = (first(b) + first(c))/2;
	T y = (second(b) + second(c))/2;
	return make_tuple(x,y,1);
}
coord getMedian(coord a, coord b, coord c)
{
	coord m = getMiddle(b,c);
	return normalizeLine(crossProd(a, m));
}
coord getBisect(coord a, coord b)
{
	coord line = crossProd(a, b);
	coord middle = getMiddle(a,b);
	return normalizeLine(make_tuple(-second(line), first(line), second(line)*first(middle) - first(line) * second(middle)));
}

int main()
{
	int t;
	cin>>t;
	for(int z = 1; z<=t; z++)
	{
        coord points[3];
        for(int i =0; i<3; i++)
		{
			T x, y;
			cin>>x>>y;
			points[i] = make_tuple(x,y,1);
		}
 		coord ortho = normalize(crossProd(getHeight(points[0], points[1], points[2]), getHeight(points[1], points[0], points[2])));
		coord centroid = normalize(crossProd(getMedian(points[0],points[1],points[2]), getMedian(points[1],points[0],points[2])));
		coord circum = normalize(crossProd(getBisect(points[0],points[1]), getBisect(points[1],points[2])));
		cout<<"Case #"<<z<<":\n";
		printf("%.6f %.6f\n%.6f %.6f\n%.6f %.6f\n",  first(centroid), second(centroid), first(ortho), second(ortho), first(circum), second(circum));


	}
}
