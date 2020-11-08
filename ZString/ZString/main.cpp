#include <iostream>
#include "ZString.h"
#include "ZWString.h"
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