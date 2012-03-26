#ifndef __RECT_H__
#define __RECT_H__
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <iostream>

using namespace std;
extern int step;
class RectXY{
   public:
      int x;
      int y;
      RectXY(int ix, int iy) { x = ix, y=iy; }
      RectXY() { }
};
class RectCorxy{
   public:
   //   RectCorxy(int x_0, int y_0, int x_1, int y_1){ x0=x_0, y0=y_0,x1=x_1,y1=y_1;}
   //private:
      int x0;
      int y0;
      int x1;
      int y1;
};
class ResultRect{
   public:
    #if 0
      ResultRect(RectXY*  rect);
      ResultRect(ResultRect*  baseResult);
      //operator=()
      RectCorxy getArea();
      int traceDraw();
      vector<RectCorxy>  getPlace();
   protected:
      int initPlace();
      int updateArea();
      int addPlace();
      int removePlace();
   private:
    #endif
      int getStep(){ return this->step; }
      int setStep( int level ) { step = level; }
      ResultRect(){ step = 0; }
      int  step;
      RectCorxy         area;
      vector<RectCorxy> places;
};
class Rect{
   public:
      Rect(vector<RectXY>& input);
      int doPlace();
      int sort();
      int getMinResult();
   protected:
      int init();
   //   int genNewResults( ResultRect* resulti, vector<RectCorxy>::iterator& place, RectXY& rect );
      int genNewResults( ResultRect* resulti, RectCorxy* place ,RectXY& rect );
      //int genNewResults( vector<ResultRect>::reverse_iterator& resulti, vector<RectCorxy>::iterator& place, RectXY& rect );
      //int genNewResults(std::list<ResultRect>::reverse_iterator&, RectCorxy*, RectXY&);
      int updateResults(RectXY rect);
      int getPlace();
      int genRect();
      int genPlace();
      int modifyPlace();
      int deletePlace();
      int removeRect();
   private:
      vector<RectXY> rects;
      vector<ResultRect> results;
      vector< vector<ResultRect> >result_vector;
};

#endif
