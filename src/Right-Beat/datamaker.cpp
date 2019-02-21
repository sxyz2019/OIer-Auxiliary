#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <windows.h>
using namespace std;
// ofstream cout("data.in");

int rand_r(unsigned int *seed)
{
	unsigned int next = *seed;
	int result;
	next *= 1103515245;
	next += 12345;
	result = (unsigned int)(next / 65536) % 2048;
	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (unsigned int)(next / 65536) % 1024;
	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (unsigned int)(next / 65536) % 1024;
	*seed = next;
	return result;
}

int main()
{
	unsigned int seed = time(NULL);
	//  srand( (unsigned)time( NULL ) );
	// freopen("input.txt","w",stdout);
	int a, b;
	a = rand_r(&seed) % 100 + 1, b = rand_r(&seed) % 100 + 1;
	printf("%d %d\n", a, b);
	return 0;
}
