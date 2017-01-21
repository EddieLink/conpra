#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

typedef tuple<int,int,int> tup;
int main()
{
    int t;
    cin>>t;
    for(int z= 1; z<=t; z++)
    {
        int n,m;
        cin>>m>>n;
        vector<tup> x = vector<tup>(n);
        for(int i =0; i<n; i++)
        {
            double a,b;
            cin>>a>>b;
            x[i] = make_tuple(a,b,i);
        }
        sort(x.begin(), x.end(), [](tup a, tup b){return (get<1>(a)/(1.0*get<0>(a)))>(get<1>(b)/(1.0*get<0>(b)));});
        int charact, current;
        charact = current = 0;
        vector<int> chosen;
        while(charact<=m)
        {
            charact+=get<0>(x[current]);
            if(charact<=m)
                chosen.push_back(current);
            else
            {
                charact-=get<0>(x[current]);
                current++;
                if(current >= n)
                    break;
            }
        }
        cout<<"Case #"<<z<<": ";
        for(int i =0; i<chosen.size(); i++)
            cout<<get<2>(x[chosen[i]])+1<<" ";
        cout<<"\n";
    }
}
