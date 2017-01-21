#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define MAX 100
typedef int t;

struct Network
{
    int size;
    bool** edges;
    t** capacity;
    t** flow;
    int source, target;

    void initFlow()
    {
        for(int i =0; i<size; i++)
            for(int j =0; j<size; j++)
                flow[i][j] = 0;
    }
    Network(t c[][3], edges[][MAX], int s, int t, int size)
    {

     /*   for(int i =0 ;i<size; i+e+)
            for(int j =0; j<size; j++)
            {
                capacity[i][j] = c[i][j];
                this->edges[i][j] = edges[i][j];
            }

        source = s;
        target = t;
        this->size = size;
        initFlow();*/
    }
    Network(t c[][MAX], bool edges[][MAX], vector<int> s, vector<int> t, int size)
    {
        this->size = size + 2;
        for(int i =0; i<s.size(); i++)
        {
            capacity[0][s[i]] = INT_MAX;
            edges[0][s[i]] = true;
        }
        for(int i = 0; i<t.size(); i++)
        {
            capacity[t[i]][size + 1] = INT_MAX;
            edges[t[i]][size+1] = true;
        }

        for(int i =0; i<size; i++)
            for(int j =0; j<size; j++)
            {
                capacity[i+1][j+1] = c[i][j];
                edges[i+1][j+1] = edges[i][j];
            }
        initFlow();
    }
    Network residualNetwork()
    {
        t cap[size][size];
        bool edg[size][size];
        for(int i =0; i<size; i++)
            for(int j = 0; j<size; j++)
            {
                if(edges[i][j])
                    cap[i][j] = capacity[i][j] - flow[i][j];
                else if(edges[j][i])
                    cap[i][j] = flow[j][i];
                else
                    cap[i][j] = 0;
                if(cap[i][j]) edg[i][j] = true;
                else    edg[i][j] = false;
            }
//        return Network(cap, edg, source, target, size);
    }
};

int main()
{
    t c[3][3];
    bool edges[3][3];
    for(int i =0; i<3; i++)
        for(int j =0; j<3; j++)
    {

        c[i][j] = 0;
        edges[i][j] = false;
    }

    Network(c,edges, 0,2,3);
}
