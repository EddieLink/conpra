#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
#include <tuple>
using namespace std;

struct Node
{
	int c; Node *l, *r;
	int intLeft, intRight;
	int markValue, markParentValue;

	bool isLeaf()
	{
		return intLeft == intRight;
	}
	Node(int v, int ind)
	{
		resetMark();
		c = v;
		intLeft = intRight = ind;
	}
	Node(Node* a, Node* b)
	{
		resetMark();
		c = max(a->c , b->c);
		l = a; r = b;
		intLeft = a->intLeft;
		intRight = b->intRight;
	}
	Node(int n, int left, int right)
	{
		if(left > right)
			return;
		c = 0; resetMark();
		if(left == right)
		{
			intLeft = intRight = left;
			return;
		}
		n = (1<<(int)ceil(log2(n)));
		right = max(right, n-1);
		intLeft = left; intRight = right;
        l = new Node(n/2, left, ((left+right)/2));
        r = new Node(n/2, ((left+right)/2)+1, right);
	}
	Node(vector<int> arr)
	{
		resetMark();
		int i;
		queue<Node*> q;
		int n = arr.size();
		int m = 1<<(int)ceil(log2(n));
		for(i = 0; i<m; i+=2)
		{
			Node *a, *b;
			if(i < n)
				a = new Node(arr[i], i);
			else
				a = new Node(0, i);
			if(i+1 < n)
				b = new Node(arr[i+1], i+1);
			else
				b = new Node(0, i+1);

			q.push(new Node(a,b));
		}
		while(!q.empty())
		{
			Node *a,*b;
			a = q.front(); q.pop();
			if(q.empty())
			{
				c = a->c;
				l = a->l; r = a->r;
				intLeft = a->intLeft; intRight = a->intRight;
				break;
			}
			b = q.front(); q.pop();
			q.push(new Node(a,b));
		}
	}

	void add(int left, int right, int value)
	{
		propagate();
		int m = getMax(left,right) + value;
        c = max(markValue, max(m, c));
		if(isLeaf()) return;
		updateMarkInters(left, right, m);
		getMax(left,right);
	}

	int getMax(int left, int right = -1)
	{
		propagate();
		if(right == -1) right = intRight;
		if(intLeft == left && intRight == right)
		{
			if(isLeaf())
				return c;
			return max(c, max(l->c, r->c));
		}
		int s = 0, lInt, rInt;
			l->getIntersection(&lInt, &rInt, left, right);
		if(lInt!=-1)
			s = max(s, l->getMax(lInt, rInt));

		r->getIntersection(&lInt, &rInt, left,right);
		if(lInt != -1)
			s = max(s, r->getMax(lInt,rInt));
		if(s>c)
		{
			c = s;
			if(!isLeaf())
				updateMarkInters(left, right ,c);
		}
		return s;
	}

	~Node()
	{
		if(!isLeaf())
			delete l, r;
	}

	private:
	void getIntersection(int* left, int *right, int a, int b)
	{
		*left = max(intLeft, a);
		if(*left > intRight)
		{
			*left = *right = -1;
			return;
		}
		*right = min(intRight, b);
		if(*right < intLeft)
		{
			*right = *left = -1;
			return;
		}
	}
	void resetMark()
	{
		markValue = 0;
		markParentValue = 0;
	}
	void updateMarkInters(int left, int right, int value)
	{
		if(left == intLeft && right == intRight || isLeaf())
		{
			updateMark(value);
			return;
		}
		int il, ir;
		l->getIntersection(&il, &ir, left, right);
		if(il!=-1)
			l->updateMarkInters(il, ir, value);
		r->getIntersection(&il, &ir, left, right);
		if(il!=-1)
			r->updateMarkInters(left, right, value);
	}
	void updateMark(int value)
	{
		markValue = max(value, markValue);
		propagate();
	}
	void propagate()
	{
		if(markValue == 0)
			return;
		if(isLeaf())
		{
			c = max(markValue,c);
			resetMark();
			return;
		}
		c = max(markValue,c);
		r->updateMark(markValue);
		l->updateMark(markValue);
		resetMark();
	}
};
int _i;
void displayTree(Node* root)
{
	queue<tuple<Node*,int>> q;
	cout<<root->c<<"\n";
	if(!root->isLeaf())
	{
		q.push(make_tuple(root->l,1));
		q.push(make_tuple(root->r, 1));
	}
	int lvl = 1;
	while(!q.empty())
	{
		Node* it = get<0>(q.front());
		int newLvl = get<1>(q.front()); q.pop();
		if(newLvl > lvl)
		{
			lvl++;
			cout<<endl;
		}
		cout<<it->c<<" ";
		if(!it->isLeaf())
		{
			q.push(make_tuple(it->l, lvl+1));
			q.push(make_tuple(it->r, lvl+1));
		}

	}
	cout<<endl;

}
string solve()
{
	int n, k; cin>>n>>k;
	vector<int> arr = vector<int>(n);
    //Node root(n,0,n-1);
    Node root(arr);
    vector<int> sol;
	for(_i =0; _i<k; _i++)
	{
		int w, h, p; cin>>w>>h>>p;
		root.add(p, p+w-1, h);
		sol.push_back(root.getMax(0));
		//displayTree(&root); cout<<endl;
	}

	string s = "";
	for(int i =0; i<sol.size(); i++)
		s+=to_string(sol[i])+" ";

	return s;
}
int main()
{
	freopen("input2","r",stdin);
	int t; cin>>t;
	for(int z = 1; z<=t; z++)
		cout<<"Case #"<<z<<": "<<solve()<<"\n";
}
