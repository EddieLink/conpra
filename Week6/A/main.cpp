#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
vector<int> equiv(int a)
{
	switch(a)
	{
		case 0: return {0, 8};
		case 1: return {0, 1, 3, 4, 7, 8, 9};
		case 2: return {2, 8};
		case 3: return {3, 8, 9};
		case 4: return {4, 8, 9};
		case 5: return {5, 6, 8, 9};
		case 6: return {6, 8};
		case 7: return {0, 3, 7, 8, 9};
		case 8: return {8};
		default: return {8,9};
	}
}
vector<int> needed(int a)
{
	switch(a)
	{
		case 0: return {0,1,2,4,5,6};
		case 1: return {2,5};
		case 2: return {0,2,3,4,6};
		case 3: return{0,2,3,5,6};
		case 4: return {1,2,3,5};
		case 5: return {0,1,3,5,6};
		case 6: return {0,1,3,4,5,6};
		case 7: return {0,2,5};
		case 8: return {0,1,2,3,4,5,6};
		default: return {0,1,2,3,5,6};
	}
}

vector<vector<int>>sol, timelog, current;
int broken[4][7];
int n;
bool correct(vector<int> c)
{
	if(c[0] > 23 || c[1] > 59)
		return false;
	int n = current.size();
	if(!n)
		return true;
	n--;
	vector <int> dif = current[n];
	if(dif[0] == c[0] && c[1] == dif[1]+1)
		return true;
	if(c[0] == dif[0]+1 && c[1] == 0 && dif[1] == 59)
		return true;
	if(!c[0] && !c[1] && dif[0] == 23 && dif[1] == 59)
		return true;

	return false;
}
void setBack(vector<vector<int>> assumptions)
{
			for(int a = 0; a<assumptions.size(); a++)
				broken[assumptions[a][0]][assumptions[a][1]] = assumptions[a][2];
			current.pop_back();
}
void backtr(int pos)
{
	if(pos == n)
	{
		for(int i =0; i<sol.size(); i++)
			if(sol[i][0] == current[0][0] && sol[i][1] == current[0][1] && sol[i][2] == current[0][2] && sol[i][3] == current[0][3])
				return;
		sol.push_back(current[0]);
		return;
	}
	vector<int> cur = timelog[pos];
	vector<int> v = {cur[0]/10, cur[0]%10, cur[1]/10, cur[1]%10};
	vector<int> prop(4, 0);
	vector<vector<int>> attempts;

		vector<int> a = equiv(v[0]);
		vector<int> b = equiv(v[1]);
		vector<int> c = equiv(v[2]);
		vector<int> d = equiv(v[3]);

		for(int i1 = 0; i1<a.size(); i1++)
		{
			prop[0] = a[i1];
			for(int i2 = 0; i2<b.size(); i2++)
			{
				prop[1] = b[i2];
				for(int i3 = 0; i3<c.size(); i3++)
				{
					prop[2] = c[i3];
					for(int i4 = 0; i4<d.size(); i4++)
					{
						prop[3] = d[i4];
						attempts.push_back(prop);
					}
				}
			}
		}

	for(int i =0; i<attempts.size(); i++)
	{
		vector<int> x = {attempts[i][0]*10+attempts[i][1], attempts[i][2]*10 + attempts[i][3]};
		if(correct(x))
		{
			current.push_back(x);
			vector<vector<int>> assumptions;
			bool cor = true;
			for(int j =0; j<4; j++)
			{
				vector<int>ass;
				if(attempts[i][j] != v[j])
				{
					vector<int>segm1 = needed(attempts[i][j]);
					vector<int>segm2 = needed(v[j]);

					for(int a = 0; a<segm1.size(); a++)
					{
						ass.push_back(j);
						ass.push_back(segm1[a]);
						ass.push_back(broken[j][segm1[a]]);
						assumptions.push_back(ass);
						ass.clear();
						if(find(segm2.begin(), segm2.end(), segm1[a]) == segm2.end())
						{
							if(broken[j][segm1[a]] == 1)
							{
								setBack(assumptions);
								cor = false;
								break;
							}
							broken[j][segm1[a]] =0;
						}
						else
						{
							if(broken[j][segm1[a]] == 0)
							{
								setBack(assumptions);
								cor = false;
								break;
							}
							broken[j][segm1[a]] = 1;
						}
					}

				}
				else
				{
					vector<int>segm = needed(v[j]);
					for(int a =0; a<segm.size(); a++)
					{
						ass.push_back(j);
						ass.push_back(segm[a]);
						ass.push_back(broken[j][segm[a]]);
						assumptions.push_back(ass);
						ass.clear();
						if(broken[j][segm[a]] == 0)
						{
							setBack(assumptions);
							cor = false;
							break;
						}
						broken[j][segm[a]] = 1;
					}
				}
				if(!cor)
					break;
			}
			if(cor)
			{
				backtr(pos+1);
				setBack(assumptions);
			}
		}
    }
}
void displaySol(int i)
{
	if(sol[i][0]<10)
		cout<<"0";
	cout<<sol[i][0]<<":";
	if(sol[i][1]<10)
		cout<<"0";
	cout<<sol[i][1]<<"\n";
}
int main()
{
	int t;
	cin>>t;
	for(int z =1; z<=t; z++)
	{
		cin>>n;
		sol.clear();
		timelog.clear();
		for(int j = 0; j<4; j++)
			for(int i =0; i<=6; i++)
				broken[j][i] =-1;
		current.clear();
		for(int i =0; i<n; i++)
		{
			string a,b;
			getline(cin, a, ':');
			getline(cin, b, '\n');
			vector<int> x;
			x.push_back(stoi(a));
			x.push_back(stoi(b));
			timelog.push_back(x);

		}
		backtr(0);

		cout<<"Case #"<<z<<":\n";
		for(int i=0; i<sol.size(); i++)
			displaySol(i);
		if(!sol.size())
			cout<<"none\n";


	}
}
