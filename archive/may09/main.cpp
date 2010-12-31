/*
ID:wang0101
PROG:dualpal
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
bool isPalDualable( int number )
{
	int threshold = 2;
	int count = 0;
	for( int i = 2; i <= 10; i++ )
	{
		if ( isPalindrome( getBaseString( i, number ) ) )
				count++;
		if ( count >= threshold ) 
			return true;
	}
	return false;
}
int main()
{
	ofstream fout("dualpal.out");
	ifstream fin("dualpal.in");
	int N;
	int S;
	fin >> N >> S;
	int i = 0;
	for(int j = S+ 1; i < N;j++)
	{
		if ( isPalDualable( j ) )
		{
			fout << j << endl;
			i++;
		}
	}
	return 0 ;
}
