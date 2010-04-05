/*
ID:wang0101
PROG:milk
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
typedef struct
{
	int price;
	int quantity;
} farmer;
bool comparePrice( farmer a, farmer b )
{
	return (a.price < b.price);
}
int main()
{
	ofstream fout("milk.out");
	ifstream fin("milk.in");
	int need;
	int numFarmers;
	fin >> need >> numFarmers;
	farmer f;
	vector<farmer> v;
	for( int i = 0; i < numFarmers; i++ )
	{
		fin >> f.price >> f.quantity;
		v.push_back( f );
	}
	sort(v.begin(), v.end(), comparePrice );
	int totalvalue = 0;
	for( int i = 0; (i < numFarmers) && ( need >= 0 ); i++ )
	{
		if ( need > v[i].quantity )
			totalvalue += v[i].price * v[i].quantity;
		else
			totalvalue += v[i].price * need;
		//printf( "v.price=%d, v.quantity=%d\n", v[i].price, v[i].quantity );
		need -= v[i].quantity; 
	}
	//printf( "total is %d\n", totalvalue );
	fout << totalvalue << endl;
	return 0 ;
}
