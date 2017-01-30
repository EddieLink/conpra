#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>
#include <algorithm>
using namespace std;

struct hallway
{
	int room, level;
	hallway(int r, int l): room(r), level(l) {};
};

typedef vector<hallway> halv;
string solve()
{
  int n,m,k,l; cin>>n>>m>>k>>l;
  typedef vector<int> vInt;
  typedef vector<bool> vBool;
  vector<halv> v = vector<halv>(n);
  int minL = INT_MAX;
  for(int i =0; i<m; i++)
	{
    int ai,bi,li; cin>>ai>>bi>>li;
    ai--; bi--;
    v[ai].push_back(hallway(bi,li));
    v[bi].push_back(hallway(ai,li));
	}
	vector<int> contr = vector<int>(n, -1);
	for(int i =0; i<k; i++)
	{
		int ai,di; cin>>ai>>di;
		contr[ai-1] = di;
	}
	if(n == 1)
		return to_string(l);
	int currentD = l;

	deque<int> q; q.push_front(0);
	vector<int> used = vector<int>(n, -1);
	int visited = 1;
	auto comp = [contr](int a, int b){
		return contr[a] < contr[b];
	};
	int maxL = -INT_MAX;
	priority_queue<int, vector<int>, decltype(comp)> pq(comp);
	used[0] = currentD;
	while(!q.empty())
	{
		int id = q.front(); q.pop_front();
		if(contr[id] != -1)
			pq.push(id);
		for(int i =0; i<v[id].size(); i++)
		{
			int room = v[id][i].room;
			if(currentD <= v[id][i].level && (used[room] == -1 || used[room] > currentD))
			{
				q.push_front(room);
				if(used[room] == -1 && id != room)
					visited++;
				used[room] = currentD;
			}
			else if(currentD > v[id][i].level && (used[room] == -1 || used[room] > currentD))
				maxL = max(maxL, v[id][i].level);
		}
		if(visited >= n)
			return to_string(currentD);
		if(q.empty())
		{
			if(!pq.empty())
			{
				int id2 = pq.top(); pq.pop();
				currentD = min(currentD, max(contr[id2], maxL));
				maxL = -INT_MAX;
				if(currentD <= contr[id2])
					contr[id2] = -1;
				if(used[id2] == -1)
					visited++;				
				used[id2] = currentD;
				q.push_front(id2);
			}
		}
	}
	if(visited < n)
		return "impossible";

	return to_string(currentD);
}

int main()
{
	int t; cin>>t;
	for(int z = 1; z<=t; z++)
		cout<<"Case #"<<z<<": "<<solve()<<"\n";
}
