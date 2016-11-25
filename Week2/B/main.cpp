#include <stdio.h>
#include <math.h>
double maxmin = -1;
int d,u,v;
int p;

double abs = 0.0001;
bool isPossible(double m)
{
	double j1 = u/m;
	double p1 = floor(j1) * m;
	if(((p1 + m)>u) && ((p1+m)<v))
		p1 = v;
	else
		p1+=m;
	return (2 + floor(j1) + floor((d-p1)/m))>=p;
}
double distance(double a, double b)
{
    double m = (a+b)/2.0;
    if(isPossible(m))
	{
		if(maxmin<m)
			maxmin = m;
		if(b-m>abs)
			return distance(m, b);
		else return m;
	}
	else
		if(m-a > abs)
			return distance(a,m);
		else return m;
}


int main()
{
//	freopen("input","r",stdin);
	int t;
	scanf("%d",&t);
	for(int z =0; z<t; z++)
	{
		d = p = u = v = 0;
		scanf("%d%d%d%d\n", &d,&p,&u,&v);

		printf("Case #%d: %.12g\n", z+1, distance(0.0, d*(1.0)));

	}
}
