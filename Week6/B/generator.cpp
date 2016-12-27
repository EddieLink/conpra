#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;
int main()
{
  srand(time(NULL));
  freopen("inputGen","w",stdout);
  int n =15;
  int startx, starty;
  startx = rand()%n;
  starty = rand()%n;
  cout<<"1\n"<<n<<" "<<n<<"\n";
  for(int i =0; i<n; i++)
  {
    for(int j =0; j<n; j++)
    {
      if(i == startx && j == starty)
      {
        cout<<"L";
        continue;
      }
      int x = rand()%1000;
      if(x<450)
      {
        cout<<"_";
        continue;
      }
      x = rand()%1000;
      if(x<400)
      {
        cout<<"T";
        continue;
      }
      cout<<"#";

    }
    cout<<"\n";
  }
  cout<<"\n";
}
