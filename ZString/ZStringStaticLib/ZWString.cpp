#include "stdafx.h"
#include <iostream>
#include <locale>
#include "ZWString.h"
using namespace std;

ZWString::ZWString()
	: ptr(nullptr)
{}

ZWString::ZWString(const wchar_t* str)
	: ZWString()
{
	Append(str);
}

ZWString::ZWString(const ZWString& str)
	: ZWString()
{
	Append(str);
}

ZWString::ZWString(ZWString&& str) noexcept
	:ZWString()
{
	ptr = str.ptr;
	str.ptr = nullptr; // ?
}

/* destructor */
ZWString::~ZWString()
{
	delete[] ptr;
}

/* function */
size_t ZWString::Length() const
{
	if (ptr == nullptr) return 0;

	size_t len = 0;
	while (ptr[len])
		++len;

	return len;
}

ZWString& ZWString::Append(const wchar_t* wc)
{
	if (wc == nullptr)
		return *this;

	// resultLen = firstLen + secondLen

	size_t firstLen = Length();
	size_t secondLen = 0;

	while (wc[secondLen])
		secondLen++;

	wchar_t* result = (wchar_t*)malloc((firstLen + secondLen + 1) * sizeof(wchar_t)); // 새로 크기 할당 받기
	result[firstLen + secondLen] = '\0';

	wmemcpy(result, ptr, firstLen);
	wmemcpy(result + firstLen, wc, secondLen);

	delete[] ptr;

	ptr = result;

	return *this;
}

ZWString& ZWString::Append(const ZWString &str)
{
	return Append((wchar_t*)str.ptr);
}

ZWString& ZWString::Erase(const int pos, size_t num)
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
	ptr = (wchar_t*)realloc(ptr, (currentLen - num + 1) * sizeof(wchar_t));

	return *this;
}

void ZWString::Reverse()
{
	int len = Length();
	int mid = (len - 1) / 2;
	for (int i = 0; i <= mid; i++)
	{
		swap(ptr[i], ptr[len - i - 1]);
	}
}

void ZWString::Print()
{
	wcout << ptr << endl;
}

wchar_t ZWString::At(int i)
{
	return ptr[i];
}
