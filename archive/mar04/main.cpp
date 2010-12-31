/*
ID:wang0101
PROG:beads
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

using namespace std;
//class Temp;
//class Neckl;
//give a two char. return if equal
static bool isEqual(char a, char b)
{
	if ( a == 'w' || b == 'w' ) return true;
	if ( a == b ) return true ;
	return false;
}
class Temp
{
	char color;
	bool full;
	int length;
	int MAX;
	public:
	Temp(int m){ length = 0; color = 'w' ; full = false; MAX = m; }
	//return false if full
	bool eat( char x , int trace, bool traceOn = false )
	{
		if ( full ) return false;
		if ( color == 'w' ) 
		{
			if ( x == 'r' || x == 'b' ) 
			{
				color = x ;
			}
		}
		else
		{
			if ( ! isEqual( color , x ) )
			{
				full = true ;
				return false ;
			}
		}
		length++;

		if ( length >= MAX )
		{
			full = true ;
			return false;
		}

		return true;
	}
	//get length
	int getLength() { return length; }
};
class Neckl
{
	string neck;
	public:
	Neckl(string necklace)
	{
		neck = necklace ;
	}
	//give a pos. longest forward/backward. +1/-1
	int getLongest( int pos , int direct )
	{
		int curChar ;
		Temp arrow( neck.length() );
		assert( direct == 1 || direct == -1 );
		bool traceOn = false;
		if ( direct == -1 && pos == 22 )
			traceOn = true;
		while (true)
		{
			curChar = getChar(pos);
			if ( arrow.eat(curChar, pos , traceOn) )
			{
				pos+=direct;
			}
			else break;

		}
		return arrow.getLength();
	}
	//give a pos. longest backward
	//give a pos. give char
	char getChar( int pos )
	{
		int realPos = ( pos % (int)(neck.length()) );
		realPos += neck.length() ;
		realPos = realPos % (int)(neck.length());
		assert( realPos >= 0 );
		return neck[realPos];
	}
	//throw a char at this
};
int main()
{
	ofstream fout("beads.out");
	ifstream fin("beads.in");
	int N;
	fin >> N ;
	string necklace;
	fin >> necklace ;
	Neckl ne( necklace );

	int maxBeads = 0;
	int maxPoint = 0;
	for(int i=0;i<N ; i++ )
	{
		int beads;
		beads = ne.getLongest( i, 1 ) + ne.getLongest( i-1, -1 );
		if ( maxBeads < beads ) 
		{
			maxPoint = i ;
			maxBeads = beads;
		}
		if ( maxBeads >= N )
	 	{
		 	maxBeads = N;
			break; 
		}
	}
	//printf(" maxpoint fowards is at %d, with %d beads\n", maxPoint, ne.getLongest(maxPoint,1) );
	//printf(" maxpoint backwards is at %d, with %d beads\n", maxPoint, ne.getLongest(maxPoint-1,-1) );
	fout << maxBeads << endl;

	return 0 ;
}
