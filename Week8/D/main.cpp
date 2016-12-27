#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define sqr(x) x*x
typedef long long int T;
struct Rational
{
	T denominator, numerator;

	private: T gcd(T x, T y)
	{
		if(y>x)
			gcd(y,x);
		do
		{
			T r = x % y;
			if(!r) break;
			x = y;
			y = r;
		}
		while(true);
		return x;
	}

	public:
	Rational()
	{
		denominator = 1;

	}
	Rational(T x, T y = 1)
	{
		denominator = y;
		numerator = x;
	}

	Rational operator+(Rational x)
	{
		int greatest=  gcd(this->denominator, x.denominator);
		return Rational((this->numerator * (greatest/this->denominator)) + (x.numerator * (greatest/x.denominator)),greatest);
	}
	Rational operator-(Rational x)
	{
		int greatest=  gcd(this->denominator, x.denominator);
		return Rational((this->numerator * (greatest/this->denominator)) - (x.numerator * (greatest/x.denominator)),greatest);
	}
	Rational operator*(Rational x)
	{
		return Rational(this->numerator * x.numerator, this->denominator * x.denominator);
	}
	Rational operator/(Rational x)
	{
		return Rational(this->numerator * x.denominator, this->denominator * x.numerator);
	}
	Rational operator+(T x)
	{
		Rational x1(x);
		return (*this) + x1;
	}
	Rational operator-(T x)
	{
		Rational x1(x);
		return (*this) - x1;
	}
	Rational operator*(double x)
	{
		Rational x1(x);
		return (*this) * x1;
	}
	bool operator==(Rational x)
	{
		T greatest1 = gcd(this->denominator, this->numerator);
		T greatest2 = gcd(x.denominator, x.numerator);
		return ((this->denominator/greatest1) == (x.denominator/greatest2)) && ((this->numerator/greatest1) == (x.numerator/greatest2));
	}
	bool operator!=(Rational x)
	{
		return !(*this == x);
	}
};
Rational abs(Rational a)
{
	return Rational(abs(a.numerator), abs(a.denominator));
}
Rational sqrt(Rational x)
{
	return Rational(sqrt(x.numerator), sqrt(x.denominator));
}
struct point{
	Rational x,y;
	bool operator ==(point x)
	{
		return this->x == x.x && this->y == x.y;
	}
};
Rational distance(point a, point b)
{
	return sqrt(sqr(a.x-b.x) + sqr(a.y-b.y));
}
point getCut(point x, point y, Rational dist)
{
	point a;
	a.x = dist * (y.x - x.x) + x.x;
	a.y = dist * (y.y - x.y) + x.y;

	return a;
}
Rational getTriangleArea(point a, point b, point c)
{
	return (a.x * b.y + b.x * c.y + c.x * a.y - a.x * c.y - c.x * b.y - b.x * a.y) * Rational(1,2);
}
bool findCut(point a, vector<point> b)
{
	for(int i =0; i<b.size(); i++)
		if(a == b[i])
			return true;
	return false;
}
int main()
{

    int t;
    cin>>t;
    for(int z = 1; z<=t; z++)
    {
		int n,m;
		cin>>n>>m;
		vector<point> points;
		vector<vector<point> > cuts;
		for(int i=0; i<n; i++)
		{
			point x;
			int a,b;
			cin>>a>>b;

			x.x = Rational(a);
			x.y = Rational(b);
			points.push_back(x);
		}
		Rational dist(1,m);
		for(int i =0; i<n; i++)
		{
			vector<point> c;
			int last = i-1;
			if(last == -1) last = n-1;
			int next = i+1;
			if(next == n) next = 0;
			point cut = getCut(points[i], points[next], dist);
			c.push_back(cut);
			cut = getCut(points[i], points[last], dist);
			c.push_back(cut);
			cuts.push_back(c);
		}
		Rational area(0);
		for(int i =1; i<n-1; i++)
			area = area + getTriangleArea(points[0], points[i], points[i+1]);
		Rational cutArea(0);
		for(int i =0; i<n; i++)
		{
			point a = points[i];
			point b = cuts[i][0];
			point c= cuts[i][1];
			cutArea = cutArea + getTriangleArea(a,b,c);
		}
		cout<<"Case #"<<z<<": ";
		Rational res = cutArea/area;
		cout<<res.numerator<<"/"<<res.denominator<<endl;
    }
}
