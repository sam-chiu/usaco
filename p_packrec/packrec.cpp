#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <iostream>
#include <fstream>

#include <string.h>
#include "math.h"
#include "unistd.h"

#include "Rect.h"

using namespace std;
#define default_in   "packrec.in"
#define default_out  "packrec.out"
#define default_num   4
int num = default_num;
string filen = string(default_in);
vector<RectXY>in_rect;

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
   cout<<"input rects:"<<endl;
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
      cout<<endl<<"begin sorting them:"<<endl;
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
  cout<<"read from file:" <<filen.c_str()<<endl;
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
 cout<<"hello world, this is an algorithm of placing rectangles"<<endl;
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
    cout << "input param:"<<"file="<<filen.c_str() <<"\tgenerate="<<bgen<<"\tnumOfRects="<<num<<endl;
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
    cout<<"input Rects, size="<<in_rect.size()<<endl;
    while (iter != in_rect.end()){
      cout<<"("<<iter->x<<","<<iter->y<<")\t";
      iter++;
    }
    cout<<endl;
    //return 0;
 #endif 
 //place rectangles:
 int ret = placeRects( in_rect );
 if(ret) cout << "get minum rectangle:"<< ret <<endl;
 else cout <<"oops: need more effort to refactor, don't give up:-)"<<endl;
 
return 0;
}
