#include <fstream>
#include <iostream>

using namespace std;

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
		// do stuff with n
		fin >> n;
	}
}