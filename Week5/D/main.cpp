#include <iostream>
#include <cstring>
using namespace std;
int main()
{
  int t;
  cin>>t;
  for(int z= 1;z<=t; z++)
  {
    string s;
    cin>>s;
    int n = s.size()-1;
    int exp = 1;
    int zi = 0;
    for(int i = n; i>=0; i--)
    {
      zi+=((s[i] - '0') * exp)%13;
      exp = (exp*8)%13;

    }
    zi+=3;
    zi = zi%13;
    if(zi == 0)
      zi = 13;
    cout<<"Case #"<<z<<": "<<zi<<"\n";
  }
}
