#pragma once

#define ZSTRING_API __declspec(dllexport)
#include <cstddef>
class ZSTRING_API ZString
{
public:
	ZString();
	ZString(const char* str);
	ZString(const ZString& str);
	ZString(ZString&& str) noexcept;
	~ZString();

	/* function */
	size_t Length() const;

	ZString& Append(const char* c);
	ZString& Append(const ZString &str);
	ZString& Erase(int pos = 0, size_t num = -1);

	void Reverse();
	void Print();
	char At(int i);

private:
	char* ptr;

};

