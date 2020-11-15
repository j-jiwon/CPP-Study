#include "ZAllocator.h"
#include <iostream>
#include <thread>

using namespace std;

int main()
{
	size_t size = 100000;
	ZAllocator zallocator;

	for (int i = 0; i < size; ++i)
	{
		void * za = zallocator.Allocate(16);
		cout << i << endl;
		if( i% 2 == 0)
			zallocator.Deallocate(za);
	}
	
	return 0;
}