#include "stdafx.h"
#include <iostream>
#include <cstddef>
#include "ZString.h"
using namespace std;

ZSTRING_API ZString::ZString()
	: ptr(nullptr)
{}

ZSTRING_API ZString::ZString(const char* c)
	: ZString()
{
	Append(c);
}

ZSTRING_API ZString::ZString(const ZString& str)
	: ZString()
{
	Append(str);
}

ZSTRING_API ZString::ZString(ZString&& str) noexcept
	:ZString()
{
	ptr = str.ptr;
	str.ptr = nullptr; // ?
}

/* destructor */
ZSTRING_API ZString::~ZString()
{
	delete[] ptr;
}

/* function */
ZSTRING_API size_t ZString::Length() const
{
	if (ptr == nullptr) return 0;

	size_t len = 0;
	while (ptr[len])
		++len;

	return len;
}

ZSTRING_API ZString& ZString::Append(const char* c)
{
	if (c == nullptr)
		return *this;

	// resultLen = firstLen + secondLen

	size_t firstLen = Length();
	size_t secondLen = 0;

	while (c[secondLen])
		secondLen++;

	char* result = (char*)malloc((firstLen + secondLen + 1) * sizeof(char)); // 새로 크기 할당 받기
	result[firstLen + secondLen] = '\0';

	memcpy(result, ptr, firstLen);
	memcpy(result + firstLen, c, secondLen);

	delete[] ptr;

	ptr = result;

	return *this;
}

ZSTRING_API ZString& ZString::Append(const ZString &str)
{
	return Append((char*)str.ptr);
}


ZSTRING_API ZString& ZString::Erase(const int pos, size_t num)
{
	size_t currentLen = Length();
	if (pos < 0 || pos >= currentLen || num < 0)
		return *this;

	int i = 0;
	while (ptr[pos + num + i])
	{
		ptr[pos + i] = std::move(ptr[pos + num + i]);
		++i;
	}
	ptr[currentLen - num] = '\0';
	ptr = (char*)realloc(ptr, (currentLen - num + 1) * sizeof(char));

	return *this;
}

ZSTRING_API void ZString::Reverse()
{
	int len = Length();
	int mid = (len - 1) / 2;
	for (int i = 0; i <= mid; i++)
	{
		swap(ptr[i], ptr[len - i - 1]);
	}
}

ZSTRING_API void ZString::Print()
{
	cout << ptr << endl;
}

ZSTRING_API char ZString::At(int i)
{
	return ptr[i];
}
