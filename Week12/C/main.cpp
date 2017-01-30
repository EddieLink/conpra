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
    vector<vBool> levels = vector<vBool>(n, vBool(10001, false));
    vector<halv> v = vector<halv>(n);
    int minL = INT_MAX;
    for(int i =0; i<m; i++)
	{
        int ai,bi,li; cin>>ai>>bi>>li;
        ai--; bi--;
        v[ai].push_back(hallway(bi,li));
        v[bi].push_back(hallway(ai,li));
	}
	vInt drained = vInt(10001,0);
	for(int i =0; i<n; i++)
	{
		int maxL = -INT_MAX;
		for(int j =0; j<v[i].size(); j++)
			maxL = max(maxL, v[i][j].level);
		minL = min(minL, maxL);
		for(int k1 =maxL; k1>=0; k1--)
		{
			levels[i][k1] = true;
			drained[k1]++;
		}
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
			if(levels[room][currentD] && (used[room] == -1 || used[room] > currentD))
			{
				q.push_front(room);
				if(used[room] == -1)
					visited++;
				used[room] = currentD;
			}
		}
		if(visited >= n)
			return to_string(currentD);
		if(q.empty())
		{
			if(!pq.empty())
			{
				int id2 = pq.top(); pq.pop();
				currentD = min(currentD, max(contr[id2], minL));
				contr[id2] = -1;
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
