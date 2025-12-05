
//Hamza S



#include "Karatsuba.h"
using namespace std;


/*
QA: 
10.1
multiplying 123456789 * 123456789
 ----------------------------------------
Serial: 15241578750190521
Serial time: 6.87e-05 seconds
------------------------------------------------
Paralel: 15241578750190521
Paralel  time: 0.0009041 seconds
------------------------------------------------


10.2:
It hits maximum cpu usage when the numbers are large enough to require the 3 recursive calls to
take a long ammount of time. Gneerally modern computers have multiple cores so the threads can be
executed in parallel. So when the recursive calls take a long time the cpu usage spikes to 100
essentially you need a very large numbers to see the effect.



10.3:
The scheme runs into a couple of problems. First yhe overhead constantly creates three new threds
at every recursive call. This can quickly overwhelm the system with too many threads. Second
the scheme does not take into account the number of available cores on the system. If there are
more threads than cores, the system will have to context switch between threads, which can lead
to lower performance.
Third the memory usage grows with every thread because each thread has to do its own bookkeeping. So deep reccursion
increases the cost. It slike trying to move furniture with a lot of people and telling them where they stand.
for something like multplying 1234*5678 thats a pretty small piece of work to divide so its a lot easier. 
the time it takes to give te orders is longer than the time to compute it. The overhead makes it a bigger problem than it 
actually is.



*/





int main() {

	long long x;
	long long y;

	cout << "Enter x  number: ";
	cin >> x;
	cout << "Enter y  number: ";
	cin >> y;



	cout << "multiplying " << x << " * " << y << endl;
	cout << " ----------------------------------------" << endl;

	// serial
	auto start = chrono::high_resolution_clock::now();
	long long result_serial = karatsuba_nonparalel(x, y);
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> serial_duration = end - start;


	cout << "Serial: " << result_serial << endl;
	cout << "Serial time: " << serial_duration.count() << " seconds";

	cout << "\n------------------------------------------------" << endl;




	// paralel runtime
	start = chrono::high_resolution_clock::now();
	long long result_parallel = paralelKaratsuba(x, y);
	end = chrono::high_resolution_clock::now();

	chrono::duration<double> parallel_duration = end - start;




	cout << "Paralel: " << result_parallel << endl;
	cout << "Paralel  time: " << parallel_duration.count() << " seconds";

	cout << "\n------------------------------------------------" << endl;


	return 0;
}