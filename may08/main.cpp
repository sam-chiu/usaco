/*
ID:wang0101
PROG:palsquare
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
string intToBaseString( int d )
{
	char result[2];
	if ( d < 10 )
		sprintf( result, "%d", d );
	else 
		result[0] = 'A' + d - 10 ;
	result[1] = '\0';
	return result;
}
string getBaseString( int base, int decimal )
{
	string result = "";
	int remainder;
	int quotient;

	while ( decimal != 0 )
	{
		remainder = decimal % base ;
		quotient  = decimal / base ;
		result = intToBaseString( remainder ) + result;
		decimal = quotient;
	}
	return result;
}
bool isPalindrome( string number )
{
	const char * p_number = number.data();
	vector<char> vc;
	vc.assign( p_number, p_number + number.size() );

	vector<char> r_vc = vc;
	reverse( r_vc.begin(), r_vc.end() );
	string r_number;
	r_number.assign( r_vc.begin(), r_vc.end() );
	
	/*
	vector<char>::iterator it = r_vc.begin();
	for ( ; it != r_vc.end(); it++ )
	{
		printf( "char = %c\n", *it );
	}
	*/
	//printf( "r_number=%s\n", r_number.c_str() );

	return ( number == r_number );
}
int main()
{
	ofstream fout("palsquare.out");
	ifstream fin("palsquare.in");
	int base;
	fin >> base;
	string x = getBaseString( 16, 15 );
//	printf ( "x = %s\n", x.c_str() );
for( int i = 1; i <= 300 ; i++ )
{
	if ( isPalindrome( getBaseString( base, i*i ) ) )
	{
		fout << getBaseString( base, i ) << " " << getBaseString( base, i*i ) << endl;
	}
}

	return 0 ;
}
