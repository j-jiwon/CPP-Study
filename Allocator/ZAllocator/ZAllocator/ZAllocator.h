#pragma once
#include <Windows.h>

struct Chunk // individual objects
{
	// Header
	size_t size;
	Chunk* next;

};


class ZAllocator
{

public:
	ZAllocator();
	virtual ~ZAllocator() noexcept;

	static Chunk* Init(size_t chunkNum, size_t chunkSize);
	static void* Allocate(size_t size);
	static void Deallocate(void* chunk);

	static Chunk* start_ptr;

private:
	size_t _chunkNum;
	ZAllocator(const ZAllocator&);
};

void *operator new(size_t);
void operator delete(void*);
