#include <fstream>
#include <iostream>

using namespace std;

const int ITERATIONS = 4;

bool isPrime(long long n, int k);
bool millerRabin(long long n, long long d);
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
	while (n != -1)
	{
		if(isPrime(n, ITERATIONS))
			cout << n << endl;
		fin >> n;
	}
}

bool isPrime(long long n, int k)
{
	if(n == 1) return false;
	if(n <= 3) return true;
	if(n % 2 == 0) return false;

	int d = n-1;
	while(d % 2 == 0)
		d /= 2;
	
	for(int i = 0; i < k; i++)
		if(!millerRabin(n, d))
			return false;
	
	return true;
}

bool millerRabin(long long n, long long d)
{
	// a random in range [2, n-2]
	long long a = 2 + rand() % (n-4);

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
	
	if(exp & 1)
		return (base * fast_exp(base, exp-1, mod)) % mod;
	
	long long a = fast_exp(base, exp/2, mod);
	return (a*a) % mod;
}