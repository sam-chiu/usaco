/*
ID:wang0101
PROG:calfflac
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
static int numChars;
static ifstream fin;
bool isGoodChar( char c )
{
	if ( ( c >= 'a') && ( c <= 'z') ) return true;
	if ( ( c >= 'A') && ( c <= 'Z') ) return true;
	return false;
}
int checkNextEqual()
{
	int curIndex = fin.tellg();
	cout << "curIndex is " << curIndex << endl;
	int leftRelativePos = 0;
	int rightRelativePos = 0;
	int leftExtend = 0;
	int rightExtend = 0;
	int matched = 0;
	char left, right;
	while (  ( curIndex - leftRelativePos >=0  )
		&& (curIndex + rightRelativePos <= numChars ) ) 
	{
		while ( curIndex + leftRelativePos >=0  ) 
		{
			if ( curIndex + leftRelativePos == 0 )
			{
				//need to think more
				cout << "reach left most" << endl;
			}
			fin.seekg( leftRelativePos-- , ios::cur );
			cout << "in left cur pos is " << fin.tellg() << endl;
			left = fin.peek();
			cout << "left char is now " << left << endl;
			if ( !isGoodChar( left ) )
			{
				cout << "left char is not good char" << endl;
				continue;
			}
			else 
			{
				cout << "left char is good char" << endl;
				leftExtend = curIndex + leftRelativePos;
				cout << "left extend is now: " << leftExtend << endl;
				//reset cur
				fin.seekg( -leftRelativePos, ios::cur ); 
				cout << "left seek reset to: " << fin.tellg() << endl;
				break; //left is found
			}
		}

		while ( curIndex + rightRelativePos <= numChars ) 
		{
			if ( curIndex + rightRelativePos == numChars )
			{
				//need to think boundary case 
			}
			fin.seekg( rightRelativePos++, ios::cur );
			right = fin.peek();
			if ( !isGoodChar( right ) )
				continue;
			else
			{
				rightExtend = curIndex + rightRelativePos ;
				//reset cur
				fin.seekg( -rightRelativePos, ios::cur );
				break;
			}
		}
		
		if ( left == right )
		{
			matched += 2;
			//TODO call again
		}
		else
		{
			//end of story
			return matched;
		}
	}
	return matched;
}

void checkOdd(int kernelPos, ifstream& fin )
{

}
int main()
{
	ofstream fout("calfflac.out");
	fin.open("calfflac.in");
	numChars = fin.rdbuf()->in_avail();
	cout << numChars << endl;
	int maxWord = 0;
	for ( int i = 0; i < numChars ; i++ )
	{
		//two case. aba. or baab
		int tmp = checkNextEqual();
		if ( tmp > maxWord )
			maxWord = tmp ;
		char x = fin.peek();
		fin.seekg( 1, ios::cur );
		//cout << i << " pos is : " <<  x << endl;
	}
	cout << " max is " << maxWord << endl;
	return 0 ;
}
