/*
ID:wang0101
PROG:friday
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main()
{
	ofstream fout("friday.out");
	ifstream fin("friday.in");
	int yearNum;
	fin >> yearNum;
	int firstDay = 0;
	int count[7] ;
	for (int w=0;w<7;w++) count[w] = 0;


	for(int i=0;i<yearNum;i++)
	{
		int curYear = 1900+i;
		int day13;
		for(int mon=1;mon<=12;mon++)
		{
			switch (mon)
			{
				case 1:
					day13 = firstDay + 12 ;
					count[day13%7]++;
					break;
				case 2:
				case 4:
				case 6:
				case 8:
				case 9:
				case 11:
					day13 += 31 ;
					count[day13%7]++;
					break;
				case 3:
					if ( curYear % 4 != 0 || 
							( (curYear % 100 ==0) && (curYear % 400 != 0) ) )
						day13 += 28 ;
					else
						day13 += 29 ;
					count[day13%7]++;
					break;
				case 5:
				case 7:
				case 10:
				case 12:
					day13 += 30 ;
					count[day13%7]++;
					firstDay = day13 + (32 - 13 ) ;
			}
		}
	}

	for(int y=0;y<7;y++)
	{
		if ( y != 6 )
			fout << count[ (y+6-1)%7 ] << " ";
		else
			fout << count[ (y+6-1)%7 ] << "\n" ;
	}
	return 0 ;
}
