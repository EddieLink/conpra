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

//relevant only here:
coord readPoint()
{
	T x, y;
	cin>>x>>y;
	return make_tuple(x,y,1);
}
typedef tuple<coord, coord, coord> sword;
coord getM(sword s1)
{
	return projPointOnLine(get<2>(s1), crossProd(get<0>(s1), get<1>(s1)));
}
bool sameSide(sword s1, coord inters, coord m1)
{
	point _inters = getPoint(m1);
	point _x3 = getPoint(get<2>(s1));
	_inters.x -= _x3.x;
	_inters.y -= _x3.y;
	_inters.x *= 2.0;
	_inters.y *= 2.0;
    _inters.x += _x3.x;
    _inters.y += _x3.y;
	T val1 = ccw(getPoint(get<0>(s1)), getPoint(get<1>(s1)), getPoint(inters));
	T val2 = ccw(getPoint(get<0>(s1)), getPoint(get<1>(s1)), _inters);
	return val1*val2>=0;
}
int main()
{
	//freopen("input2","r",stdin);
    int t;
    cin>>t;
    for(int z = 1; z<=t; z++)
    {
		sword s1, s2;
		coord x[3];
		for(int i =0; i<3; i++)
			x[i] = readPoint();
		s1 = make_tuple(x[0], x[1], x[2]);
		for(int i =0; i<3; i++)
			x[i] = readPoint();
		s2 = make_tuple(x[0],x[1], x[2]);

		coord m1 = normalize(getM(s1));
		coord m2 = normalize(getM(s2));

		coord l1,l2;
		l1 = crossProd(get<2>(s1), m1);
		l1 = normalizeLine(l1);
		l2 = crossProd(get<2>(s2), m2);
		l2 = normalizeLine(l2);

		coord inters = normalize(crossProd(l1,l2));

		cout<<"Case #"<<z<<": ";

		if(!infinite(inters) && sameSide(s1, inters, m1) && sameSide(s2, inters, m2))
			printf("%.10f %.10f", first(inters), second(inters));
		else
			cout<<"strange";
		cout<<"\n";

    }
}
