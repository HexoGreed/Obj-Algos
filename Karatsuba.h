#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>


using namespace std;

/// get length of num 
int getLength(long long val) {
	string strVal = to_string(val);
	return strVal.length();
}




long long pow10(int n) { // gotta do this bc pow returns doubles instead of longs
	long long res = 1;
	for (int i = 0; i < n; i++) {
		res *= 10;
	}


	return res;
}


//non paralel karatsuba

long long karatsuba_nonparalel(long long x, long long y) {
	if (x < 10 || y < 10) {
		return x * y; // doest work for nums less than 10 so added this
	}



	//for size
	int n = max(getLength(x), getLength(y));
	int half = n / 2;

	//calc splitter
	long long split = pow10(half);

	

	//split nums
	long long xl = x / split;
	long long xr = x % split;
	long long yl = y / split;
	long long yr = y % split;

	//recursive
	long long p1 = karatsuba_nonparalel(xl, yl);
	long long p2 = karatsuba_nonparalel(xr, yr);
	long long p3 = karatsuba_nonparalel(xl + xr, yl + yr);




	// p1*10^(2*half)+ (P3 - P1 - P2) * 10^half + P2
	// 
	return (p1 * pow10(2 * half)) + ((p3 - p1 - p2) * pow10(half)) + p2;

}



void threaded_worker(long long x, long long y, long long& result) {
	result = karatsuba_nonparalel(x, y);
}


//paralel karatsuba
long long paralelKaratsuba(long long x ,long long y) {
	if (x < 10 || y < 10) {
		return x * y; // doest work for nums less than 10 so added this
	}


	int n = max(getLength(x), getLength(y)); // copy paste form above
	int half = n / 2;

	//calc splitter
	long long split = pow10(half);



	//split nums
	long long xl = x / split;
	long long xr = x % split;
	long long yl = y / split;
	long long yr = y % split;




	long long p1, p2, p3;


	//created 3 threads
	thread thread1(threaded_worker, xl, yl, ref(p1));
	thread thread2(threaded_worker, xr, yr, ref(p2));
	thread thread3(threaded_worker, xl + xr, yl + yr, ref(p3));

	thread1.join();
	thread2.join();
	thread3.join();

	
	return (p1 * pow10(2 * half)) + ((p3 - p1 - p2) * pow10(half)) + p2;
}