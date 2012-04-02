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
#include <algorithm>


using std::ofstream;
using std::ifstream;
using std::ostream;
using std::vector;
using std::cout;
using std::endl;
using std::next_permutation;
class Rect
{
  public:
    Rect(int x1, int y1)
    {
      x = x1; y = y1;
    }
  int x;
  int y;
  int area() { return x * y; }
  void normalize()
  {
    int tempx = x;
    int tempy = y;
    if ( x<=y )
      return;
    else
    {
      x = tempy;
      y = tempx;
    }
  }
  friend ostream&
    operator<< (ostream& out, Rect& r)
  {
    out << r.x << " " << r.y << endl;
    return out;
  }
  bool operator== (Rect& rhs)
  {
    return (x == rhs.x && y == rhs.y );
  }
  Rect swap(int config)
  {
    if (config) return Rect(y,x);
    return Rect(x,y);
  }
};

vector< vector<int> > permus;
void init_permutations()
{
  int a[4] = {0,1,2,3};
  do
  {
    vector<int> s;
    s.assign(a,a+4);
    permus.push_back(s);
  } while (next_permutation(a,a+4));
}

void print_permu(vector<int> s)
{
  cout << s[0] << s[1] << s[2] << s[3] << endl;
}

vector<Rect> inputs;
void init_inputs()
{
  ifstream fin("packrec.in");
  while(fin.good())
  {
    int x=-1,y=-1;
    fin >> x;
    fin >> y;
    if (x!=-1)
      inputs.push_back(Rect(x,y));
  }
}

vector< vector<Rect> > allrects;

void init_allrects()
{
  for (int i = 0; i < permus.size(); i++) {
    for (int j = 0; j <= 0xf; j++) {
      vector<Rect> rects;
      for (int k = 0; k < 4; k++) {
        rects.push_back(inputs[permus[i][k]].swap(j&(0x1<<k)));
      }
      allrects.push_back(rects);
    }
  }
}

void print_allrects()
{
  cout <<  allrects.size() << endl;
}

int sum_x( const vector<Rect> &combo, int first, int last )
{
  int sum = 0;
  for (; first <= last; ++first) {
    sum += combo[first].x;
  }
  return sum;
}

int sum_y( const vector<Rect> &combo, int first, int last )
{
  int sum = 0;
  for (; first <= last; ++first) {
    sum += combo[first].y;
  }
  return sum;
}

int max_x( const vector<Rect> &combo, int first, int last )
{
  int max = 0;
  for (; first <= last; ++first) {
    max = std::max(max,combo[first].x);
  }
  return max;
}

int max_y( const vector<Rect> &combo, int first, int last )
{
  int max = 0;
  for (; first <= last; ++first) {
    max = std::max(max,combo[first].y);
  }
  return max;
}


