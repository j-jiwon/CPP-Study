#pragma once
#include <Windows.h>

class ZAllocator
{
public:
	ZAllocator();
	ZAllocator(size_t size, void* start, size_t blockSize);
	virtual ~ZAllocator() noexcept;

	void* Allocate(size_t size);
	void Deallocate(void* ptr);

	void * operator new(size_t size);
	void operator delete(void *ptr);
	void SetHeap(HANDLE h);


private:
	struct ZBlock
	{
		ZBlock* prev_block = nullptr;
		ZBlock* next_block = nullptr;
	};

	typedef ZBlock* block_ptr;
	void* zallocator = nullptr;// whole pool address
	block_ptr freeBlock = nullptr;
	block_ptr allocBlock = nullptr;

	size_t blockSize;
	size_t blockNum;
	size_t memorySize = blockNum * (blockSize + sizeof(ZBlock));

};
