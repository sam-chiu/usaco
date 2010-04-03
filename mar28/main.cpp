/*
ID:wang0101
PROG:namenum
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>


using namespace std;
string _sn;
char getNumberFromLetter( char c )
{
	switch ( c )
	{
		case 'A' :
		case 'B' :
		case 'C' :
			return '2';
		case 'D' :
		case 'E' :
		case 'F' :
			return '3';
		case 'G' :
		case 'H' :
		case 'I' :
			return '4';
		case 'J' :
		case 'K' :
		case 'L' :
			return '5';
		case 'M' :
		case 'N' :
		case 'O' :
			return '6';
		case 'P' :
		case 'R' :
		case 'S' :
			return '7';
		case 'T' :
		case 'U' :
		case 'V' :
			return '8';
		case 'W' :
		case 'X' :
		case 'Y' :
			return '9';
	}
	return 0;
}
bool isMatch( string sn, string letters )
{
	if ( sn.size() != letters.size() )
		return false;
	bool assume = true;
	for ( int i = 0; i < sn.size(); i++ )
	{
		if ( ! ( getNumberFromLetter( ( char )letters[i] ) == sn[i] ) )
			assume = false;
	}
	return assume;
}
bool matchSn( string name )
{
	return isMatch( _sn, name );
}
string getSnFromName( string name )
{
	string result = "";
	for ( int i = 0; i < name.size(); i++ )
	{
		result += getNumberFromLetter( (char) name[i] );
	}
	return result;
}
//weak compare
int compareStringBySn( string name1, string name2 )
{
	return ( getSnFromName( name1 ) <  getSnFromName( name2 ) );
}
void printDict( vector<string> & v, ostream & os )  
{
	vector<string>::iterator it;
	for ( it = v.begin(); it != v.end(); it++ )
	{
		//printf( "%s\n", (*it).c_str() );
		os << (*it) << endl;
	}
}
int main()
{
	ofstream fout("namenum.out");
	ifstream fin("namenum.in");
	ifstream din("dict.txt");
	vector<string> dict;
	vector<string> name_perm;
	string name;
	string sn;
	//debug

	while ( !din.eof() )
	{
		din >> name ;
		dict.push_back( name );
	}
	//sort by sn
	sort( dict.begin(), dict.end(), compareStringBySn );
	//printDict( dict );
	vector<string> result;
	while ( fin >> sn )
	{
		//fin >> sn ;
		//printf( "sn: %s \n", sn.c_str() );
		if ( sn == "\n" ) break;
		_sn = sn;
		vector<string>::iterator found;
		found = find_if( dict.begin(), dict.end(), matchSn );
		if ( found == dict.end() )
		{
			fout << "NONE" << endl;
			break;
		}
		while ( found != dict.end() )
		{
			//fout << (*found) << endl;
			result.push_back( *found );
			found++;
			if ( found == dict.end() || !matchSn( *found ) )
				break;
		}
	}
	sort( result.begin(), result.end() );
	printDict( result, fout );

	/*
	string test( "GREG" );
	if ( binary_search( dict.begin(), dict.end(), test ) )
		printf( "FOUND\n" );
	else
		printf( "NOT FOUND\n" );
		*/

	//binary search the dict
	return 0 ;
}
