#include "ZAllocator.h"
#include <new>
#include <Windows.h>
static HANDLE hHeap;

ZAllocator::ZAllocator()
{
	hHeap = HeapCreate(0, 1<<15, 0);
}

ZAllocator::ZAllocator(size_t size, void* start, size_t block_num)
	: blockNum(block_num), blockSize(size)
{
	zallocator = operator new(memorySize);

	if (zallocator != nullptr)
	{
		for (auto i = 0; i < blockNum; ++i)
		{
			block_ptr curr = reinterpret_cast<block_ptr>(static_cast<char*>(zallocator) + i * (blockSize + sizeof(ZBlock)));

			curr->prev_block = nullptr;
			curr->next_block = freeBlock;

			if (freeBlock != nullptr)
			{
				freeBlock->prev_block = curr;
			}
			freeBlock = curr;
		}
	}

};

ZAllocator::~ZAllocator()
{
	if (zallocator != nullptr)
		operator delete(zallocator);
};

void* ZAllocator::Allocate(size_t size)
{
	if (size > blockSize || freeBlock == nullptr || zallocator == nullptr)
		return operator new(size);

	block_ptr curr = freeBlock;
	freeBlock = curr->next_block;

	if (freeBlock != nullptr)
	{
		freeBlock->prev_block = nullptr;
	}

	curr->next_block = allocBlock;
	if (allocBlock != nullptr)
	{
		allocBlock->prev_block = curr;
	}
	allocBlock = curr;

	return static_cast<void *>(reinterpret_cast<char*>(curr) + sizeof(ZBlock));
}

void ZAllocator::Deallocate(void* ptr)
{
	if (zallocator < ptr && ptr < (void*)((char*)zallocator + memorySize))
	{
		block_ptr curr = reinterpret_cast<block_ptr>(static_cast<char*>(ptr) - sizeof(ZBlock));

		allocBlock = curr->next_block;
		if (allocBlock != nullptr)
		{
			allocBlock->prev_block = nullptr;
		}

		curr->next_block = freeBlock;
		if (freeBlock != nullptr)
		{
			freeBlock->prev_block = curr;
		}

		freeBlock = curr;

	}
	else 
		operator delete(ptr);
}


void* ZAllocator::operator new(size_t size)
{
	return HeapAlloc(hHeap, 0, size);
}

void ZAllocator::operator delete(void *ptr)
{
	if (ptr != nullptr)
	{
		HeapFree(hHeap, 0, ptr);
	}
}

void ZAllocator::SetHeap(HANDLE h)
{
	hHeap = h;
}
