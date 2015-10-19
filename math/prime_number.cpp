/*
  by asas
*/
#include <bits/stdc++.h>
using namespace std ;

/*
 * get (1~MAX) all prime number
 */
template<int MAX>
class primeNumber
{
	public:
	int buf[ MAX + 1 ] = {} ;
	vector<int> prime ; // prime number array, ex: 2, 3, 5, 7....
	
	/*
	 * Initial this class and create the prime number array.
	 */
	primeNumber()
	{
		for ( int i = 2 ; i <= MAX ; i ++ )
		{
			if ( !buf[ i ] ) // is prime number
			{
				prime.push_back( i ) ;
				buf[ i ] = prime.size() ;
			}
			for ( int j = 0 ; j < buf[ i ] && i * prime[ j ] <= MAX ;  )
			{
				buf[ i * prime[ j ] ] = ++ j ; // 计穦砆计い程借计縵奔 
			}
		}
	}
	
	/*
	 * Return whether [number] is a prime number.
	 */
	bool isPrime( int number )
	{
		for ( int i = 0 ; i < prime.size() ; i ++ )
		{
			if ( prime[ i ] * prime[ i ] > number )
			{
				return true ;
			}
			if ( number % prime[ i ] == 0 )
			{
				return false ;
			}
		}
		return true ;
	}
	
	/*
	 * Returns a reference to the prime number at position pos in the prime 
	 * number array.
	 */
	const int operator []( const int &pos ) const
	{
		if ( pos >= prime.size() || pos < 0 )
		{
			return -1 ;
		}
		return prime[ pos ] ;
	}
	
	/*
	 * Return range of the number of prime numbers.
	 */
	const int size() const
	{
		return prime.size() ;
	}
} ;
int main()
{
	primeNumber<46341> p ;
	int n ;
	cout << "Have " << p.size() << " prime numbers." << endl ;
	cout << "The 5-th prime number is " << p[ 5 - 1 ] << endl ;
	while ( cin >> n )
	{
		if ( p.isPrime( n ) == true )
		{
			cout << n << " is prime number." << endl ;
		}
		else
		{
			cout << n << " isn't prime number." << endl ;
		}
	}
	return 0 ;
}

