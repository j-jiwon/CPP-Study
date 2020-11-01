#pragma once

class ZWString
{
public:
	ZWString();
	ZWString(const wchar_t* str);
	ZWString(const ZWString& str);
	ZWString(ZWString&& str) noexcept;
	~ZWString();

	/* function */
	size_t Length() const;

	ZWString& Append(const wchar_t* c);
	ZWString& Append(const ZWString &str);
	ZWString& Erase(int pos = 0, size_t num = -1);

	void Reverse();
	void Print();
	wchar_t At(int i);

private:
	wchar_t* ptr;
};

