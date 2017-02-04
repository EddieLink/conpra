#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <tuple>
using namespace std;
struct Node
{
	int c; Node *l, *r;
	int intLeft, intRight;
	int markLeft, markRight;

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

	bool inInterval(int ind)
	{
		return ind >= intLeft && ind <= intRight;
	}

	void add(int left, int value)
	{
		propagate();
		c += value;
		if(isLeaf())
			return;
		if(l->inInterval(left))
			l->add(left, value);
		else
			r->add(left, value);
	}
	int setZero(int left, int right)
	{
		propagate();
		int oldC = c;
		if(isLeaf()) 
		{
			c = 0;
			resetMark();
			return oldC;
		}
		if(left == intLeft && right == intRight)
		{
			c = 0;
			l->updateSetMark(0);
			r->updateSetMark(0);
			return oldC;
		}
		int a,b;
		l->getIntersection(&a, &b, left, right);
		int dec1, dec2;
		dec1 = dec2 = 0;
		if(a != -1)
		{
			dec1 = l->setZero(a,b);
			c-=dec1;
		}
		r->getIntersection(&a, &b, left, right);
		if(a != -1)
		{
			dec2 = r->setZero(a,b);
			c-=dec2;
		}
		return dec1+dec2;
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
		markLeft = markRight = -1;
	}
	void updateMarkInters(int left, int right, int value)
	{
		if(left == intLeft && right == intRight)
		{
			updateSetMark(value);
			return;
		}
		if(isLeaf())
		{
			c = value;
			setMark = -1;
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
	void updateSetMark(int value)
	{
		propagate();
		setMark = value;		
	}
	void propagate()
	{
		if(setMark == -1)
			return;
		if(isLeaf())
		{
			c = setMark;
			resetMark();
			return;
		}
		c = 0;
		l->updateSetMark(0);
		r->updateSetMark(0);
		resetMark();
	}
};
void displayTree(Node* root)
{
	cout<<endl;
	cout<<root->c<<endl;
	queue<tuple<Node*, int>> q;
	q.push(make_tuple(root->l,1));
	q.push(make_tuple(root->r, 1));
	int lvl = 1;
	while(!q.empty())
	{
		Node* cur = get<0>(q.front());
		int newLvl = get<1>(q.front()); 
		q.pop();
		if(newLvl > lvl)
		{
			lvl++;
			cout<<endl;
		}

		cout<<cur->c<<" ";
		if(!cur->isLeaf())
		{
			q.push(make_tuple(cur->l, lvl+1));
			q.push(make_tuple(cur->r, lvl+1));
		}
	}
	cout<<endl;
}
int solve()
{
	int n,k; cin>>n>>k;
	vector<int> arr = vector<int>(n,0);
    Node root(arr);
    int caught = 0;
	for(int i =0; i<k; i++)
	{
		char c; cin>>c;
		switch(c)
		{
			case 's':
			{
				int x; cin>>x; x--;
				root.add(x, 1);
				// cout<<"Added "<<x<<": "<<root.getSum(x)<<"\n";
				break;
			}
			case 'd':
			{
				int x; cin>>x; x--;
				int y = root.getSum(x);
				if(y > 0)
				{
					root.add(x,-1);
					// cout<<"Removed "<<x<<": "<<root.getSum(x)<<"\n";
				}

				break;
			}
			default:
			{
				int l, r; cin>>l>>r; 
				l--; r--;
				int currentCaught = root.getSum(l,r);
				caught+=currentCaught;
				root.setZero(l, r);
				// cout<<"Removed between "<<l<<" and "<<r<<": "<<root.getSum(l,r)<<endl;
			}
		}
		// displayTree(&root);

	}
	return caught;
}
int main()
{
	// freopen("input","r",stdin);
	int t; cin>>t;
	for(int z = 1; z<=t; z++)
		cout<<"Case #"<<z<<": "<<solve()<<"\n";
}