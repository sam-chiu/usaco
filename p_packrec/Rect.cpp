#include "Rect.h"
      //bool first=true;
      int op_step=0;
   //private:
   //   vector<RectXY> rects;
   //   vector<ResultRect> results;
      Rect::Rect(vector<RectXY>& input)
      {
	 cout<<"TRACE: constructor Rect"<<endl;
         rects = input;
         init();
      }
      int Rect::doPlace() { 
	 cout<<"TRACE: Rect::doPlace"<<endl;
         for(vector<RectXY>::iterator xy = rects.begin(); xy != rects.end(); xy++)
	 {
            updateResults(*xy);
         }
         return 0; 
      }
      int Rect::sort() { 
	 cout<<"TRACE: Rect::sort"<<endl;
         return 0; 
      }
      int Rect::getMinResult() { 
	 cout<<"TRACE: Rect::getMinResult"<<endl;
         cout<<"\t"<<"step="<<op_step<<"  size-result="<< results.size()<<endl;
         int area = 50*4*50;
         vector<ResultRect>*res = &result_vector.at(op_step);
         for(int i=0; i<result_vector.at(op_step).size();i++){
           int square = res->at(i).area.x1 * res->at(i).area.y1;
           cout<<"MAX step="<<op_step<<"\t i="<<i<<"\t square="<<square<<endl;
           if( area > square ) area = square; 
         }
         cout<<"PACK_RECT_RESULT:"<<area<<endl;
         for(vector<ResultRect>::iterator ri = res->begin(); ri != res->end(); ri++){
            if(ri->area.x1 * ri->area.y1 > area) continue;
            if( ri->area.x1 < ri->area.y1 ) cout<< "PACK_RECT_XY:"<<ri->area.x1<<" "<<ri->area.y1<<endl;
            else cout<< "PACK_RECT_XY:"<<ri->area.y1<<" "<<ri->area.x1<<endl;
         } 
         return area; 
      }
      int Rect::init() { 
	 cout<<"TRACE: Rect::init"<<endl;
         ResultRect i;
         RectCorxy  p;
         vector<ResultRect> step_vector;
         //result_vector.push_back(step_vector);
         //init (0,0,0,0) & (0,0,-1,-1) for iterator handler:
         i.area.x0 = i.area.y0 = i.area.x1 = i.area.y1 = 0;
         p.x0 = p.y0 = 0, p.x1 = p.y1 = -1;
         i.places.push_back(p);
         i.setStep(0);
         // init results vector:
         //step_vector.push_back(i);
         result_vector.push_back(step_vector);
         result_vector.at(0).push_back(i);
         return 0; 
      }
      int Rect::genNewResults( ResultRect* resulti, RectCorxy* place ,RectXY& rect ){
      //int Rect::genNewResults(std::list<ResultRect>::reverse_iterator& resulti, RectCorxy* place, RectXY& rect ) {
         cout << "TRACE: Rect::genNewResults"<<endl;
	 ResultRect  nextstepR ; 
	 int nx = place->x0 + rect.x;
	 int ny = place->y0 + rect.y;
         cout<<"debug:place=("<<place->x0<<" "<<place->y0<<" "<<place->x1<<" "<<place->y1<<" )"
             <<"\trect=("<<rect.x<<","<<rect.y<<")\tnow-square::  "<<
             resulti->area.x0<<","<<resulti->area.y0<<","<<resulti->area.x1<<","<<resulti->area.y1<<endl;
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
         cout << "\t\tresult area :(" << nextstepR.area.x0<<","<<nextstepR.area.y0 
              << ","<<nextstepR.area.x1<<","<<nextstepR.area.y1<<")" 
              << "\t area="<< nextstepR.area.x1*nextstepR.area.y1 <<endl;
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
		 //if( place->x0 >0 && ( rect.y1 > place.y0 && ( place.y1 == -1 || place.y1 > rect.y1)) )
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
           //nextstepR.step = step; 
           cout << "\t\t\tnext step="<<op_step + 1 <<endl;
           nextstepR.setStep( op_step + 1 ); 
           //cout<<"-----b results size="<<results.size()<<endl;
           result_vector.at(op_step+1).push_back(nextstepR);
           //cout<<"-----e results size="<<results.size()<<endl;

         return 0;
      }
      
      int Rect::updateResults(RectXY rect)
      {
         cout << "TRACE: Rect::updateResults"<<endl;
         cout << "STEP= "<<op_step<<"\trect="<<rect.x<<","<<rect.y<<"\t::size-stack="<<results.size() <<endl;
         RectXY rectyx;
         rectyx.x = rect.y, rectyx.y = rect.x;
         //results = result_vector.at(op_step);
         //vector<ResultRect>::reverse_iterator resulti;
         int i,j, num = result_vector.at(op_step).size();
         vector<ResultRect> step_vector;
         result_vector.push_back(step_vector);
         int pn ;
         //list<ResultRect>::reverse_iterator resulti;
         RectCorxy  place;
         ResultRect *resulti;
         //list<ResultRect>::iterator tmprm=results.end();
	// for( resulti = results.rbegin(); resulti != results.rend(); resulti++ ){
	 for(  i = num - 1 ; i >=0; i-- ){
             //add new results:
             resulti = &result_vector.at(op_step).at(i);
             cout<<"loop:::top-step= "<<op_step<<"\tresult-step= "<< resulti->getStep() <<"\t::size-stack="<<result_vector.at(op_step).size() <<endl;
             if(resulti->getStep() < op_step) 
                   break;
              pn = resulti->places.size();
             //for( vector<RectCorxy>::iterator place = resulti->places.begin();
	     //	     place != resulti->places.end() ;  place ++ ){
             for( j = 0; j < pn ;  j++){
                     cout<<"__________debug::pn="<<pn<<" j="<<j<<endl;
                     //place = resulti->places.at(j);
                     RectCorxy putit = resulti->places.at(j);
                  /*   putit.x0 = place.x0; 
                     putit.y0 = place.y0; 
                     putit.x1 = place.x1;
                     putit.y1 = place.y1;
                  */
                     cout<<"____1______debug::putit="<<putit.x0<<","<<putit.y0<<"," <<putit.x1<<","<<putit.y1<<endl;
		     genNewResults( resulti, &putit, rect );
		     if(op_step>0) {
                     cout<<"____2______debug::putit="<<putit.x0<<","<<putit.y0<<"," <<putit.x1<<","<<putit.y1<<endl;
		        genNewResults( resulti, &putit, rectyx );
		     }
	     }
         }
         op_step++;
         return 0; 
      }

