#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>
using namespace std;

#define node get<0>
#define stairs get<1>

typedef vector<tuple<int,int>> v_tup;

int main()
{
    int t; cin>>t;
    for(int z = 1; z<= t; z++)
    {
        int n,m,s; cin>>n>>m>>s;
        v_tup g[n+1];
        for(int i =0; i<m; i++)
        {
            int a,b,c; cin>>a>>b>>c;
            g[a].push_back(make_tuple(b,c));
            g[b].push_back(make_tuple(a,-c));
        }

        bool visited[n+1];
        int sum[n+1], bfs[n+1];
        for(int i =1; i<=n; i++)
        {
            sum[n] = bfs[n] = 0;
            visited[i] = false;
        }
        queue<int> q;
        q.push(s);
        visited[s] = true;
        sum[s] = 0;
        bfs[s] = 0;

        int min = INT_MAX;
        while(!q.empty())
        {
            int c = q.front(); q.pop();
            for(int i =0; i<g[c].size(); i++)
                if(visited[node(g[c][i])] && sum[node(g[c][i])] != sum[c] + stairs(g[c][i]))
                {
                    int lvl = bfs[node(g[c][i])] + bfs[c] + 1;
                    if(min > lvl) min = lvl;
                }
                else if(!visited[node(g[c][i])])
                {
                    bfs[node(g[c][i])] = bfs[c] + 1;
                    sum[node(g[c][i])] = sum[c] + stairs(g[c][i]);
                    visited[node(g[c][i])] = true;
                    q.push(node(g[c][i]));
                }

        }
        cout<<"Case #"<<z<<": ";
        if(min == INT_MAX)
            cout<<"possible\n";
        else cout<<min<<"\n";
    }
}
