#include "ZAllocator.h"
#include <new>
#include <Windows.h>
#include <iostream>
using namespace std;

#define ALIGNMENT 8

class Heap 
{
public:
	Heap()
	{
		hHeap = HeapCreate(0, 1<<25, 0);
	}
	~Heap()
	{
		HeapDestroy(hHeap);
	}

	void* Alloc(size_t size)
	{
		return HeapAlloc(hHeap, 0, size);
	}

	static Heap* GetHeap()
	{
		static Heap newHeap;
		return &newHeap;
	}

private:
	HANDLE hHeap;
};

ZAllocator::ZAllocator()
{		
}

ZAllocator::~ZAllocator()
{
};

Chunk* ZAllocator::start_ptr = nullptr;

Chunk* ZAllocator::Init(size_t chunkNum, size_t chunkSize)
{
	chunkSize = (chunkSize + ALIGNMENT - 1) & ~ALIGNMENT; // power2 align
	Chunk* heapStart = (Chunk *)Heap::GetHeap()->Alloc((chunkSize + sizeof(Chunk)) * chunkNum);
	
	Chunk* chunk = heapStart;
	for (int i = 0; i < chunkNum; ++i)
	{
		chunk->next = reinterpret_cast<Chunk*>(chunk) + chunkSize;
		chunk = chunk->next;
	}
	chunk->next = nullptr;
	
	return chunk;
}

void* ZAllocator::Allocate(size_t size)
{
	if (start_ptr == nullptr)
	{
		start_ptr = (Chunk*)Heap::GetHeap()->Alloc(sizeof(Chunk));
		Init(8, size);
	}
	
	Chunk* freeChunk = (Chunk*)start_ptr;
	start_ptr = reinterpret_cast<Chunk*>(start_ptr)->next;

	return freeChunk;
}

void ZAllocator::Deallocate(void* chunk)
{
	reinterpret_cast<Chunk *>(chunk)->next = start_ptr;
	start_ptr = reinterpret_cast<Chunk*>(chunk);
}

void * operator new(size_t size)
{
	return ZAllocator::Allocate(size); nullptr;
}

void operator delete(void * ptr)
{
	if (ptr != nullptr)
	{
		ZAllocator::Deallocate(ptr);
	}
}
