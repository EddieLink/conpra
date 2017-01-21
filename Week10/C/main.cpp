#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
#include <climits>
using namespace std;

#define first get<0>
#define second get<1>
#define fr get<2>

typedef tuple<int,int,int> tup;
void initMat(int m[4][4])
{
    for(int i =0; i<4; i++)
        for(int j =0; j<4; j++)
            m[i][j] = 0;
}
void increaseFreq(int i, int j, int m[4][4])
{
    m[i][j]++;
    if(i!=j) m[j][i]++;
}
void setSol(int start, int end, int val, int sol[4][4], vector<tup> pairs)
{
    for(int i = start; i<end; i++)
        sol[first(pairs[i])][second(pairs[i])] = val;
}
int getScore(int sol[4][4], int freq[4][4])
{
    int sc = 0;
    for(int i =0; i<4; i++)
        for(int j = i; j<4; j++)
            sc+= sol[i][j] * freq[i][j];
    return sc;
}
int main()
{
    int t;
    int sol[4][4];
    int freq[4][4];
    cin>>t;
    vector<string> humans;
    vector<string> mice;
    map<char,int> n_base;
    n_base['A'] = 0;
    n_base['C'] = 1;
    n_base['T'] = 2;
    n_base['G'] = 3;

    for(int z = 1; z<=t; z++)
    {
        mice.clear();
        humans.clear();
        initMat(sol);
        initMat(freq);
        int n,m;
        cin>>n>>m;
        string s;
        for(int i =0; i<n; i++)
        {
            cin>>s;
            humans.push_back(s);
        }
        for(int i =0; i<m; i++)
        {
            cin>>s;
            mice.push_back(s);
            int length = s.length();
            for(int a =0; a<n; a++)
                for(int j =0; j<length; j++)
                    increaseFreq(n_base[s[j]], n_base[humans[a][j]],freq);
        }

        vector<tup> pairs;
        for(int i =0; i<4; i++)
            for(int j = i + 1; j<4; j++)
                pairs.push_back(make_tuple(i, j, freq[i][j]));
        sort(pairs.begin(), pairs.end(), [](tup a, tup b){return fr(a)>fr(b);});
        int max = -INT_MAX;
        for(int a =0; a<=10; a++)
            for(int b =0; b<= 10; b++)
                for(int c = 0; c<=10; c++)
                    for(int d = 0; d<=10; d++)
                    {
                        sol[0][0] = a; sol[1][1] = b; sol[2][2] = c; sol[3][3] = d;
                        int s = a+b+c+d;
                        if(!(s%2))
                        {
                            setSol(0,2, 10, sol, pairs);
                            setSol(3,6, -10, sol, pairs);
                            setSol(2,3, 10-(s/2), sol, pairs);
                            int score = getScore(sol, freq);
                            if(score>max) max = score;
                        }

                    }
        cout<<"Case #"<<z<<": "<<max<<"\n";
    }

}
