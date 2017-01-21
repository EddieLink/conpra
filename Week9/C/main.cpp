//dinic's algorithm found here: https://sites.google.com/site/indy256/algo_cpp/dinic_flow
#include <algorithm>
#include <vector>
#include <climits>
#include <iostream>
#include <sstream>
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

//string split methods from http://stackoverflow.com/a/236803
void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}
vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
char x[50000];

int main()
{
    int t;
    cin>>t;
    for(int z= 1; z<=t; z++)
    {
        int n,m;
        cin>>n>>m;
        int size = n+m + 2;
        for(int i =0; i<size; i++)
        {
            g[i].clear();
            dist[i] = work[i] = q[i] = 0;
        }
        for(int i =1; i<=m; i++)
            addEdge(0,i, 1);
        cin.getline(x,50000);
        for(int i=1; i<=n; i++)
        {
            addEdge(m+i+1, size-1, 1);
            cin.getline(x,50000);
            string s(x);

            vector<string> pres = split(s, ',');
            for(int j = 0; j< pres.size(); j++)
            {
                if(pres[j].find('-') != string::npos)
                {
                    vector<string> range = split(pres[j], '-');
                    int first = stoi(range[0]);
                    int last = stoi(range[1]);
                    for(int k = first; k<=last; k++)
                        addEdge(k, m+i+1, 1);
                }
                else if(pres[j].length() > 0)
                    addEdge(stoi(pres[j]),m+i+1, 1);
            }
        }
        cout<<"Case #"<<z<<": ";
        if(maxFlow(0,size-1) < n)
            cout<<"no\n";
        else
            cout<<"yes\n";

    }
}
