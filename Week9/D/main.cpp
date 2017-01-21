//dinic's algorithm found here: https://sites.google.com/site/indy256/algo_cpp/dinic_flow
#include <algorithm>
#include <vector>
#include <climits>
#include <iostream>
#include <sstream>
#include <tuple>
#include <cstring>
using namespace std;

const int maxnodes = 5000;

int nodes = maxnodes, src, dest;
int dist[maxnodes], q[maxnodes], work[maxnodes];

struct Edge {
  int to, rev;
  int f, cap;
};
vector<Edge> g[maxnodes];
// Adds bidirectional edge
void addEdge(int s, int t, int cap){
  Edge a = {t, g[t].size(), 0, cap};
  Edge b = {s, g[s].size(), 0, cap};
  g[s].push_back(a);
  g[t].push_back(b);
}

bool dinic_bfs() {
  fill(dist, dist + nodes, -1);
  dist[src] = 0;
  int qt = 0;
  q[qt++] = src;
  for (int qh = 0; qh < qt; qh++) {
    int u = q[qh];
    for (int j = 0; j < (int) g[u].size(); j++) {
      Edge &e = g[u][j];
      int v = e.to;
      if (dist[v] < 0 && e.f < e.cap) {
        dist[v] = dist[u] + 1;
        q[qt++] = v;
      }
    }
  }
  return dist[dest] >= 0;
}

int dinic_dfs(int u, int f) {
  if (u == dest)
    return f;
  for (int &i = work[u]; i < (int) g[u].size(); i++) {
    Edge &e = g[u][i];
    if (e.cap <= e.f) continue;
    int v = e.to;
    if (dist[v] == dist[u] + 1) {
      int df = dinic_dfs(v, min(f, e.cap - e.f));
      if (df > 0) {
        e.f += df;
        g[v][e.rev].f -= df;
        return df;
      }
    }
  }
  return 0;
}

int maxFlow(int _src, int _dest) {
  src = _src;
  dest = _dest;
  int result = 0;
  while (dinic_bfs()) {
    fill(work, work + nodes, 0);
    while (int delta = dinic_dfs(src, INT_MAX))
      result += delta;
  }
  return result;
}
void reinitialize(int size)
{
    for(int i =0; i<size+3; i++)
    {
        dist[i] = work[i] = q[i] = 0;
        g[i].clear();
    }

}

int main()
{
    freopen("input","r",stdin);
    int t;
    cin>>t;
    for(int z = 1; z<=t; z++)
    {
        int n,m;
        cin>>n>>m;
        int size = n + m + 2;
        int wins[n+1];
        bool possible[n+1];
        vector<tuple<int,int>> matches[n+1];
        int max = -INT_MAX;
        for(int i =1; i<=n; i++)
        {
            possible[i] = true;
            cin>>wins[i];
            if(wins[i] > max)
                max = wins[i];
        }
        for(int i =1; i<=m; i++)
        {
            int a,b;
            cin>>a>>b;
            matches[a].push_back(make_tuple(b,n+i));
            matches[b].push_back(make_tuple(a,n+i));
        }

        for(int team =1; team<=n; team++)
        {
            reinitialize(size);
            int totalWins =  wins[team] + matches[team].size();
            if(totalWins < max)
            {
                possible[team] = false;
                continue;
            }
            if(matches[team].size() == m && max <= totalWins)
                continue;
            bool edge = false;
            for(int j = 1; j<=n; j++)
            {
                int cap = totalWins - wins[j];
                addEdge(0, j, cap);
                if(j == team) continue;
                for(int k = 0; k<matches[j].size(); k++)
                {
                    int te = get<0>(matches[j][k]);
                    if(te == team) continue;
                    edge = true;
                    addEdge(j, get<1>(matches[j][k]), 1);
                }
            }
            for(int i =1; i<=m; i++)
                addEdge(n+i, size-1, 1);
            int flow = maxFlow(0, size-1);

            int val = m-flow-matches[team].size();
            if(val != 0 && edge)
                possible[team] = false;
            if(possible[team])
                for(int i =0; i<g[0].size(); i++)
                {
                    int w = g[0][i].f + wins[g[0][i].to];
                    if(w > totalWins && g[0][i].to != team)
                    {
                        possible[team] = false;
                        break;
                    }
                }
        }

        cout<<"Case #"<<z<<": ";
        for(int i=1; i<=n; i++)
            if(possible[i])
                cout<<"yes ";
            else
                cout<<"no ";
        cout<<"\n";



    }
}
