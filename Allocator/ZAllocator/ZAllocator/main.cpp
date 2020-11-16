#include "ZAllocator.h"
#include <iostream>
#include <thread>

using namespace std;

int main()
{
	ZAllocator zallocator;
	void * ptr = zallocator.Allocate(64);
	zallocator.Deallocate(ptr);

	return 0;
}