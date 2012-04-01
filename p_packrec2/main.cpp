/*
ID:wang0101
PROG:packrec
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <set>


using std::ofstream;
using std::ifstream;
using std::ostream;
using std::vector;
using std::cout;
using std::endl;
class Rect
{
  public:
    Rect(int x1, int y1)
    {
      x = x1; y = y1;
    }
  int x;
  int y;
  friend ostream&
    operator<< (ostream& out, Rect& r)
  {
    out << r.x << " " << r.y << endl;
    return out;
  }
  Rect swap(int config)
  {
    if (config) return Rect(y,x);
    return Rect(x,y);
  }
};

typedef vector<int> Combination;
typedef vector<Combination> Combinations;
typedef pair<int,bool> Wrap;
Combinations generate_combinations(int n)
{
  Combinations result;


}

int main(int argc, const char *argv[])
{
  vector<Rect> inputs;
  ifstream fin("packrec.in");
  while(fin.good())
  {
    int x=-1,y=-1;
    fin >> x;
    fin >> y;
    if (x!=-1)
      inputs.push_back(Rect(x,y));
  }


  for (int i = 0; i < inputs.size(); i++) {
    cout << inputs[i];
  }


  ofstream fout("packrec.out");
  return 0;
}
