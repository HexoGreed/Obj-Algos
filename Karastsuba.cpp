#include <iostream>
#include <cmath>
using namespace std;

int karatsuba(int x, int y) {
    // Base case
        if (x < 10 || y < 10)
        return x * y;



    // Find the size of nums
    int n = log10(max(x, y)) + 1;
    int half = n / 2;
    int power = pow(10, half);

    // Split x and y
    int xLeft = x / power;
    int xRight = x % power;
    int yLeft = y / power;
    int yRight = y % power;

    // Recursive calls
    int P1 = karatsuba(xLeft, yLeft);
    int P2 = karatsuba(xRight, yRight);
    int P3 = karatsuba(xLeft + xRight, yLeft + yRight);

    // Combine results
    return P1 * pow(10, 2 * half) + (P3 - P1 - P2) * pow(10, half) + P2;
}

int main() {
    int x, y;
    cout << "Enter first number: ";
    cin >> x;
    cout << "Enter second number: ";
    cin >> y;

    if (x > 123456789 || y > 123456789) {
        cout << "Numbers must be <= 123,456,789." << endl;
        return 1;
    }

    cout << "Karatsuba result: " << karatsuba(x, y) << endl;
    cout << "Normal result: " << x * y << endl;

    return 0;
}
