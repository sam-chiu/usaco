/*
ID:wang0101
PROG:crypt1
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
#include <algorithm>
struct case_t 
{
	int i;
	int j;
	int k;
	int a;
	int b;
};
case_t case_to_compare;  //for predicate only
std::vector<int> digits;
std::vector<case_t> cases;
// Tests case_t equal: predicate for find_if
bool IsCaseFoundExists(case_t a)
{
	return (( a.i == case_to_compare.i )
			&&  ( a.j == case_to_compare.j )
			&&  ( a.k == case_to_compare.k )
			&&  ( a.a == case_to_compare.a )
			&&  ( a.b == case_to_compare.b ));
}
// Generates a number given i, j, k
int GetNumber(int i, int j, int k)
{
	assert( digits.size() > 0 );
	int result = 0;
	result += 100 * digits[ i ];
	result += 10  * digits[ j ];
	result += 1   * digits[ k ];
	return result;
}
// Generates number for two digits
int GetNumber(int a, int b)
{
	assert( digits.size() > 0 );
	int result = 0;
	result += 10 * digits[ a ];
	result += 1  * digits[ b ];
	return result;
}
// Tests a digit is within set
bool IsInSet(int digit)
{
	for (int i = 0; i < digits.size(); i++) 
	{
		if (digit == digits[i]) 
		{
			return true;
		}
	}
	return false;
}
// Tests a three digit number, see if within set range
bool TestThreeDigitsOK(int num)
{
	if (num >= 100 && num <= 999) 
	{
		assert( digits.size() > 0 );
		int digit = 0;
		digit = num % 10;
		if (!IsInSet(digit)) 
			return false;
		digit = (num / 10) % 10;
		if (!IsInSet(digit)) 
			return false;
		digit = num / 100 ;
		if (!IsInSet(digit)) 
			return false;
		return true;
	}
	return false;
}
// Tests a four digit number, see if within set range
bool TestFourDigitsOK(int num)
{
	if (num >= 1000 && num <= 9999) 
	{
		assert( digits.size() > 0 );
		int digit = 0;
		digit = num % 10;
		if (!IsInSet(digit)) 
			return false;
		digit = (num / 10) % 10;
		if (!IsInSet(digit)) 
			return false;
		digit = (num / 100) % 10;
		if (!IsInSet(digit)) 
			return false;
		digit = num / 1000 ;
		if (!IsInSet(digit)) 
			return false;

		return true;
	}
	return false;
}
// Tests the numbers, see if conform to standards
bool NumberTestPass(int i, int j, int k, int a, int b)
{
	int first_number = GetNumber(i, j, k);
	int second_number = GetNumber(a, b);
	if (!TestThreeDigitsOK(first_number * digits[ b ])) 
		return false;
	if (!TestThreeDigitsOK(first_number * digits[ a ])) 
		return false;
	if (!TestFourDigitsOK(first_number * second_number)) 
		return false;
	return true;
}
int main(int argc, const char *argv[])
{
	case_to_compare.i = -1;
	case_to_compare.j = -1;
	case_to_compare.k = -1;
	case_to_compare.a = -1;
	case_to_compare.b = -1;
	digits.clear();
	cases.clear();
	std::ofstream fout("crypt1.out");
	std::ifstream fin("crypt1.in");
	int num_set = 0;
	fin >> num_set;
	//std::cout << num_set << std::endl;
	for (int i = 0; i < num_set; i++) 
	{
		int d = 0;
		fin >> d;
		digits.push_back(d);
	}
	//for (int i = 0; i < digits.size(); i++) 
	//{
		//printf("%d\n", digits[i]);
	//}
	

	//genreate *** times ** : all possibilty
	// i, j, k ( first_number  )
	//    a, b ( second_number ) 
	int success_case_count = 0;
	for (int i = 0; i < num_set; i++) 
	{
		for (int j = 0; j < num_set; j++) 
		{
			for (int k = 0; k < num_set; k++) 
			{
				for (int a = 0; a < num_set; a++) 
				{
					for (int b = 0; b < num_set; b++) 
					{
						if ( NumberTestPass(i, j, k, a, b) )
						{
							case_t this_case = { i, j, k, a, b };
							if (cases.size() == 0) 
							{
								cases.push_back(this_case);
								success_case_count++;
								//printf("i am here\n");
							}
							else 
							{
								case_to_compare.i = i;
								case_to_compare.j = j;
								case_to_compare.k = k;
								case_to_compare.a = a;
								case_to_compare.b = b;
								std::vector<case_t>::iterator it;
								it = find_if( cases.begin(), cases.end(), IsCaseFoundExists);
								if (it == cases.end()) 
								{
									//printf("i am there\n");
									//for (int c = 0; c < cases.size(); c++) 
									//{
										//printf("case %d :%d %d %d %d %d \n", c, cases[c].i, cases[c].j, cases[c].k, cases[c].a, cases[c].b);
									//}
									cases.push_back(this_case);
									success_case_count++;
								}
							}
						}
					}
				}
			}
		}
	}


	//printf("result: %d\n", success_case_count);
	fout << success_case_count << std::endl;
	
	return 0;
}
