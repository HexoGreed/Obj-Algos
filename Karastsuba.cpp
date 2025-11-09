//Hamza

#include <iostream>
#include <cmath>
using namespace std;

long long karatsuba(long long x, long long y) { // was using int but it overfowed for some inputs
	if (x < 10 || y < 10) {

		return x * y;
		//gottta do this bc if i didnt for some reason it would give me an exit code.
	}






	long long n = log10(max(x, y)) + 1;
	long long half = n / 2;
	long long power = pow(10, half);



	//split
	long long xleft = x / power;
	long long xright = x % power;

	long long yleft = y / power;
	long long yright = y % power;




	//recursion
	long long leftHalf = karatsuba(xleft, yleft);
	long long RightHalf = karatsuba(xright, yright);
	long long sumHalf = karatsuba(xleft + xright, yleft + yright);




	return leftHalf * pow(10, 2 * half) + (sumHalf - leftHalf - RightHalf) * power + RightHalf;

}


int main() {

	long long x, y;
	cout << "Enter two numbers seperated by a space\n";
	cin >> x >> y;


	if (x > 123456789 || y > 123456789) {

		cout << "Numbers are too big keep it under 123456789\n\n";
		return 1;
	}


	cout << "karatsuba: " << karatsuba(x, y) << "\n\n";
	cout << "normal: " << x * y;

	return 0;
}
