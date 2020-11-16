#pragma once
#include <Windows.h>

struct Chunk
{
	Chunk* prev;
	Chunk* next;
};

class ZAllocator
{

public:
	ZAllocator();
	ZAllocator(size_t chunksPerBlocks);
	virtual ~ZAllocator() noexcept;

	void* Allocate(size_t size);
	void Deallocate(void* ptr);

private:
	size_t mChunksPerBlock;
	Chunk* alloc_ptr = nullptr;
	Chunk* allocateBlock(size_t chunkSize);
};


void *operator new(size_t size);
void operator delete(void *ptr, size_t size);
