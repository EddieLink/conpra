#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> v;

int lastBefore(int p, bool* positions)
{
    for(int i = p; i>=1; i--)
        if(positions[i])    return i;
    return 0;
}
int main()
{
    int t;
    cin>>t;
    for(int z =1; z<=t; z++)
    {
        int l,n,d;
        cin>>l>>n>>d;
        bool positions[l+1] = {};
        v lamps;
        for(int i =0; i<n; i++)
        {
            int p;
            cin>>p;
            positions[p] = true;
            lamps.push_back(p);
        }
        sort(lamps.begin(), lamps.end(), [](int a, int b){return a<b;});
        int covered_to = 0;
        for(int i=0; i<n; i++)
            if(lamps[i] - d > covered_to)
                break;
            else
                covered_to = lamps[i] + d;
        cout<<"Case #"<<z<<": ";
        if(covered_to < l)
        {
            cout<<"impossible\n";
            continue;
        }
        int c_pos = 0;
        int c_lamp;
        int lamp_count = 0;
        while(c_pos < l)
        {
            c_lamp = lastBefore(c_pos + d, positions);
            c_pos = c_lamp + d;
            lamp_count++;
        }
        cout<<lamp_count<<"\n";
    }
}
