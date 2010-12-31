/*
ID:wang0101
PROG:barn1
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
typedef struct rangeCows
{
	int start;
	int end;
	void addcow( int x )
	{
		if ( x == start - 1)
			start = x;
		if ( x == end + 1 )
			end = x;
	}
} rangeCows;
typedef struct gap
{
	int start;
	int end;
	int gapLength()
	{
		return ( end - start + 1 );
	}
} gap;
vector<rangeCows> layout;
vector<gap> gaps;
int _cow;
bool comparerangeCows( rangeCows x )
{
	return ( ( _cow == x.start - 1 )
		|| ( _cow == x.end + 1 ) ) ;
}
bool strictComparerangeCows( rangeCows a, rangeCows b )
{
	if ( a.end < b.start ) return true;
	if ( a.start > b.end) return false;
	return false;
}
bool strictCompareGaps( gap a, gap b )
{
	return ( a.gapLength() < b.gapLength() );
}
void cleanLayout()
{
	sort ( layout.begin(), layout.end(), strictComparerangeCows );
	for (int i = 0; i < layout.size(); i++ )
	{
		if ( i == layout.size() - 1 ) break;
		if ( layout[i].end == layout[i+1].start - 1 )
		{
			//do merge. merge to lower
			layout[i].end = layout[i+1].end;
			layout.erase( layout.begin() + i+1 );
		}
	}
}
void constructGap()
{
	//assume already sorted
	for( int i =0; i < layout.size(); i++ )
	{
		if ( i == layout.size() -1 ) break;
		gap g;
		g.start = layout[i].end + 1;
		g.end = layout[i+1].start - 1;
		gaps.push_back( g );
	}
}
void addtoLayout( int cow )
{
	vector<rangeCows>::iterator it;
	_cow = cow;
	it = find_if( layout.begin(), layout.end(), comparerangeCows );
	if ( it != layout.end() )
	{
		it->addcow( cow );
	}
	else
	{
		rangeCows newcow;
		newcow.start = cow;
		newcow.end = cow;
		layout.push_back( newcow );
	}
}

int main()
{
	ofstream fout("barn1.out");
	ifstream fin("barn1.in");
	int maxBoards;
	int numStores;
	int numCows;
	fin >> maxBoards >> numStores >> numCows;
	//iterate
	int cowcode = 0;
	for( int i = 0; i < numCows; i++ )
	{
		fin >> cowcode;
		addtoLayout( cowcode );
	}
	cleanLayout();
	
	/*
	for ( int i = 0; i < layout.size(); i++ )
	{
		printf( "rangeCows: [ %d , %d ] \n", layout[i].start, layout[i].end );
	}
	*/
	
	constructGap();
	//sort gap
	sort( gaps.begin(), gaps.end(), strictCompareGaps ); 
	/*
	for ( int i = 0; i < gaps.size(); i++ )
	{
		printf( "range gaps: [ %d , %d ], length is [ %d ] \n", gaps[i].start, gaps[i].end, gaps[i].gapLength() );
	}
	*/
	int maxBlock = layout[layout.size() -1].end - layout[0].start + 1;

	int sumToRemove = 0;
	int count = 0;
	for ( int i = gaps.size() -1 ; i >= 0; i-- )
	{
		if ( maxBoards == 1 ) break;
		count ++;
		sumToRemove += gaps[i].gapLength() ;
		if ( count == maxBoards - 1) break; 
	}

	int answer = maxBlock - sumToRemove ;
	//printf( " answer is %d\n", answer );
	fout << answer << endl;
	

	return 0 ;
}
