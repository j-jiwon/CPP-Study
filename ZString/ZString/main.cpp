// for lib test
//#pragma comment (lib, "../lib/ZStringStaticLib.lib")
//#include "../lib/header/ZString.h"
//#include "../lib/header/ZWString.h"

// for dll test
#include "../ZStringDLL/stdafx.h"
#pragma comment(lib, "../../ZString/Debug/ZStringDLL.lib")
#include "../ZStringDLL/ZString.h"
#include "../ZStringDLL/ZWString.h"

// main
#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	ZString str1("apple");
	std::cout << str1.Length() << std::endl;
	ZString str2("banana!");
	std::cout << str2.Length() << endl;

	str1.Append(str2);
	str1.Print();

	str1.Erase(3, 2);
	str1.Print();

	str1.Reverse();
	str1.Print();

	cout << str1.At(6) << endl;


	ZString str4("가나다");
	cout << str4.Length() << endl << endl; // 6
	cout << "-------------------------------" << endl;

	wcout.imbue(locale(""));

	ZWString wstr(L"가나다"); // 3
	cout << wstr.Length() << endl;
	wstr.Print();

	ZWString wstr1(L"Apple");
	ZWString wstr2(L"Banana");
	wstr1.Print();
	wstr1.Append(wstr2);
	wstr1.Print();

	wstr1.Reverse();
	wstr1.Print();

}