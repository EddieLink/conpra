#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <stack>
#include <stdlib.h>
using namespace std;
 
struct Point
{
	double x, y;
};

//graham found here: http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
Point p0;
Point nextToTop(stack<Point> &S)
{
	Point p = S.top();
	S.pop();
	Point res = S.top();
	S.push(p);
	return res;
}

int swap(Point &p1, Point &p2)
{
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

double distSq(Point p1, Point p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) +
		  (p1.y - p2.y)*(p1.y - p2.y);
}

int orientation(Point p, Point q, Point r)
{
	double val = (q.y - p.y) * (r.x - q.x) -
			  (q.x - p.x) * (r.y - q.y);
 
	if (val == 0) return 0; 
	return (val > 0)? 1: 2; 
}

int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;
 

   int o = orientation(p0, *p1, *p2);
   if (o == 0)
	 return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
 
   return (o == 2)? -1: 1;
}

vector<Point> convexHull(Point points[], int n)
{
   double ymin = points[0].y; int min = 0;
   for (int i = 1; i < n; i++)
   {
	 double y = points[i].y;

	 if ((y < ymin) || (ymin == y &&
		 points[i].x < points[min].x))
		ymin = points[i].y, min = i;
   }
 

   swap(points[0], points[min]);

   p0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), compare);

   int m = 1; 
   for (int i=1; i<n; i++)
   {

	   while (i < n-1 && orientation(p0, points[i],
			points[i+1]) == 0)
		  i++;
 
 
	   points[m] = points[i];
	   m++;
   }

   stack<Point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);
 

   for (int i = 3; i < m; i++)
   {
		while (orientation(nextToTop(S), S.top(), points[i]) != 2)
		S.pop();
		S.push(points[i]);
   }
   vector<Point> sol;
   while (!S.empty())
   {
	   Point p = S.top();
	   sol.push_back(p);
	   S.pop();
   }
   return sol;
}
double getTriangleArea(Point a, Point b, Point c)
{
	return abs(a.x * b.y + b.x * c.y + c.x * a.y - a.x * c.y - c.x * b.y - b.x * a.y) * 0.5;
}
double solve()
{
	int n; cin>>n;
	Point points[n];
	for(int i= 0; i<n; i++)
		cin>>points[i].x>>points[i].y;	

	double area = 0.0;
	vector<Point> hull = convexHull(points, n);
	for(int i =1; i<hull.size()-1; i++)
		area = area + getTriangleArea(hull[0], hull[i], hull[i+1]);
	return area * 2.0;
}
int main()
{
	int t; cin>>t;
	for(int z = 1; z<=t; z++)
		cout<<"Case #"<<z<<": "<<solve()<<"\n";
}