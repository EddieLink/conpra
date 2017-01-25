#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

#define iterateEdges(node) for(map<char, Node>::iterator it = node.edges.begin(); it!=node.edges.end(); it++)
struct Node{
  bool word;
  map<char, Node> edges;
  int words;

  int addWord(string s)
  {
    if(s.length() == 0)
    {
      this->word = true;
      return 0;
    }
    if(this->word)
      words++;
    if(edges.find(s[0]) == edges.end())
      edges[s[0]] = Node();
    words += edges[s[0]].addWord(s.substr(1, s.length()-1));
    return words;
  }
  Node(): word(false), words(0){};
};
int count(Node x)
{
  int ct = 0;
  if(x.word)
    ct+=(x.words > 1)?1:0;
  iterateEdges(x)
    ct+=count(it->second);
  return ct;
}
int solve()
{
  int n; cin>>n;
  Node root;
  int prefixes = 0;
  for(int i =0; i<n; i++)
  {
    string s; cin>>s;
    root.addWord(s);
  }
  //iterateEdges(root)
    //prefixes+=count(it->second);
  return root.words;
}
int main()
{
  freopen("input","r",stdin);
  int t; cin>>t;
  for(int z = 1; z<=t; z++)
    cout<<"Case #"<<z<<": "<<solve()<<"\n";
}
