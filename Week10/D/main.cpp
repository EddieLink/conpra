#include <iostream>
#include <climits>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAX 301

int n;
bool mat[MAX][MAX];
void moveElement(int i, bool *s1, bool *s2)
{
    s1[i] = false;
    s2[i] = true;
}
int calculate(bool *s1, bool *s2)
{
    int score = 0;
    for(int i =1; i<=n; i++)
        for(int j = 1; j<=n; j++)
            if(s1[i] && s2[j] && mat[i][j])
                score++;
    return score;
}
bool* createArray(int n)
{
    return (bool*)malloc(sizeof(bool) * (n+1));
}
int main()
{
    int t; cin>>t;
    bool *s1, *s2, *sol;
    s1 = createArray(MAX);
    s2 = createArray(MAX);
    sol = createArray(MAX);
    for(int z= 1; z<=t; z++)
    {
        cin>>n;
        int max = -INT_MAX;

        for(int i =0; i<=n; i++)
            for(int j = 0; j<=n; j++)
                mat[i][j] = false;
        for(int i =1; i<=n; i++)
        {
            int k;
            s1[i] = true;
            s2[i] = false;
            cin>>k;
            for(int j =0; j<k; j++)
            {
                int x; cin>>x;
                mat[i][x] = mat[x][i] = true;
            }
        }
        while(true)
        {
            bool change = false;
            for(int i =1; i<=n; i++)
            {
                moveElement(i, s1, s2);
                int score = calculate(s1,s2);
                if(score > max)
                {
                    change = true;
                    max = score;
                    for(int a = 1; a<=n; a++)
                        sol[a] = s1[a];
                }
                else
                    moveElement(i, s2, s1);
            }
            if(!change) break;
        }
        cout<<"Case #"<<z<<":\n";
        for(int i =1; i<=n; i++)
            if(sol[i]) cout<<i<<" ";
        cout<<"\n";
    }
}
