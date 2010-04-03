/*
ID:wang0101
PROG:milk2
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <pair>

using namespace std;
//rewrite for performance. do not use complex class
//keep target simple and effective get the right answer.
typedef vector< pair<int,int> > vec;
typedef pair<int,int> range;
void insert( vec & v,  range x );
int main(int argc ,char** argv ) 
{
	ifstream fin("milk2.in");
	ofstream fout("milk2.out");

	int n;
	fin >> n ;
	//printf( "n %d\n", n );


	vec v ;
	range x ;
	int a,b ;
	for( int i = 0 ; i < n ; i++ )
	{
		fin >> a >> b ;
		x.first = a;
		x.second = b;
		insert( v, x );
	}
	int busy_max  = 0 ;
	int idle_max = 0 ;
	int last_first = 0;
	int last_second = v[0].first ;
	int busy = 0;
	int idle = 0;
	for (vec::iterator it = v.begin() ; it != v.end() ; it++ )
	{
		busy = it->second - it->first ;
		idle = it->first - last_second ;
		if ( busy > busy_max ) busy_max = busy ;
		if ( idle > idle_max ) idle_max = idle ;
		last_second = it->second;
		//printf( "[%d,%d] \n", it->first, it->second );
	}
	fout << busy_max << " " << idle_max << std::endl;
	return 0 ;
}
void insert( vec & v,  range x )
{
	//write a sequential insert
	if ( v.empty() ) 
	{
		v.push_back(x);
		return ;
	}
	for ( int i = 0 ; i < v.size() ; i++ )
	{
		if ( x.first > v[i].second )
		{
			if ( i != ( v.size() - 1 ) )
				continue;
			else 
			{
				v.push_back( x );
				return;
			}
		}
		else if ( x.first < v[i].first )
		{
			if ( x.second < v[i].first )
			{
				v.insert(v.begin()+i, x);
				return;
			}
			else
			{
				if ( x.second <= v[i].second )
				{
					//merge
					x.second = v[i].second;
					v.erase( v.begin()+i );
					v.insert( v.begin()+i , x );
					return;
				}
				if ( i == ( v.size() - 1))
				{
					v.erase( v.begin() + i );
					v.push_back( x );
					return;
				}
				//get the end
				for ( int j = i+1 ; j < v.size() ; j++ )
				{
					if ( x.second > v[j].second ) 
					{
						if ( j != (v.size() -1) )
							continue;
						else
						{
							v.erase( v.begin()+ i , v.end() );
							v.push_back( x );
							return;
						}
					}
					else if ( x.second < v[j].first )
					{
						v.erase( v.begin()+i , v.begin()+j );
						v.insert( v.begin()+i , x );
						return;
					}
					else
					{
						x.second = v[j].second ;
						v.erase( v.begin()+i, v.begin()+j+1 );
						v.insert( v.begin()+i, x );
						return;
					}
				}
			}
		}
		else
		{
			if ( x.second <= v[i].second )
			{
				return;
				//merged. nothing.
			}
			else
			{
				if ( i == ( v.size() - 1 ) )
				{
					x.first = v[i].first ;
					v.erase( v.begin() + i );
					v.push_back( x ) ;
					return;
				}
				//check if no more j
				for ( int j = i+1; j < v.size() ; j++ )
				{
					if ( x.second > v[j].second )
					{
						if ( j != (v.size() - 1) )
							continue;
						else
						{
							x.first = v[i].first ;
							v.erase( v.begin()+i , v.end() );
							v.push_back( x );
							return;
						}
					}
					else if ( x.second < v[j].first )
					{
						x.first = v[i].first ;
						v.erase( v.begin()+i , v.begin()+j);
						v.insert( v.begin()+i, x );
						return;
					}
					else
					{
						x.first = v[i].first ;
						x.second = v[j].second;
						v.erase( v.begin()+i , v.begin()+j+1 );
						v.insert( v.begin()+i , x );
						return;
					}
				}
			}
		}

	}
}
