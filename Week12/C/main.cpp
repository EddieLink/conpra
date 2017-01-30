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
	queue<int> q2;
	vector<int> used = vector<int>(n, -1);
	int visited = 1;
	typedef tuple<int,int> tup;
	auto comp = [](tup a, tup b){
		return get<0>(a) < get<0>(b);
	};
	int minL = INT_MAX;
	priority_queue<tup, vector<tup>, decltype(comp)> pq(comp);
	while(!q.empty())
	{
		int id = q.front(); q.pop_front();
		used[id] = currentD;
		if(contr[id] != -1)
			minL = min(minL, contr[id]);
		for(int i =0; i<v[id].size(); i++)
		{
			int room = v[id][i].room;
			if(used[room] == -1)
				if(v[id][i].level >= currentD)
				{
					q.push_front(room);
					visited++;
					used[room] = currentD;
				}
				else
					pq.push(make_tuple(v[id][i].level, room));
		}
		if(visited >= n)
			break;
		if(q.empty())
		{
			if(!pq.empty())
			{
				tup x = pq.top(); pq.pop();
				int level, room;
				level = get<0>(x);
				room = get<1>(x);
				if(minL <= level)
				{
					currentD = level;
					q.push_front(room);
					if(used[room] == -1)
						visited++;
					used[room] = currentD;
				}
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
