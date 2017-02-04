#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#define RDG 0.000001
double calc(vector<int> x, double c)
{
	double val = 0;
	for(int i =0; i<x.size(); i++)
		val+=pow(c,i+1) * x[i];
	return val;
}
int ct = 10;
double fnd(vector<int> x, double c1, double c2, int e)
{
	double c = (c1+c2)/(2*1.0);
	double current = calc(x, c);
	//cout<<"Current: "<<current<<", e: "<<e<<", c:"<<c<<endl;
	ct--; 
	//if(ct<=0) return c;
	if(current >= e - RDG && current <= e + RDG || c == 1 || !c)
		return c;
	if(current > e)
		return fnd(x, c1, c, e);
	if(current < e)
		return fnd(x, c, c2, e);
	return c;
}
double solve()
{
	double sol = 0;
	int n,b; cin>>n>>b;
	double prob = 0;
	vector<int> val = vector<int>(n);
	int e = 0;
	for(int i =0; i<n; i++)
		cin>>val[i];
	e = b*n;
	return fnd(val, 0, 1, b);
}
int main()
{
	int t; cin>>t;
	for(int z = 1; z<=t; z++)
		cout<<"Case #"<<z<<": "<<solve()<<"\n";
	return 0;
}
