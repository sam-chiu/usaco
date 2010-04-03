/*
ID:wang0101
PROG:gift1
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void init(int x[], int n )
{
	for (int i=0;i<n;i++) {x[i]=0;}
}
void setMoney( string name, int amount, 
		int num  , int max, string names[],
		int income[], int cost[],string recv[]) 
{
	if (num==0) return;
	if (amount==0) return;
	for (int i = 0 ;i < max ; i++ )
	{
		if ( names[i] == name )
			cost[i] += amount/num * num ;
		for ( int j=0;j<num;j++)
			if(recv[j] == names[i] )
				income[i] += amount/num ;
	}
}
int main()
{
	ofstream fout("gift1.out");
	ifstream fin("gift1.in");
	int n ;
	int line = 0;
	fin >> n ;
	line++;
	string names[n];
	for (int i = 0 ; i < n ; i++ )
	{
		fin >> names[i] ;
		line++;
	}
	int income[n];
	int cost[n];
	init(income, n);
	init(cost, n);
	int amount ;
	int num;
	while( !fin.eof() )
	{
		string name;
		fin >> name;
		if (name.empty()) break;
		line++;
		fin >> amount >> num ;
		line++;
		string recv[num];
		for (int i=0;i<num;i++) {fin >> recv[i] ;line++;}
		setMoney(name,amount,num,n,names,income,cost,recv);
	}

	for(int k=0;k<n;k++)
	{
		fout << names[k] << " " << (income[k]-cost[k]) << endl ;
	}

	return 0 ;
}
