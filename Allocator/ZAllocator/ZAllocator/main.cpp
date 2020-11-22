#include "ZAllocator.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Test Code

struct Object
{
	uint32_t data[2];
	static ZAllocator allocator;
	static void* operator new(size_t size)
	{
		return allocator.Allocate(size);
	}
	static void operator delete(void *ptr)
	{
		return allocator.Deallocate(ptr);
	}
};

ZAllocator Object::allocator;

int main()
{
	// Test 1
	constexpr int arraySize = 10;
	Object *object[arraySize];
	cout << sizeof(Object) << endl;

	cout << "allocate " << arraySize << endl;

	for (int i = 0; i < arraySize; ++i)
	{
		object[i] = new Object();
		cout << i << " " << object[i] << endl;
	}

	cout << endl;

	for (int i = arraySize - 1; i >= 0; --i)
	{
		cout << i << " " << object[i] << endl;
		delete object[i];
	}

	cout << endl;

	object[0] = new Object();
	cout << "new [0] = " << object[0] << endl <<endl ; // reuisng!



	// Test 2

	ZAllocator zallocator;
	auto start = std::chrono::system_clock::now();

	for (int i = 0; i < 100000000; ++i)
	{
		auto ptr = zallocator.Allocate(32);
		zallocator.Deallocate(ptr);
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "finished computation at " << ctime(&end_time)
		<< "elapsed time: " << elapsed_seconds.count() << "s\n" << std::endl;

	/*
	
		8
		allocate 10
		0 038E05A8
		1 019200C0
		2 019204A0
		3 0199F4A0
		4 01A1E4A0
		5 01A9D4A0
		6 01B1C4A0
		7 01B9B4A0
		8 01C1A4A0
		9 01C994A0

		9 01C994A0
		8 01C1A4A0
		7 01B9B4A0
		6 01B1C4A0
		5 01A9D4A0
		4 01A1E4A0
		3 0199F4A0
		2 019204A0
		1 019200C0
		0 038E05A8

		new[0] = 038E05A8

		finished computation at Mon Nov 23 00:03 : 14 2020
		elapsed time : 4.09553s
	
	*/
}