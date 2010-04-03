/*
ID:wang0101
PROG:transform
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct pix
{
	int r;
	int c;
};
enum TRANSFORM
{
	NOCHANGE, CLOCK90, CLOCK180, CLOCK270,
	FLIP, FLIP90, FLIP180, FLIP270
};
TRANSFORM intToEnum( int i )
{
	switch ( i )
	{
		case 0 : return CLOCK90 ;
	  case 1 : return CLOCK180;
		case 2 : return CLOCK270 ;
	  case 3 : return FLIP ;
	  case 4 : return FLIP90 ;
		case 5 : return FLIP180 ;
		case 6 : return FLIP270 ;
		case 7 : return NOCHANGE ;
		default:
						 return NOCHANGE;
				//printf ( "illegel enum\n" );
	}
}
pix make_pix( int r, int c )
{
	pix ret;
	ret.r = r;
	ret.c = c;
	return ret;
}
pix convertRC( pix in, TRANSFORM t, int n);
class Image
{
	bool* tip;
	int size ;
	public:
	Image( int n )
	{
		tip = new bool[n*n];
		size = n ;
	}
	~Image()
	{
		delete tip ;
	}
	void setPixValue( int r, int c, bool val )
	{
		tip[ r + size * c] =  val;
	}
	bool getPixValue( pix p ) 
	{
		return tip[ p.r + size * p.c] ;
	}
	bool getPixValue( int r, int c )
	{
		return tip[ r + size * c ] ;
	}
	bool cmp( Image & target, TRANSFORM t )
	{
		pix targetPix;
		for ( int i = 0; i < size; i++ )
		{
			for ( int j = 0 ; j < size ; j++ )
			{
				targetPix = convertRC( make_pix( i, j ), t , size );
				if ( tip[i + j * size ] != target.getPixValue( targetPix ) )
					return false;
			}
		}
		return true;
	}
};
pix convertRC( pix in, TRANSFORM t, int n)
{
	pix ret;
	pix temp;
	switch ( t )
	{
		case NOCHANGE:
			return in ;
		case CLOCK90:
			ret.r = in.c ;
			ret.c = n - 1 - in.r ; 
			return ret;
	  case CLOCK180:
			ret.r = n - 1 - in.r ;
			ret.c = n - 1 - in.c ;
			return ret;
		case CLOCK270:
			ret.r = n - 1 - in.c ;
			ret.c = in.r ;
			return ret;
		case FLIP:
			ret.r = in.r ;
			ret.c = n - 1 - in.c ;
			return ret;
		case FLIP90:
			temp = convertRC( in , FLIP , n );
			return convertRC( temp, CLOCK90, n );
		case FLIP180:
			temp = convertRC( in, FLIP, n );
			return convertRC( temp, CLOCK180, n );
		case FLIP270:
			temp = convertRC( in, FLIP, n );
			return convertRC( temp, CLOCK270, n );
		default:
			printf( " unregonized transform enum\n" );
	}
	return in ; 
}

int main()
{
	ofstream fout("transform.out");
	ifstream fin("transform.in");

	int n ;
	fin >> n ;
	//printf ( "n : %d \n" , n );
	
	string line;
	Image image1(n);
	int image1_true_count = 0;
	for( int i = 0; i < n ; i++ )
	{
		fin >> line ;
		for ( int j = 0 ; j < n ; j++ )
		{
			image1.setPixValue( i, j ,( (line[j] == '@' ) ? true : false ) ) ;
			if ( image1.getPixValue( i, j ) ) image1_true_count++;
		}
	}
	Image image2( n );
	int image2_true_count = 0;
	for( int i = 0; i < n ; i++ )
	{
		fin >> line ;
		for ( int j = 0 ; j < n ; j++ )
		{
			image2.setPixValue( i, j ,  ( ( line[j] == '@' ) ? true : false ) );
			if ( image2.getPixValue( i, j ) ) image2_true_count++;
		}
	}
	//
	if ( image1_true_count != image2_true_count )
	{
		//printf( "not possible" );
		fout << 7 << endl;
		return 0;
	}
	//printout
#if 0
	for ( int i = 0 ; i < n ; i++ )
	{
		for ( int j = 0 ; j < n ; j++ )
			printf( "%d " , image1.getPixValue( i, j ) );
		printf( " \n" );
	}
#endif
	//
	int i ;
	for ( i = 0 ; i < 8 ; i++ )
	{
		if ( image1.cmp( image2, intToEnum( i ) ) ) 
			break;
	}
	if ( i < 8 )
	{
		//printf( " success match at case %d\n", i );
		if ( i < 4 )
			fout << ( i + 1 ) << endl;
		else if ( i < 7 )
			fout << 5 << endl;
		else 
			fout << 6 << endl;
	}
	else if ( i == 8 )
	{
		fout << 7 << endl;
	//	printf ( "didn't match anything\n" );
	}


	//printf ( "line : %s \n", line.c_str() );
	return 0 ;
}
