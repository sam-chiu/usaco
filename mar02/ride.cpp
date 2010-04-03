/*
ID:wang0101
PROG:ride
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int getCharIndex( int x ) 
{
	return x - 'A' + 1 ;
}
int getValue( string x )
{
	int y = 1;
	for (int i = 0 ; i < x.length() ; i++)
	{
		y *= getCharIndex( (int)x[i] ) ;
	}
	return y%47 ;
}
int main()
{
	ofstream fout("ride.out");
	ifstream fin("ride.in");
	string a , b ;
	fin >> a;
	fin >> b;
	if ( getValue(a) == getValue(b) )
		fout << "GO" << endl;
	else
		fout << "STAY" << endl;
	//printf( "a is %s \n", a.c_str() ) ;
	//printf( "a val is %d \n", getValue( a ) ) ;
	//printf( "b is %s \n", b.c_str() ) ;
	//printf( "b val is %d \n", getValue( b ) ) ;
	return 0 ;
}
