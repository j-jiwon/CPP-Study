#include <iostream>
#include "ZFunction.cpp"

using namespace std;

ZFunction<double(int, int)> lambda;
ZFunction<double(int, int)> func;

double Divide(int a, int b)
{
	if (b != 0)
	{
		return (double)a / b;
	}
	return 0;
}

void main()
{
	double vx = 0.3;
	double rx = 0;

	lambda = [vx, &rx](int a, int b)->double
	{
		rx = 0.5;
		return vx + rx + a + b;
	};

	func = &Divide;
	cout << lambda(1, 2) << endl;
	cout << func(1, 2) << endl;

}