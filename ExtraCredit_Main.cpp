/*
Hamza s

QA: 


1. Implement and test (driver program) a concrete parallelization strategy for the
solve_min_conflicts function using threads. Focus on how you would distribute
the workload and manage shared resources (if any).



I used a paralel indipendant restart strategy, since minConfolics
is a local search it can get stuck sometimes. So I created multiple threads
each one trying to solve the problem independently with a different random seed.
Each solving a seperate board instance, the first one to find the solution tells the others
to stop




2. Consider the count_conflicts_for_queen function. Is it beneficial to parallelize
the conflict counting for a single queen? Justify your answer, considering the
overhead of thread creation and synchronization. 


No its not really bennificial , the function iterates N times to check to collums. 
This is a very fast operation and the overhead of creating threads and synchronizing them
takes way longer than just running a loop of comparisons.
Paralelizing this would only slow the program down for small to medium values of N.





3. How would you parallelize the process of finding the best row to move a conflicted
queen to within the inner loop of solve_min_conflicts? What are the potential
challenges and benefits of this approach?



to paralelize finding the best row ou would split the row from 0 to n-1 amoung the threads
, ex thread1 checks 0 - 50, thread b checks 51- 100 etc. Each thread would find a local min.
The challenge would be merging the results bcause the main thread has to wait for all workers 
to finish and then compare results. The bennifit would be that for large N values 
it could speed up the search because the algo has a bottle neck of O(N) 







4. Discuss the potential impact of the number of threads on the performance of your
parallelized min-conflicts algorithm. How might the optimal number of threads vary
with the value of 'n'?




Increasing threads improves performace up to the # of physical cores available.
A small N value wouldnt bennifit because te overhead would dominate.
A large N calue would bennifit more because the search space is larger and more threads
could explore it faster. but using more cores than avaliable would worsen the performace







5. Compare the actual computed runtime performance of your parallelized algorithm
to the sequential version. For which values of 'n' do you anticipate the parallel
version to show a significant improvement, and why might it be worse for other
values?


//im skipping this










*/



























#include "ExtraCredit.h"
#include <iostream>

using namespace std;



int main() {
	int n = 50;
	int maxItters = 1000;

	int numThreads = thread::hardware_concurrency(); //get the cores

	if (numThreads == 0) {
		numThreads = 4; //default to 4 threads if can't detect
	}



	cout << "solving N Queens (N = " << n << " ) using << " << numThreads << " Threads" << endl;


	vector<std::thread> threads;
	auto start_time = std::chrono::high_resolution_clock::now();




	for (int i = 0; i < numThreads; ++i) {

		threads.emplace_back(solverWork, n, maxItters, i + 100);
	}

	for (auto& t : threads) {

		if (t.joinable()) {


			t.join();
		}
	}


	auto end_time = chrono::high_resolution_clock::now();
	chrono::duration<double> diff = end_time - start_time;


	if (!final_soln.empty()) {

		cout << "Solution found: " << endl;
		cout << "time: " << diff.count() << "seconds " << endl;

		cout << "first 10 rows: \n";


		for (int i = 0; i < std::min(n, 10); ++i) std::cout << final_soln[i] << " ";
		std::cout << "\n";
	}







	return 0;
} // main