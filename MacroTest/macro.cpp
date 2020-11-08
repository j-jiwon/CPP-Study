#define MAX(a ,b) (((a) > (b)) ? (a) : (b))

int main()
{
	int num1 = 1;
	int num2 = 2;

	int max1 = MAX(num1, num2);
	int max2 = MAX(num1, num2);
	return 0;
}

// $ gcc -E -o macro.i macro.c
// macro.i 
/* 
int main()
{
	int num1 = 1;
	int num2 = 2;

	int max1 = (((num1) > (num2)) ? (num1) : (num2));
	int max2 = (((num1) > (num2)) ? (num1) : (num2));
	return 0;
}
*/