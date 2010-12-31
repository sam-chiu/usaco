/*
ID:wang0101
PROG:calfflac
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

bool IsLetter(const char& c)
{
	if (c >= 'A' && c <= 'Z') 
	{
		return true;
	}
	if (c >= 'a' && c <= 'z') 
	{
		return true;
	}
	return false;
}
bool IsEqual(const char& a, const char& b)
{
	return ( tolower(a) == tolower(b) );
}
int main(int argc, char** argv)
{
	//ifstream fin("calfflac.in");
	std::ofstream fout("calfflac.out");
	std::vector<char> v;
	if (FILE *fp = fopen("calfflac.in", "r")) 
	{
		char buf[20000];
		while (int len = fread(buf, 1, sizeof(buf), fp))
			v.insert(v.end(), buf, buf + len);
		fclose(fp);
	}


	int max_extend      = 0;
	int max_left        = 0;
	int max_right       = 0;
	int max_full_length = 0;
	for (int i = 0; i < v.size(); i++) 
	{
		if (i == 0 || i == v.size() - 1) 
			continue;
		// Be center, or center left, or center right.
		int left_bound   = i;
		int right_bound  = i;
		int left_extend  = i;
		int right_extend = i;
		// Get left first char
		//bool done = false;
		int equal_count = 0;
		// Test for center case like: abcba ( c is current index )
		while ( true )
		{
			while (--left_bound >= 0)
			{
				if ( IsLetter(v[left_bound]) ) 
				{
					break;
				}
				else 
					continue;
			}
			if ( left_bound < 0 ) 
			{
				//done = true;  // No more letters on left.
				break;
			}
			while (++right_bound < v.size())
			{
				if ( IsLetter(v[right_bound]) ) 
					break;
				else 
					continue;
			}
			if ( right_bound == v.size() ) 
			{
				//done = true;  // No more letters on right.
				break;
			}

			if (IsEqual(v[left_bound],v[right_bound])) 
			{
				//printf("%c-%c\n", v[left_bound], v[right_bound]);
				left_extend = left_bound;
				right_extend = right_bound;
				equal_count++;
				continue;
			}
			else 
			{
				break;
			}
		}
		if (equal_count > max_extend) 
		{
			max_extend = equal_count ;
			max_full_length = 2 * max_extend + 1;
			max_left = left_extend;
			max_right = right_extend;
		}
		// Test for even case like: abba ( first b is current index )
		left_bound   = i+1;  // So start from current index
		right_bound  = i;
		left_extend  = i;
		right_extend = i;
		equal_count  = 0;
		while ( true )
		{
			while (--left_bound >= 0)
			{
				if ( IsLetter(v[left_bound]) ) 
				{
					break;
				}
				else 
					continue;
			}
			if ( left_bound < 0 ) 
			{
				//done = true;  // No more letters on left.
				break;
			}
			while (++right_bound < v.size())
			{
				if ( IsLetter(v[right_bound]) ) 
					break;
				else 
					continue;
			}
			if ( right_bound == v.size() ) 
			{
				//done = true;  // No more letters on right.
				break;
			}

			if (IsEqual(v[left_bound],v[right_bound])) 
			{
				//printf("%c-%c\n", v[left_bound], v[right_bound]);
				left_extend = left_bound;
				right_extend = right_bound;
				equal_count++;
				continue;
			}
			else 
			{
				break;
			}
		}
		//printf("current i is: %d, current char is [%c]\n",i, v[i]);
		//printf("equal_count is : %d\n", equal_count);
		if (equal_count > max_extend) 
		{
			max_extend = equal_count;
			max_full_length = 2 * max_extend;
			max_left = left_extend;
			max_right = right_extend;
		}
		//printf("Got range: from %d to %d\n", left_bound, right_bound);
		//for (int j = left_bound; j <= right_bound; j++) 
		//{
			//printf("%c", v[j]);
			//printf("\n");
		//}
	}

	//std::cout << v.size() << std::endl;
	//std::cout << "max left:" << max_left << " ,max right:" << max_right << std::endl;
	//std::cout << ( 2 * max_extend + 1) << std::endl;
	fout << max_full_length << std::endl;
	for (int i = max_left; i <= max_right; i++) 
	{
		//printf("%c", v[i]);
		fout << v[i];
	}
	//printf("\n");
	fout << std::endl;
	return 0;
}
