#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Node{
	typedef map<char, Node*> dict;
	bool word;
	int winning;
	dict edges;

	void addWord(string s)
	{
		if(s.length() == 0)
		{
			word = true;
			winning = 1;
			return;
		}
		if(s.length() > 1)
			winning = -2;
		if(s.length() == 1 && winning == -1)
			winning = 0;
		if(edges.find(s[0]) == edges.end())
			edges[s[0]] = new Node;
		edges[s[0]]->addWord(s.substr(1));
	}
	int markWinners()
	{
		if(winning == 0 || winning == 1|| winning == 2 || winning == 3)
			return winning;
		bool canDecide = false, win = false, lose = false, cannotDecide = false;
		for(dict::iterator it = edges.begin(); it!=edges.end(); it++)
		{
			Node *c = it->second;
			int x = c->winning;
			if(x <= -1)
				x = c->markWinners();
			if(x == 3)
				canDecide = true;
			else if(x == 2)
				cannotDecide = true;
			else if(x == 1)
				lose = true;
			else if(x == 0)
				win = true;
		}
		if(cannotDecide && !canDecide && !win && !lose)
			winning = 3;
		else
		{
			if(lose && !win && !canDecide)
				winning = 0;
			if(win && !lose && !canDecide)
				winning = 1;
			if(canDecide || (win && lose))
				winning = 2;
		}
		return winning;
	}

	Node(): word(false), winning(-1){};
	~Node()
	{
		for(dict::iterator i = edges.begin(); i!=edges.end(); i++)
			delete i->second;
	}
};
void solve()
{
	int n, w; cin>>n>>w;
	Node root;
	for(int i =0; i<w; i++)
	{
		string s; cin>>s;
		root.addWord(s);
	}
	int win = root.markWinners();
	//  cout<<win<<endl; return;
	bool outcomes[2];
	if(win == 1)
	{
		outcomes[0] = true;
		outcomes[1] = (n%2);
	}
	else if(win == 0)
	{
		outcomes[0] = !(n%2);
		outcomes[1] = false;
	}
	else if(win == 2)
	{
		outcomes[0] = true;
		outcomes[1] = true;
	}
	else
	{
		outcomes[0] = false;
		outcomes[1] = false;
	}
	map<bool, string> o;
	o[true] = "victory"; o[false] = "defeat";
	cout<<o[outcomes[0]]<<endl<<o[outcomes[1]]<<endl<<o[!outcomes[0]]<<endl<<o[!outcomes[1]]<<endl;
}
int main()
{
	int t; cin>>t;
	for(int z = 1; z<=t; z++)
	{
		cout<<"Case #"<<z<<":\n";
		solve();
	}
}
