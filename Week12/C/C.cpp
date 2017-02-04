#include <map>
#include <cassert>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <utility>
using namespace std;
#define DBG 0

typedef pair<int,int> ii;

int main(){
  freopen("inputGen","r",stdin);
  int t;
  cin >> t;
  for(int _t=1; _t<=t; ++_t){
    // read input
    int n,m,k,l; cin>>n>>m>>k>>l;
    vector<vector<ii> >G(n,vector<ii>());
    vector<int> crooms(n,INT_MAX);
    for(int _m=0; _m<m; ++_m){
      int a,b,lvl; cin>>a>>b>>lvl; a--; b--;
      G[a].push_back(ii(b,lvl));
      G[b].push_back(ii(a,lvl));
    }
    for(int _k=0; _k<k; ++_k){
      int a,d; cin>>a>>d; a--;
      crooms[a] = d;
    }


    #if DBG
      cout << "control rooms: ";
      for(int i=0; i<crooms.size(); ++i)
        cout << crooms[i] << " ";
      cout << endl << "G:\n";
      for(int i=0; i<G.size(); ++i){
        cout << i << ": ";
        for(int j=0; j<G[i].size(); ++j)
          printf("%d(lvl: %d) ", G[i][j].first, G[i][j].second);
        cout << endl;
      }
    #endif



    queue<int> Q;
    Q.push(0);
    vector<bool> visited(n,false);
    visited[0] = true;
		int minimum_drain_level = INT_MAX;
    priority_queue<ii,vector<ii>, less<ii> > Pedges; // (lvl, nnode)

    int visited_nodes = 1;
    while(visited_nodes < n){
      while(!Q.empty()){
        int v = Q.front(); Q.pop();
        if(crooms[v] != INT_MAX){
          minimum_drain_level = min(minimum_drain_level, crooms[v]);
        }

        for(int i=0; i<G[v].size(); ++i){
          int u = G[v][i].first;
          int lvl = G[v][i].second;
          if(!visited[u]){
            if(lvl >= l){
              visited_nodes++;
              visited[u] = true;
              Q.push(u);
            }
            else{
             Pedges.push(ii(lvl, u));
            }
          }
        }
      }
      if(visited_nodes < n){
        ii e = Pedges.top(); Pedges.pop();
        int lvl = e.first;
        int v = e.second;
        if(minimum_drain_level > lvl)
          break;
        l = lvl;
        Q.push(v);
        if(!visited[v])
          visited_nodes++;
        visited[v] = true;
      }
      else
        break;
    }

    printf("Case #%d: ", _t);
    if(visited_nodes < n)
      cout<<"impossible\n";
  	else
      cout << l << endl;

  }

    return 0;
}
