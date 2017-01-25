#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int ct;
struct Node{
	bool word, conflict;
	map<char, Node> edges;
	int words; 

	void addWord(string s)
	{
		words++;
		if(s.length() == 0)
		{
			word = true;
			if(words > 1)
			{
				conflict = true;
				ct++;
			}
			return;
		}
		if(this->word && !conflict)
		{
			ct++;
			conflict = true;
		}
		if(edges.find(s[0]) == edges.end())
			edges[s[0]] = Node();
		edges[s[0]].addWord(s.substr(1));
	}
	Node(): word(false), words(0), conflict(false){};
};
int solve()
{
	int n; cin>>n; ct = 0;
	Node root;
	int prefixes = 0;
	for(int i =0; i<n; i++)
	{
		string s; cin>>s;
		root.addWord(s);
	}
	return ct;
}
int main()
{
	int t; cin>>t;
	for(int z = 1; z<=t; z++)
		cout<<"Case #"<<z<<": "<<solve()<<"\n";
}
