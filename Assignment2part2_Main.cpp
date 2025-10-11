

/*
1.) the reccursion stops when the array = 0 or 1. 0 menas it doesnt exist and 1 means that the only canidate.

2.) if N is odd it isnt paired and carried forward to the next round.

3.) the time complexity is o(n) because each round we scan through the array only once. 
    then we go onto the second array wich has n/2 elements. 
	essentialy we have n + n/2 + n/4 ... +1 = o(n)
    its linear.

4.) we can avoid using an extra array B by not actually storing the survivors.
  instead, we keep track of a single current candidate and a counter.
  when the counter is zero, we take the current element as the candidate and set counter to one.
  if the next element matches the candidate, we increase the counter.
  if it does not match, we decrease the counter (they cancel each other out).
  at the end of the scan, the remaining candidate is the only possible majority element.

  5. Done

  //PArt 2 DOne
*/




#include <iostream>
#include <vector>
using namespace std;

// Recursive function to find candidate  (changed for part 5)
int findCandidate(const vector<int>& A) {
    int candidate = -1; // 
    int count = 0;


    for (int x : A) {


        if (count == 0) {//if counter = 0 new canidate is chosen
            candidate = x;
            count = 1;
		}
		else if (x == candidate) { // increment if same as canidate

            count++;

		}
		else { // decrement if different

            count--;
        }
    }

    return candidate;
}

// Verify if candidate is majority
// It counts how many times the candidate appears and checks if it exceeds N/2.

bool isMajority(const vector<int>& A, int candidate) {
    int count = 0;

    for (int x : A) {

        if (x == candidate) count++;

    }

    return count > (A.size() / 2);
}

int main() {


    vector<vector<int>> testCases = {
    {2, 2, 2, 2, 4, 4, 4, 4, 4},
    {3, 3, 4, 2, 4, 4, 2, 4, 4},

	{1, 1, 1, 2, 2}, //added this
	{ 1, 2, 3, 4, 5 } //for no majoority
    };


    for (const auto& A : testCases) {
        int candidate = findCandidate(A);




        //verify and display
        if (candidate != -1 && isMajority(A, candidate)) {
            cout << "Majority is: " << candidate << endl;
        }
        else {
            cout << "No majority" << endl;
        }
    }


    return 0;
}
