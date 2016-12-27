#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>
#define MAX 10000
#define T tuple<int, int, int>
using namespace std;
int n;
vector<T> points;
vector<int> hull;
double calculateAngle(T a,T b)
{
	double yDif = get<1>(b)-get<1>(a);
	double xDif = get<0>(b)-get<0>(a);
	return atan2(yDif, xDif);
	return atan(yDif/(double)xDif);
}
int onRight(T x, T line1, T line2)
{
	return ((get<0>(line2)-get<0>(line1))*(get<1>(x)-get<1>(line1)) - (get<0>(x)-get<0>(line1))*(get<1>(line2)-get<1>(line1)));
}
double dist(T a, T b)
{
	return sqrt(pow(get<0>(a)-get<0>(b),2) + pow(get<1>(a)-get<1>(b),2));
}
int main()
{
    int t;
    cin>>t;
    for(int z = 1; z<=t; z++)
    {
		hull.clear();
		points.clear();
		cin>>n;
		int minx, miny, p0;
		minx = miny = 1001;
		for(int i=0; i<n; i++)
		{
			int x,y;
			cin>>x>>y;
			if(y<miny)
			{
				minx = x;
				miny = y;
				p0 = i;
			}
			else if(y == miny && x<minx)
			{
				minx = x;
				p0 = i;
			}
			points.push_back(make_tuple(x,y,i));
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
			int v = onRight(remaining[i], points[hull[1]], points[hull[0]]);
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
		sort(hull.begin(), hull.end());
		cout<<"Case #"<<z<<": ";
		for(int i =0;i<hull.size(); i++)
			cout<<hull[i]+1<<" ";
		cout<<"\n";
    }
}
