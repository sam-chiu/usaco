/*
ID:wang0101
PROG:packrec
LANG:C++
*/
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <iostream>
#include <math.h>
using namespace std;
extern int step;
int op_step=0;
#define default_in   "packrec.in"
#define default_out  "packrec.out"
#define default_num   4
using namespace std;
int num = default_num;
string filen = string(default_in);
class RectXY;
vector<RectXY>in_rect;
class RectXY{
   public:
      int x;
      int y;
      RectXY(int ix, int iy) { x = ix, y=iy; }
      RectXY() { }
};
class RectCorxy{
   public:
      int x0;
      int y0;
      int x1;
      int y1;
};
class ResultRect{
   public:
      int getStep(){ return this->step; }
      int setStep( int level ) { step = level; }
      ResultRect(){ step = 0; }
      int  step;
      RectCorxy         area;
      vector<RectCorxy> places;
};
class Rect{
   public:
      Rect(vector<RectXY>& input)
      {
         rects = input;
         init();
      }
      int doPlace()
      { 
         for(vector<RectXY>::iterator xy = rects.begin(); xy != rects.end(); xy++)
         {
            updateResults(*xy);
         }
         return 0; 
      }
      int sort() { 
         return 0; 
      }
      int getMinResult() { 
         int area = 50*4*50;
         vector<ResultRect>*res = &result_vector.at(op_step);
         for(int i=0; i<result_vector.at(op_step).size();i++){
           int square = res->at(i).area.x1 * res->at(i).area.y1;
           if( area > square ) area = square; 
         }
         std::ofstream fout("packrec.out");
         fout << area << std::endl;
         for(vector<ResultRect>::iterator ri = res->begin(); ri != res->end(); ri++){
            if(ri->area.x1 * ri->area.y1 > area) continue;
            //if( ri->area.x1 < ri->area.y1 ) cout<< "PACK_RECT_XY:"<<ri->area.x1<<" "<<ri->area.y1<<endl;
            //else cout<< "PACK_RECT_XY:"<<ri->area.y1<<" "<<ri->area.x1<<endl;
            if ( ri->area.x1 < ri->area.y1 )
            {
              fout << ri->area.x1 << " " << ri->area.y1 << std::endl;
            }
            else
            {
              fout << ri->area.y1 << " " << ri->area.x1 << std::endl;
            }
         } 
         return area; 
      }
   protected:
      int init() 
      { 
         ResultRect i;
         RectCorxy  p;
         vector<ResultRect> step_vector;
         i.area.x0 = i.area.y0 = i.area.x1 = i.area.y1 = 0;
         p.x0 = p.y0 = 0, p.x1 = p.y1 = -1;
         i.places.push_back(p);
         i.setStep(0);
         result_vector.push_back(step_vector);
         result_vector.at(0).push_back(i);
         return 0; 
      }
      int genNewResults( ResultRect* resulti, RectCorxy* place ,RectXY& rect )
      {
        ResultRect  nextstepR ; 
        int nx = place->x0 + rect.x;
        int ny = place->y0 + rect.y;
#if 1
        if( (place->x1 !=-1 && place->x1 < nx )|| 
            (place->y1 !=-1 && place->y1 < ny ) ) return 0;
        //init nextstepR of area:
        nextstepR.area.x0 = resulti->area.x0;
        nextstepR.area.y0 = resulti->area.y0;
        nextstepR.area.x1 = resulti->area.x1;
        nextstepR.area.y1 = resulti->area.y1;
        //update area:
        if( nx > resulti->area.x1)
          nextstepR.area.x1 = nx;
        else
          nextstepR.area.x1 = resulti->area.x1;
        if( ny > resulti->area.y1)
          nextstepR.area.y1 = ny;
        else
          nextstepR.area.y1 = resulti->area.y1;
        //update places:
        for(vector<RectCorxy>::iterator np = resulti->places.begin(); 
            np != resulti->places.end(); np++ ) {
          //change places and push back to next step results:
          if( np->x0 == place->x0 && np->y0 == place->y0 && place->x1 == -1 && place->y1 == -1 )
            continue;
          RectCorxy newPlace;
          newPlace.x0=np->x0;
          newPlace.y0=np->y0;
          newPlace.x1=np->x1;
          newPlace.y1=np->y1;
          if(  np->x0 > place->x0 && np->x0 < place->x1 )
            if( np->y1 == -1 || np->y1 > place->y0 && np->y0 < place->y0 ) newPlace.y1 = place->y0;
          if(  np->y0 > place->y0 && np->y0 < place->y1 )
            if( np->x1 == -1 || np->x1 > place->x0 && np->x0 < place->x0 ) newPlace.x1 = place->x0; 
          nextstepR.places.push_back( newPlace );
        }
#endif            
        //genPlaces for this layout:
        RectCorxy p1,p2;
        p1.x0=nx,	p1.y0=place->y0,	p1.x1=place->x1,	p1.y1=place->y1;
        p2.x0=place->x0,	p2.y0=ny,	p2.x1=place->x1,	p2.y1=place->y1;

        nextstepR.places.push_back( p1 ); 
        nextstepR.places.push_back( p2 );
        nextstepR.setStep( op_step + 1 ); 
        result_vector.at(op_step+1).push_back(nextstepR);

        return 0;
      }
      int updateResults(RectXY rect)
      {
         RectXY rectyx;
         rectyx.x = rect.y, rectyx.y = rect.x;
         int i,j, num = result_vector.at(op_step).size();
         vector<ResultRect> step_vector;
         result_vector.push_back(step_vector);
         int pn ;
         RectCorxy  place;
         ResultRect *resulti;
         for(  i = num - 1 ; i >=0; i-- ){
           //add new results:
           resulti = &result_vector.at(op_step).at(i);
           if(resulti->getStep() < op_step) 
             break;
           pn = resulti->places.size();
           for( j = 0; j < pn ;  j++){
             //cout<<"__________debug::pn="<<pn<<" j="<<j<<endl;
             RectCorxy putit = resulti->places.at(j);
             genNewResults( resulti, &putit, rect );
             if(op_step>0) {
               genNewResults( resulti, &putit, rectyx );
             }
           }
         }
         op_step++;
         return 0; 
      }
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
int genRandNum()
{
      //string comd = "rand -f";
      float x, y;
      FILE *fp = popen( "rand -f", "r");
      fscanf(fp,"%f",&x);
      x*=50;
      cout << "rand float:" << x <<endl;
      fclose(fp);
      int xx = trunc( x ); 
      if(0==xx)xx=1;
      if(xx>50)xx=50;
      return xx;

}
void genDataFile(string filen){
   // random generate rects: X,Y
   cout <<"max random=" << RAND_MAX <<endl;
   ofstream out_file;
   out_file.open( default_in);
   for(int i=0; i<num; i++) {
      //generate number:
      long int ranx; // =  random() % 50;
      long int rany; // =  random() % 50; cout << ranx<<","<<rany<<endl;
      ranx = genRandNum();
      sleep(1);
      rany = genRandNum();
      sleep(1);
      //cout << ranx<<","<<rany<<endl;
      cout << "RECT_CORXY:"<<ranx<<"  "<<rany<<endl;
      out_file<< ranx << " " << rany <<endl;
      long int tmp = ranx; 
      if(rany>ranx){
	      ranx=rany,rany=tmp;
      }
      RectXY xy(ranx, rany);
      in_rect.push_back(xy);
   }
   out_file.close();
   return ;
}
//main control process
int placeRects(vector<RectXY> input){
   int ret=0;
   //get sort input vector of Rect(x,y)
   vector<RectXY> svRect;
   //cout<<"input rects:"<<endl;
   vector<RectXY>::iterator i,j;
   for( i = input.begin(); input.end() != i; i++){
	   if( 0 == svRect.size() ) {
		   svRect.push_back(*i);
	   }
	   else {
   		for( j = svRect.begin(); svRect.end() != j; j++)
		    if( i->x > j->x ) break;
                if(svRect.end() == j ) svRect.push_back( *i );
                else svRect.insert(j, *i);

	   }
	   cout<<i->x<<" " <<i->y<<"\t";
   }
      //cout<<endl<<"begin sorting them:"<<endl;
   for(vector<RectXY>::iterator i = svRect.begin();
       svRect.end() != i;
       i++)  cout<<i->x<<" "<<i->y<<"\t";
   cout<<endl;
   // generate Rect class and init it:
   	//doLayout.init();
   Rect doLayout(svRect);
   // run placing of Rect:
   doLayout.doPlace();
   // computering and output result area, x, y and Trace the layout:
   ret = doLayout.getMinResult();

   return ret;
}

string help = " This is a program to computer minum area of 4 rects \n\
            usage: ./rectPlace   [ -f input.txt] [ -g] [ -n num]    \n\
            default parameter:  --file=packrec.in, --out=packrec.out\n\
            where: put rects (x,y) to input.txt                     \n";
bool readData(){
  //cout<<"read from file:" <<filen.c_str()<<endl;
  string line;
  ifstream infile(filen.c_str());
  if(infile.is_open()){
     int i=0;
     char str[128];
     while( i<num && infile.good() )
     {
	     getline(infile, line);
             strncpy(str, line.c_str(),128);
             int ranx=0, rany=0;
             sscanf( str, "%d %d", &ranx, &rany );
	     cout << "RECT_CORXY:"<<ranx<<"  "<<rany<<endl;
	     long int tmp = ranx; 
	     if(rany>ranx){
		     ranx=rany,rany=tmp;
	     }
	     RectXY xy(ranx, rany);
	     in_rect.push_back(xy);
           i++;
     }
  }else {
          cout<<"cannot open input file!,"<<endl;
          return -1;
  }
  return false;
}
int main(int argc, char* argv[]){
 //cout<<"hello world, this is an algorithm of placing rectangles"<<endl;
 #if 1
   bool bgen = false;
   bool bfile = false;
   bool notplace = false;
   char ch; 
   while ( -1 != (ch=getopt(argc, argv, "f:n:gt?h"))  )
   {
     switch(ch){
       case 'f':
         bfile = true;
         filen = string( optarg ); 
       break;
       case 'g':
         bgen = true;
       break;
       case 't':
         notplace = true;
       break;
       case 'n':
         num = atoi(optarg);
       break;
       case 'h':
       default:
        cout << help <<endl; 
        break;
    };

   }
    //cout << "input param:"<<"file="<<filen.c_str() <<"\tgenerate="<<bgen<<"\tnumOfRects="<<num<<endl;
    if(bgen){
      cout<<"----begin generate rects:"<<endl;
       genDataFile(filen);
      cout<<"----end generate rects:"<<endl;
       return 0;
    }
    else { //if( bfile){
	 readData();
         if(notplace) return 0;
    }
   //return 1;
 #endif 
 #if 1
    vector<RectXY>::iterator iter = in_rect.begin();
    //cout<<"input Rects, size="<<in_rect.size()<<endl;
    while (iter != in_rect.end()){
      cout<<"("<<iter->x<<","<<iter->y<<")\t";
      iter++;
    }
    cout<<endl;
    //return 0;
 #endif 
 //place rectangles:
 int ret = placeRects( in_rect );
 //if(ret) cout << "get minum rectangle:"<< ret <<endl;
 //else cout <<"oops: need more effort to refactor, don't give up:-)"<<endl;
 
return 0;
}

