// Adam Kraus
#include <fstream>
#include <iostream>

using namespace std;

bool isWitness(long long a, long long n);
long long isPrime(long long n);
bool millerRabin(long long n, long long d, long long a);
long long fast_exp(long long base, long long exp, long long mod);

int main()
{
	ifstream fin("witness.in");

	if(!fin)
	{
		cout << "Bad witness.in" << endl;
		fin.close();
		return -1;
	}

	ofstream fout("witness.out");

	if(!fout)
	{
		cout << "Bad witness.out" << endl;
		fin.close();
		fout.close();
		return -1;
	}

	long long int n;

	fin >> n;
	while (n > 2)
	{
		long long w = isPrime(n);
		if(w == 0)
			fout << n << " is prime" << endl;
		else
			fout << n << " " <<  (n-w-3) << endl;
		fin >> n;
	}

	fin.close();
	fout.close();
}

/*
Returns number of witnesses, prime numbers have none
*/
long long isPrime(long long n)
{
	if(n == 1) return 1; // false
	if(n <= 3) return 0; // true

	long long w = 0;
	
	for(int a = 2; a <= n-2; a++)
	{
		if(isWitness(a, n))
		{
			w++;
		}
	}
	
	return w;
}

/*
Returns true if a is a witness to n being composite
*/
bool isWitness(long long a, long long n)
{
	// need t, u such that u is odd, and 2^t * u = n-1
	long long u = n-1;
	long long t = 0;

	// while u still odd
	while(u % 2 == 0)
	{
		u /= 2;
		t += 1;
	}

	long long x = fast_exp(a, u, n);

	for(int i = 0; i < t; i++)
	{
		long long old_x = x;
		x = (x*x) % n;
		if(x == 1 && old_x != 1 && old_x != n-1)
			return true;
	}

	if(x != 1)
		return true;
	
	return false;
}

/*
Fast exponentiation algorithm
*/
long long fast_exp(long long base, long long exp, long long mod)
{
	if(exp == 0)
		return 1;
	
	if(exp & 1) // if odd
		return (base * fast_exp(base, exp-1, mod)) % mod;
	
	long long a = fast_exp(base, exp/2, mod);
	return (a*a) % mod;
}