Rect get_min_bbox(int layout,vector<Rect> combo)
{
  int bbox_x;
  int bbox_y;
  switch(layout)
  {
    case 1:
      {
        bbox_x = sum_x(combo,0,3);
        bbox_y = max_y(combo,0,3);
      }
      break;
    case 2:
      {
        int w1 = sum_x(combo,0,2);
        int w2 = combo[3].x;
        bbox_x = std::max(w1,w2);
        int h1 = max_y(combo,0,2);
        int h2 = combo[3].y;
        bbox_y = h1 + h2;
      }
      break;
    case 3:
      {
        int w1 = sum_x(combo,0,1);
        int w2 = combo[2].x;
        int w3 = combo[3].x;
        bbox_x = std::max(w1,w2) + w3;
        int h1 = max_y(combo,0,1);
        int h2 = combo[2].y;
        int h3 = combo[3].y;
        bbox_y = std::max(h1+h2,h3);
      }
      break;
    case 4:
      {
        int w1 = combo[0].x;
        int w2 = max_x(combo,1,2);
        int w3 = combo[3].x;
        bbox_x = w1 + w2 + w3;
        int h1 = combo[0].y;
        int h2 = sum_y(combo,1,2);
        int h3 = combo[3].y;
        bbox_y = std::max(std::max(h1,h2),h3);
      }
      break;
    case 5:
      {
        int w1 = max_x(combo,0,1);
        int w2 = combo[2].x;
        int w3 = combo[3].x;
        bbox_x = w1 + w2 + w3;
        int h1 = sum_y(combo,0,1);
        int h2 = combo[2].y;
        int h3 = combo[3].y;
        bbox_y = std::max(std::max(h1,h2),h3);
      }
      break;
    case 6:
      {
        if ( combo[1].x >= combo[0].x )
        {
          int top_w = combo[0].x + combo[3].x;
          int low_w = combo[1].x + combo[2].x;
          int most_w = std::max(top_w, low_w);
          int l_h = combo[0].y + combo[1].y;
          int r_h = combo[2].y + combo[3].y;
          if ( top_w <= low_w )
          {
            if (( (combo[1].x + combo[3].x) <=  most_w )
                || ( combo[2].y >= combo[1].y ))
            {
              bbox_x = most_w;
              bbox_y = std::max(l_h,r_h);
            }
            else
            {
              int m_h = combo[1].y + combo[3].y;
              bbox_x = most_w;
              bbox_y = std::max(l_h,m_h);
            }
          }
          else
          {
            if (( (combo[1].x + combo[3].x) <= most_w )
                || ( combo[2].y >= combo[1].y ))
            {
              bbox_x = most_w;
              bbox_y = std::max(l_h,r_h);
            }
            else
            {
              int m_h = combo[1].y + combo[3].y;
              bbox_x = most_w;
              bbox_y = std::max(l_h,m_h);
            }
          }
        }
        else /* fake */
        {
              bbox_x = 1000;
              bbox_y = 1000;
        }
      }
      break;
  }
  return Rect(bbox_x,bbox_y);
}

void print_combo(vector<Rect> combo)
{
  for (int i = 0; i < combo.size(); i++) {
    cout << i << ": " << combo[i] << endl;
  }
}

vector<Rect> results;
void scan_allrects()
{
  int min_area = 9999999;
  for (int i = 0; i < allrects.size(); i++) {
    vector<Rect> combo = allrects[i];
    for (int j = 1; j <= 6; j++) {
      Rect bbox = get_min_bbox(j,combo);
      if ( bbox.area() == 750 )
      {
        printf("####\e[1;37m\e[41m j:%d  \e[0m####\n", 
            j );
        print_combo(combo);
      }
      if (bbox.area()<min_area)
      {
        //printf("####\e[1;37m\e[41m overriding with: x,y:%d,%d \e[0m####\n", 
            //bbox.x, bbox.y );
        results.clear();
        results.push_back(bbox);
        min_area = bbox.area();
      }
      else if ( bbox.area() == min_area )
      {
        results.push_back(bbox);
      }
    }
  }
  printf("####\e[1;37m\e[41m min area:%d \e[0m####\n", min_area);
}

void print_results()
{
  for (int i = 0; i < results.size(); i++) {
    cout << results[i] << endl;
  }
}

void normalize_results()
{
  for (int i = 0; i < results.size(); i++) {
    results[i].normalize();
  }
}

bool sortfunc(Rect lhs, Rect rhs)
{
  return ( lhs.x < rhs.x );
}

vector<Rect> dedup_results()
{
  vector<Rect> newresults;
  for (int i = 0; i < results.size(); i++) {
    if (newresults.empty())
    {
      newresults.push_back(results[i]);
      continue;
    }
    bool found = false;
    for (int j = 0; j < newresults.size(); j++) {
      if (newresults[j]==results[i])
      {
        found = true;
        break;
      }
    }
    if ( found )
      continue;
    else
      newresults.push_back(results[i]);
  }

  // sort here;
  std::sort(newresults.begin(),newresults.end(),sortfunc);
  
  return newresults;
}

int main(int argc, const char *argv[])
{

  init_inputs();
  /*
  for (int i = 0; i < inputs.size(); i++) {
    cout << inputs[i];
  }
  */

  init_permutations();
  /*
  for (int i = 0; i < permus.size(); i++) {
    print_permu(permus[i]);
  }
  */

  init_allrects();
  //print_allrects();

  scan_allrects();
  //print_results();
  normalize_results();
  vector<Rect> newresults = dedup_results();

  ofstream fout("packrec.out");
  for (int i = 0; i < newresults.size(); i++) {
    if (i==0)
      fout << newresults[i].area() << endl;
    fout << newresults[i];
  }

  return 0;
}
