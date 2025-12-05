#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;


//precent overflow
typedef long long int64;



int64 gcd(int64 a, int64 m) {
	int64 x = a;
	int64 y = m;

	while (y != 0) {
		int64 r = x % y;
		x = y;
		y = r;
	}
	return x;
}


// algo to find decryption key d
int64 extendGCD(int64 e, int64 m) {
	int64 s = 0, old_s = 1;
	int64 t = 1, old_t = 0;
	int64 r = m, old_r = e;



	while (r != 0) {

		int64 quot = old_r / r;

		int64 temp = r;
		r = old_r - quot * r;
		old_r = temp;

		temp = s;
		s = old_s- quot * s;//was uring old r here instead of t
		old_s = temp;


		temp = t;
		t = old_t - quot * t;
		old_t = temp;
	}

	if (old_s < 0) {
		old_s = old_s + m;
	}

	return old_s;
}


int64 modPow(int64 base, int64 exponent, int64 modulo) {
	if (modulo == 1) return 0;
	int64 c = 1;
	for (int64 i = 0; i < exponent; i++) {
		c = (c * base) % modulo;
	}

	return c;
}


