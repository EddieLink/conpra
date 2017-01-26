#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;


struct Node
{
	int c; Node *l, *r;
	int intLeft, intRight;
    int markLeft, markRight, markValue;

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
		c = a->c + b->c;
		l = a; r = b;
		intLeft = a->intLeft;
		intRight = b->intRight;
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

	bool inInterval(int ind)
	{
		return ind >= intLeft && ind <= intRight;
	}
	void add(int ind, int value)
	{
		propagate();
		c += value;
		Node* nxt;
		if(!isLeaf())
		{
			if(l->inInterval(ind)) nxt = l;
			else nxt = r;
			nxt->add(ind, value);
		}
	}

	void add(int left, int right, int value)
	{
		propagate();
		c+=value * (right-left + 1);
		if(isLeaf())
			return;
		l->updateMarkInters(left, right, value);
		r->updateMarkInters(left, right, value);
	}
	int getSum(int left, int right = -1)
	{
		propagate();
		if(right == -1) right = left;
		if(intLeft == left && intRight == right)
			return c;
		int s = 0, lInt, rInt;
		l->getIntersection(&lInt, &rInt, left, right);
		if(lInt!=-1)
			s+=l->getSum(lInt, rInt);
		r->getIntersection(&lInt, &rInt, left,right);
		if(lInt != -1)
			s+=r->getSum(lInt,rInt);
		return s;
	}

	~Node()
	{
		if(!isLeaf())
			delete l, r;
	}

	private:
	void updateMarkInters(int left, int right, int value)
	{
		int lInt, rInt;
		getIntersection(&lInt, &rInt, left, right);
		if(lInt!=-1)
		{
			propagate();
			updateMark(lInt, rInt, value);
		}
	}
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
		markLeft = markRight = markValue = -1;
	}
	void updateMark(int left, int right, int value)
	{
		markLeft = left;
		markRight = right;
		markValue = value;
	}
	bool isMarked()
	{
		return markLeft != -1;
	}
	void propagate()
	{
		if(!isMarked())
			return;
		if(isLeaf())
		{
			c+=markValue;
			resetMark();
			return;
		}
		c+=markValue * (markRight - markLeft + 1);
		l->updateMarkInters(markLeft, markRight, markValue);
		r->updateMarkInters(markLeft, markRight, markValue);
		resetMark();
	}
};
int solve()
{
	int n, k; cin>>n>>k;
	vector<int> arr = vector<int>(n,0);
	Node root(arr);
	int val = 0; int lim = 1000000007;
	for(int i =0; i<k; i++)
	{
		char com;
		cin>>com;
		if(com == 'q')
		{
			int x; cin>>x;
			val+=root.getSum(x-1) % lim;

		}
		else
		{
			int l, r, v; cin>>l>>r>>v;
			root.add(l-1,r-1,v);

		}
	}
	return val % lim;
}
int main()
{
	freopen("input","r",stdin);
	int t; cin>>t;
	for(int z = 1; z<=t; z++)
		cout<<"Case #"<<z<<": "<<solve()<<"\n";
}
