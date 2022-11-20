#include <fstream>
#include <iostream>

using namespace std;

long long isPrime(long long n);
bool millerRabin(long long n, long long d, long long a);
long long fast_exp(long long base, long long exp, long long mod);

int main()
{
	ifstream fin("witness.in");
	ofstream fout("witness.out");

	if(!fin)
	{
		cout << "Bad witness.in" << endl;
		fin.close();
		fout.close();
		return -1;
	}

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
}

/*
Returns number of witnesses, prime numbers have none
*/
long long isPrime(long long n)
{
	if(n == 1) return 1; // false
	if(n <= 3) return 0; // true

	int d = n-1;
	while(d % 2 == 0)
		d /= 2;

	long long w = 0;
	
	for(int a = 2; a <= n-2; a++)
	{
		if(!millerRabin(n, d, a))
		{
			w++;
		}
	}
	
	return w;
}

/*
Returns false if n is composite, meaning a is a witness
*/
bool millerRabin(long long n, long long d, long long a)
{
	// x = a^d % n
	long long x = fast_exp(a, d, n);

	if(x == 1 || x == n-1)
		return true;
	
	while(d != n-1)
	{
		x = (x*x) % n;
		d *= 2;

		if(x == 1) return false;
		if(x == n-1) return true;
	}

	return false;
	
}

long long fast_exp(long long base, long long exp, long long mod)
{
	if(exp == 0)
		return 1;
	
	if(exp & 1) // if odd
		return (base * fast_exp(base, exp-1, mod)) % mod;
	
	long long a = fast_exp(base, exp/2, mod);
	return (a*a) % mod;
}