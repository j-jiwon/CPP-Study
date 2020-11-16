#include "ZAllocator.h"
#include <new>
#include <Windows.h>
#include <iostream>
static HANDLE hHeap;

using namespace std;

ZAllocator::ZAllocator()
{
	hHeap = HeapCreate(0, 1<<15, 0);
}

ZAllocator::ZAllocator(size_t chunksPerBlocks)
	:mChunksPerBlock(chunksPerBlocks)
{
	alloc_ptr = reinterpret_cast<Chunk*>( operator new (chunksPerBlocks));
};

ZAllocator::~ZAllocator()
{
};

void* ZAllocator::Allocate(size_t size)
{
	if (size > mChunksPerBlock || alloc_ptr == nullptr)
		return operator new(size);

	if (alloc_ptr == nullptr)
	{
		alloc_ptr = allocateBlock(size);
	}

	Chunk* freeChunk = alloc_ptr;

	alloc_ptr = alloc_ptr->next;

	return freeChunk;
}

void ZAllocator::Deallocate(void* ptr)
{
	reinterpret_cast<Chunk *>(ptr)->next = alloc_ptr;
	alloc_ptr = reinterpret_cast<Chunk*>(ptr);
}

Chunk* ZAllocator::allocateBlock(size_t chunkSize)
{
	cout << mChunksPerBlock << "blocks" << endl;

	size_t blockSize = mChunksPerBlock * chunkSize;

	Chunk *blockBegin = reinterpret_cast<Chunk *>(malloc(blockSize));

	Chunk *chunk = blockBegin;

	if (chunk != nullptr)
	{
		for (int i = 0; i < mChunksPerBlock - 1; ++i)
		{
			chunk->next = reinterpret_cast<Chunk*>(reinterpret_cast<char *>(chunk) + chunkSize);
			chunk = chunk->next;
		}

		chunk->next = nullptr;
	}

	return blockBegin;
}

void *operator new(size_t size)
{
	return HeapAlloc(hHeap, 0, size);
}

void operator delete(void *ptr, size_t size)
{
	if (ptr != nullptr)
	{
		HeapFree(hHeap, 0, ptr);
	}
}