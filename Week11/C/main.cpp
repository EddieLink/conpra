#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct farmer{
	int iq, w;
};
int solve()
{
	int n; cin>>n;
	vector<farmer> v = vector<farmer>(n);
	for(int i=0; i<n; i++)
		cin>>v[i].iq>>v[i].w;
	sort(v.begin(), v.end(), [](farmer x, farmer y){
		if(x.iq == y.iq)
			return x.w > y.w;
		return x.iq < y.iq;
	});
    int l[n];
	int length = 1;
	l[0] = 1;

	for(int i = 1; i<n; i++)
	{
		l[i] = 1;
		for(int j = i-1; j>=0; j--)
			if(l[j] + 1 > l[i] && v[j].w > v[i].w)
				l[i] = l[j]+1;
		if(l[i] > length)
			length = l[i];
	}
    return length;
}

int main()
{
	int t; cin>>t;
	for(int z=1; z<=t; z++)
		cout<<"Case #"<<z<<": "<<solve()<<"\n";
}
