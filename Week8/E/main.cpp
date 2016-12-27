#include <iostream>
#include <string>
#include <cmath>
using namespace std;
string productions[200];
int n,d,a;
string s;
void transform()
{
	string ns = "";
	for(int i =0; i<s.size(); i++)
	{
		if(s[i] == '+' || s[i] == '-')
			ns+=s[i];
		else
			ns+=productions[s[i]];
	}
	s = ns;
}
double get_rad(double x)
{
	return x * M_PI/180;
}
int main()
{
	int t;
	cin>>t;
	for(int z =1; z<=t; z++)
	{

		cin>>n>>d>>a>>s;
        for(int i =0; i<n; i++)
        {
			string x;
			cin>>x;
			productions[x[0]] = x.substr(3);
        }
        for(int i =0; i<d; i++)
			transform();
		for(int i =0; i<200; i++)
			productions[i] = "";
		double x,y;
		x = y = 0;
		double angle = 0;
		cout<<"Case #"<<z<<": \n";
		for(int i =0; i<s.size(); i++)
		{
			if(s[i] == '+')
				angle+=get_rad(a);
			else if(s[i] == '-')
				angle-=get_rad(a);
			else
			{
				printf("%.10f %.10f\n", x,y);
				x+=cos(angle);
				y+=sin(angle);
			}
		}
		printf("%.10f %10f\n", x,y);
	}
}
